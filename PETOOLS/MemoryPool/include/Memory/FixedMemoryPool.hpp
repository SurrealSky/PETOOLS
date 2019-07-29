#ifndef __MEMORY_FIXED_MEMORY_POOL_HPP
#define __MEMORY_FIXED_MEMORY_POOL_HPP


#include "SGIMemoryPool.hpp"

namespace async
{

	namespace memory
	{


		// ������С__BYTES = 10 * 1024

		template<bool __IS_MT, size_t __BYTES, typename AllocT = MallocAllocateTraits>
		class FixedMemoryPool
		{
		public:
			typedef typename LockTypeTraits<__IS_MT>::value_type LockType;
			typedef thread::CAutoLock<LockType>			AutoLock;
			typedef AllocT								AllocType;

			// ���̹߳���ʱ��Ӧ���ñ�������volatile���Σ������߳�Ӧ�����価���Ż�����ٶ�
			union obj;
			typedef typename ValueTypeVolatileTraits<obj, __IS_MT>::value_type	ObjPtrType;


		private:
			// ÿ�γ�ʼ��ʱ������free - list������Ԫ�ص�����
			static const size_t __NUM_NODE = 20;
			static const size_t __ALIGN = 4;

			// ROUND_UP ��bytes�ϵ���__ALIGN�ı���
			enum { ROUND = (__BYTES + __ALIGN - 1) & ~(__ALIGN - 1) };

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
			ObjPtrType m_pFreeLists[1];


		public:
			FixedMemoryPool()
				: m_pStartFree(NULL)
				, m_pEndFree(NULL)
				, m_szHeap(0)
			{
				::memset((void *)m_pFreeLists, 0, 1 * sizeof(ObjPtrType));
			}

			~FixedMemoryPool()
			{
				clear();
			}

		private:
			FixedMemoryPool(const FixedMemoryPool &);
			FixedMemoryPool &operator=(const FixedMemoryPool &);

		public:
			// n�������0
			void *Allocate(size_t n)
			{
				assert(n == __BYTES);

				// Ѱ��free - lists���ʵ���һ��
				ObjPtrType *pFreeListTemp = m_pFreeLists;
				obj *pResult = NULL;

				// ���ù��캯��ʱ��Ҫ����
				{
					AutoLock lock(m_lock);	

					pResult = *pFreeListTemp;

					if( pResult == NULL )
					{	
						// ���û���ҵ����õ�������
						pResult = ReFill(ROUND);
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
				assert(n == __BYTES);

				// �õ��ڴ�ص�ַ
				obj *pTemp = reinterpret_cast<obj *>(p);
				ObjPtrType *pFreeListTemp = m_pFreeLists;

				{
					AutoLock lock(m_lock);

					// ���ա��ı�Nextָ�룬�����صĽڵ����List��ͷ
					pTemp->pFreeListLink = *pFreeListTemp;
					*pFreeListTemp = pTemp;
				}

			}

		private:
			// ROUND_UP ��bytes�ϵ���__ALIGN�ı���
			static inline size_t ROUNDUP(size_t bytes)
			{
				return ((bytes) + __ALIGN - 1) & ~(__ALIGN - 1);
			}

		private:
			// ����һ����СΪn�Ķ���,�������СΪn���������鵽free - list
			obj *ReFill(size_t n)
			{
				// ȱʡΪ__NUM_NODE��������,����ڴ�ռ䲻�㣬��õ����������С��20
				size_t nObjs = __NUM_NODE;

				// ����ChunkAlloc,����ȡ��nObjs������
				// nObjs����Pass By reference����
				char *pChunk = ChunkAlloc(n, nObjs);

				// ���ֻ���һ������,���������ͷ����������,���¿�������
				if( 1 == nObjs )
					return reinterpret_cast<obj *>(pChunk);

				// �������free - list��ע��������
				ObjPtrType *pFreeListTemp  = m_pFreeLists;

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
					// �ڴ��ʣ��ռ䲻��һ������
					// ��Ҫ��ȡ���ڴ�, ע���һ�η��䶼Ҫ������szTotal�Ĵ�С
					// ͬʱҪ����ԭ�е�m_szHeap / 4�Ķ���ֵ
					size_t szGet = 2 * szTotal + ROUNDUP(m_szHeap >> 4);

					// ����Heap�ռ䣬���������ڴ��
					m_pStartFree = reinterpret_cast<char *>(AllocType::Allocate(szGet));

					if( NULL == m_pStartFree )
					{
						// û�з��䵽�ڴ棬ת��MallocMemoryPool
						m_pEndFree = 0;
						m_pStartFree = reinterpret_cast<char *>(MallocMemoryPool::Allocate(szGet));
						if( NULL == m_pStartFree )
							throw std::bad_alloc("FixedMemoryPool");
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


		typedef FixedMemoryPool<true, 10 * 1024>	MTFixedMemoryPool;
		typedef FixedMemoryPool<false, 10 * 1024>	STFixedMemoryPool;

	}
}




#endif