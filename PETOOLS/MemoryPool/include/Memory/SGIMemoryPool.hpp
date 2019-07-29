#ifndef __SGI_MEMORYPOOL_HPP
#define __SGI_MEMORYPOOL_HPP


#include "../MultiThread/Lock.hpp"
#include "SGIMallocPool.hpp"
#include <vector>
#include <algorithm>




/*
	ʵ�ַ���:
	���ڴ�ز���HASH-LIST���ݽṹ��������,����һ���ڴ�ʱ,�����Ҫ����ڴ泬����ĳ��������ֱ�ӵ���malloc�����ڴ�, 
	�������Ƚ������ݶ���,�����������Ľ���õ����ڵ�HASH��,�ڸ�HASH-LIST�в���ʱ����ڿ��õĽڵ�,
	����о�ֱ�ӷ���,����ÿ����20���ڵ�Ԫ��Ϊ������ʼ����LIST�е�Ԫ������,
	�����Ȼ����ʧ���˾�ȥ��һ��HASH���в��ҿ����ڴ�,��������
*/



namespace async
{

	namespace memory
	{

		// ���̲߳���Ҫvolatile�����߳�����Ҫ
		template<typename T, bool __IS_MT>
		struct ValueTypeVolatileTraits
		{
			typedef T* volatile 		value_type;
		};
		template<typename T>
		struct ValueTypeVolatileTraits<T, false>
		{
			typedef T*					value_type;
		};


		// ��ѡ����
		template<bool __IsMt>
		struct LockTypeTraits
		{
			typedef thread::CAutoCriticalSection	value_type;
		};
		template<>
		struct LockTypeTraits<false>
		{
			typedef thread::CAutoNull				value_type;
		};


		// Win32 �Ϸ����ڴ淽ʽ

		struct VirtualAllocateTraits
		{
			static void *Allocate(size_t size)
			{
				// ��ָ�����ڴ�ҳ��ʼ�ձ����������ڴ��ϣ�����������������ҳ�ļ���
				void *p = ::VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, PAGE_EXECUTE_READWRITE);
				::VirtualLock(p, size);

				return p;
			}

			static void Deallocate(void *p, size_t size)
			{
				::VirtualUnlock(p, size);
				::VirtualFree(p, size, MEM_RELEASE);
			}
		};

		struct HeapAllocateTraits
		{
			static HANDLE GetHeap()
			{
				static HANDLE heap = NULL;

				if( heap == NULL )
				{
					heap = ::HeapCreate(0, 0, 0);

					// ���õ���Ƭ��
					ULONG uHeapFragValue = 2;
					::HeapSetInformation(heap, HeapCompatibilityInformation, &uHeapFragValue, sizeof(ULONG));
				}

				return heap;
			}

			static void *Allocate(size_t size)
			{
				return ::HeapAlloc(GetHeap(), HEAP_ZERO_MEMORY, size);;
			}

			static void Deallocate(void *p, size_t/* size*/)
			{
				::HeapFree(GetHeap(), 0, p);
			}
		};

		struct MallocAllocateTraits
		{
			static void *Allocate(size_t size)
			{
				return std::malloc(size);
			}

			static void Deallocate(void *p, size_t)
			{
				return std::free(p);
			}
		};


		// С����������� __MAX_BYTES = 256

		template<bool __IS_MT, size_t __MAX_BYTES, typename AllocT = MallocAllocateTraits>
		class SGIMemoryPool
		{
		public:
			typedef typename LockTypeTraits<__IS_MT>::value_type LockType;
			typedef thread::CAutoLock<LockType>			AutoLock;
			typedef AllocT								AllocType;

			// ���̹߳���ʱ��Ӧ���ñ�������volatile���Σ������߳�Ӧ�����価���Ż�����ٶ�
			union obj;
			typedef typename ValueTypeVolatileTraits<obj, __IS_MT>::value_type	ObjPtrType;



		private:
			// С��������ϵ��߽�
			static const size_t __ALIGN = 8;

			// free-lists�ĸ���
			static const size_t __NUM_FREE_LISTS = __MAX_BYTES / __ALIGN;

			// ÿ�γ�ʼ��ʱ������free - list������Ԫ�ص�����
			static const size_t __NUM_NODE = 20;

			// Chunk allocation state
		private:
			// �ڴ����ʼλ��
			char *m_pStartFree;
			// �ڴ�ؽ���λ��
			char *m_pEndFree;
			// ������Ŀռ��С
			size_t m_szHeap;

			typedef std::vector<std::pair<void *, size_t>> Bufs;
			Bufs m_bufs;

			// �߳���
			LockType m_lock;	

		private:
			// free - lists�Ľڵ㹹��
			union obj
			{
				union obj *pFreeListLink;
				char clientData[1];		/* The client sees this*/
			};

			// free - lists����
			ObjPtrType m_pFreeLists[__NUM_FREE_LISTS];


		public:
			SGIMemoryPool()
				: m_pStartFree(NULL)
				, m_pEndFree(NULL)
				, m_szHeap(0)
			{
				//STATIC_ASSERT(__NUM_FREE_LISTS != 0, __NUM_FREE_LISTS);

				m_bufs.reserve(__NUM_FREE_LISTS);
				::memset((void *)m_pFreeLists, 0, __NUM_FREE_LISTS * sizeof(ObjPtrType));
			}

			~SGIMemoryPool()
			{
				clear();
			}

		private:
			SGIMemoryPool(const SGIMemoryPool &);
			SGIMemoryPool &operator=(const SGIMemoryPool &);

		public:
			// n�������0
			void *Allocate(size_t n)
			{
				// ����__MAX_BYTES����MallocAllocator
				if( n > __MAX_BYTES )
				{
					return MallocMemoryPool::Allocate(n);
				}

				// Ѱ��free - lists���ʵ���һ��
				ObjPtrType *pFreeListTemp = m_pFreeLists + FREELISTINDEX(n);
				obj *pResult = NULL;

				// ���ù��캯��ʱ��Ҫ����
				{
					AutoLock lock(m_lock);	

					pResult = *pFreeListTemp;

					if( pResult == NULL )
					{	
						// ���û���ҵ����õ�free - list��׼���������free - list
						pResult = ReFill(ROUNDUP(n));
					}
					else
					{
						// ����free list,ʹ��ָ����һ��List�Ľڵ㣬���������ʱ��ͷ���ΪNULL
						*pFreeListTemp = pResult->pFreeListLink;
					}

				}

				return pResult;
			}


			// p����Ϊ��
			void Deallocate(void *p, size_t n)
			{
				// ����__MAX_BYTES����MallocAllocator
				if( n > __MAX_BYTES )
					return MallocMemoryPool::Deallocate(p, n);

				// Ѱ��free - lists���ʵ���һ��
				obj *pTemp = reinterpret_cast<obj *>(p);
				ObjPtrType *pFreeListTemp = m_pFreeLists + FREELISTINDEX(n);

				{
					AutoLock lock(m_lock);

					// ������Ӧ��free - list,���ա��ı�Nextָ�룬�����صĽڵ����List��ͷ
					pTemp->pFreeListLink = *pFreeListTemp;
					*pFreeListTemp = pTemp;
				}

			}


			void *Reallocate(void *p, size_t szOld, size_t szNew)
			{
				// �������__MAX_BYTES����MallocAllocator
				if( szOld > __MAX_BYTES && szNew > __MAX_BYTES) 
				{
					return MallocMemoryPool::Reallocate(p, szOld, szNew);
				}

				// ���Բ����Ĵ�С��ͬ��ֱ�ӷ���
				if( ROUNDUP(szOld) == ROUNDUP(szNew) ) 
					return p;

				// �ٴ�����ռ�
				void *pResult = Allocate(szNew);

				// �ж�ѡ����������
				size_t szcopy = szNew > szOld ? szOld : szNew;
				::memmove(pResult, p, szcopy);

				// ɾ��ԭ�ȵ�����
				Deallocate(p, szOld);

				return pResult;

			}


		private:
			// ROUND_UP ��bytes�ϵ���__ALIGN�ı���
			static inline size_t ROUNDUP(size_t bytes)
			{
				return ((bytes) + __ALIGN - 1) & ~(__ALIGN - 1);
			}

			// ���������С������ʹ�õ�n��free - lists��n��0����
			static inline size_t FREELISTINDEX(size_t bytes)
			{
				return (((bytes) + __ALIGN - 1) / __ALIGN) - 1;
			}

		private:
			// ����һ����СΪn�Ķ���,�������СΪn���������鵽free - list
			obj *ReFill(size_t n)
			{
				// ȱʡΪ__NUM_NODE��������,����ڴ�ռ䲻�㣬��õ����������С��20
				size_t nObjs = __NUM_NODE;

				// ����ChunkAlloc,����ȡ��nObjs������Ϊfree - list��������
				// nObjs����Pass By reference����
				char *pChunk = ChunkAlloc(n, nObjs);

				// ���ֻ���һ������,���������ͷ���������ߣ�free - list��������
				if( 1 == nObjs )
					return reinterpret_cast<obj *>(pChunk);

				// �������free - list��ע��������
				ObjPtrType *pFreeListTemp  = m_pFreeLists + FREELISTINDEX(n);

				// ��Chunk�ռ��ڽ���free - list
				// pResult׼�����ظ��ͻ���
				obj *pResult = reinterpret_cast<obj *>(pChunk);

				obj *pCurObj = NULL, *pNextObj = NULL;

				// ������һ����λ���ڴ棬����һ������
				--nObjs;
				// ��Ҫ����һ����λ���ڴ棬����һ����λ��ʼ��ʣ���obj��������, ����free - listָ�������ÿռ�
				*pFreeListTemp = pNextObj = reinterpret_cast<obj *>(pChunk + n);

				// ��free - list�ĸ����鴮������
				// ��1��ʼ,��0������
				for(size_t i = 1; ; ++i)
				{
					pCurObj = pNextObj;
					pNextObj = reinterpret_cast<obj *>(reinterpret_cast<char *>(pNextObj) + n);

					if( nObjs == i )
					{
						// �������, ��һ���ڵ�ΪNULL, �˳�ѭ��
						pCurObj->pFreeListLink = NULL;
						break;
					}
					else
					{
						pCurObj->pFreeListLink = pNextObj;
					}
				}

				return pResult;
			}

			// ����һ���ռ�,������nObjs����СΪsize������
			// ���䵥λ�ߴ�Ϊsize, ��nObjs��Ԫ��
			// ��Щ�ڴ��������ַ��������һ���, ������ָ��
			char *ChunkAlloc(size_t sz, size_t &nObjs)
			{
				size_t szTotal = sz * nObjs;
				// �ڴ��ʣ��ռ�
				size_t szLeft =  m_pEndFree - m_pStartFree;

				char *pResult = NULL;
				if( szLeft >= szTotal )
				{
					// �ڴ��ʣ��ռ���������
					pResult = m_pStartFree;

					// �ƶ�ָ��ʣ��ռ��ָ��
					m_pStartFree += szTotal;

					return pResult;
				}
				else if( szLeft >= sz )
				{
					// �ڴ��ʣ��ռ䲻����ȫ���������������㹻һ�����ϵ�����
					// �ı�����Ĵ�С
					nObjs = szLeft / sz;

					// �ƶ�ָ��ʣ��ռ��ָ��
					szTotal = sz * nObjs;
					pResult = m_pStartFree;
					m_pStartFree += szTotal;

					return pResult;
				}
				else 
				{
					// �������ڴ���е�ʣ�໹�����ü�ֵ
					if( szLeft > 0 )
					{
						// ������ʵ���free - list, Ѱ���ʵ���free - list
						ObjPtrType *pFreeListTemp = m_pFreeLists + FREELISTINDEX(szLeft);

						// ����free - list�����ڴ���еĲ���ռ����
						reinterpret_cast<obj *>(m_pStartFree)->pFreeListLink = *pFreeListTemp;
						*pFreeListTemp = reinterpret_cast<obj *>(m_pStartFree);
					}

					// �ڴ��ʣ��ռ䲻��һ������
					// ��Ҫ��ȡ���ڴ�, ע���һ�η��䶼Ҫ������szTotal�Ĵ�С
					// ͬʱҪ����ԭ�е�m_szHeap / 4�Ķ���ֵ
					size_t szGet = 2 * szTotal + ROUNDUP(m_szHeap >> 4);

					// ����Heap�ռ䣬���������ڴ��
					m_pStartFree = reinterpret_cast<char *>(AllocType::Allocate(szGet));

					if( NULL == m_pStartFree )
					{
						// Heap�ռ䲻��
						ObjPtrType *pFreeList = NULL; 
						obj *pTemp = NULL;

						for(int i = sz; i <= __MAX_BYTES; i += __ALIGN)
						{
							pFreeList = m_pFreeLists + FREELISTINDEX(i);
							pTemp = *pFreeList;

							if( NULL == pTemp )
							{
								// free - list����δ�����飬���������ͷ�
								*pFreeList = pTemp->pFreeListLink;
								m_pStartFree = reinterpret_cast<char *>(pTemp);
								m_pEndFree = m_pStartFree + i;

								// �ݹ���ã�����nObjs
								return ChunkAlloc(sz, nObjs);
							}
						}

						// û�з��䵽�ڴ棬ת��MallocMemoryPool
						m_pEndFree = 0;
						m_pStartFree = reinterpret_cast<char *>(MallocMemoryPool::Allocate(szGet));
					}

					// �洢�����ṩ�ͷ�
					m_bufs.push_back(std::make_pair(m_pStartFree, szGet));

					m_szHeap += szGet;
					m_pEndFree = m_pStartFree + szGet;

					// �ݹ���ã�����nObjs
					return ChunkAlloc(sz, nObjs);
				}
			}

			// ����ڴ�
			void clear()
			{
				for(Bufs::iterator iter = m_bufs.begin();
					iter != m_bufs.end(); ++iter)
				{
					AllocType::Deallocate(iter->first, iter->second);
				}
				m_bufs.clear();
			}
		};


		typedef SGIMemoryPool<true, 256>				SGIMTMemoryPool;
		typedef SGIMemoryPool<false, 256>				SGISTMemoryPool;

	}
}

#endif