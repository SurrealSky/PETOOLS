#ifndef __SGI_MALLOC_MEMORYPOOL_HPP
#define __SGI_MALLOC_MEMORYPOOL_HPP



#include <iostream>
#include <new>
#include <exception>



namespace async
{

	namespace memory
	{


		class MallocMemoryPool
		{
			// ����set_new_handler(),ָ���Լ���out-of-memory handler
			typedef void (*pFuncOOMHandler)();

		private:
			static pFuncOOMHandler m_pFuncOOMHandler;

		private:
			// ���º������������ڴ治��
			// oom : out of memory
			static void *OOMMalloc(size_t sz)
			{
				pFuncOOMHandler pHandler = NULL;
				void *pResult = NULL;

				// ���ϳ����ͷš����á����ͷš�������...
				for( ; ; )
				{
					pHandler = m_pFuncOOMHandler;

					if( NULL == pHandler )
						throw std::bad_alloc();

					// ���ô�����,��ͼ�ͷ��ڴ�
					(*pHandler)();

					// �ٴγ��������ڴ�
					pResult = std::malloc(sz);
					if( pResult )
						return pResult;
				}
			}


			static void *OOMRealloc(void *p, size_t sz)
			{
				pFuncOOMHandler pHandler = NULL;
				void *pResult = NULL;

				// ���ϳ����ͷš����á����ͷš�������...
				for( ; ; )
				{
					pHandler = m_pFuncOOMHandler;

					if( NULL == pHandler )
						throw std::bad_alloc();

					// ���ô�����,��ͼ�ͷ��ڴ�
					(*pHandler)();

					// �ٴγ��������ڴ�
					pResult = std::realloc(p, sz);
					if( pResult )
						return pResult;
				}
			}



		public:
			static void *Allocate(size_t sz)
			{
				// ֱ��ʹ��malloc
				void *pResult = std::malloc(sz);

				// ����޷�����Ҫ��ʱ,����OOMMalloc
				if( NULL == pResult )
					pResult = OOMMalloc(sz);

				return pResult;
			}

			static void Deallocate(void *p, size_t/* sz*/)
			{
				// ֱ��ʹ��free
				std::free(p);
			}


			static void *Reallocate(void *p, size_t/* szOld*/, size_t szNew)
			{
				// ֱ��ʹ��realloc
				void *pResult = std::realloc(p, szNew);

				// �޷�����Ҫ��ʱ, ����OOMRealloc
				if( NULL == pResult )
					pResult = OOMRealloc(p, szNew);

				return pResult;
			}


			// ����set_new_handler(),ָ���Լ���out-of-memory handler
			static void (*MallocMemoryPool::pFuncSetOOMHandler(pFuncOOMHandler pFunc))()
			{
				pFuncOOMHandler pOldFunc = m_pFuncOOMHandler;
				m_pFuncOOMHandler = pFunc;

				return pOldFunc;
			}
		};

		// __declspec(selectany) ��ֹLNK2005
		__declspec(selectany) MallocMemoryPool::pFuncOOMHandler MallocMemoryPool::m_pFuncOOMHandler = NULL;
	}
}


#endif