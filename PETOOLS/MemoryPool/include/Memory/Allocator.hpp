#ifndef __ALLOCATOR_HPP
#define __ALLOCATOR_HPP



#include "SGIMemoryPool.hpp"


namespace async
{
	namespace memory
	{


		// ------------------------------------------------------------
		// class Allocator

		template<typename T, typename AllocT = SGIMTMemoryPool>
		class Allocator
		{
		public:
			// type definitions
			typedef T				value_type;
			typedef T*				pointer;
			typedef const T*		const_pointer;
			typedef T&				reference;
			typedef const T&		const_reference;
			typedef size_t			size_type;
			typedef ptrdiff_t		difference_type;

			// rebind allocator to type U
			template<typename U>
			struct rebind 
			{
				typedef Allocator<U, AllocT> other;
			};

		private:
			static AllocT m_alloc;

		public:
			/* constructors and destructor
			* - nothing to do because the allocator has no state
			*/
			Allocator()
			{
			}
			Allocator(const Allocator &rhs)
				: m_alloc(rhs.m_alloc)
			{
			}
			template<typename U>
			Allocator(const Allocator<U, AllocT>& rhs)
				: m_alloc(rhs.m_alloc)
			{
			}
			~Allocator()
			{
			}

		public:
			// return address of values
			static pointer Address(reference value)
			{
				return &value;
			}
			static const_pointer Address(const_reference value)
			{
				return &value;
			}

			// return maximum number of elements that can be allocated
			static size_type MaxSize()
			{
				size_type count = static_cast<size_type>(-1) / sizeof(value_type);

				return 0 < count ? count : 1;
			}

			// allocate but don't initialize num elements of type T
			static pointer Allocate() 
			{
				pointer ret = reinterpret_cast<pointer>(m_alloc.Allocate(sizeof(value_type)));

				return ret;
			}

			static pointer Allocate(size_type num, const void* const = 0) 
			{
				pointer ret = reinterpret_cast<pointer>(m_alloc.Allocate(num * sizeof(value_type)));

				return ret;
			}

			// deallocate storage p of deleted elements
			static void Deallocate(pointer p) 
			{
				Destroy(p);
				return m_alloc.Deallocate(p, sizeof(value_type));
			}
			static void Deallocate(pointer p, size_type num) 
			{
				Destroy(p);
				return m_alloc.Deallocate(p, num * sizeof(value_type));
			}

			// initialize elements of allocated storage p with value value
			static void Construct(pointer p)
			{
				// initialize memory with placement new
				//__Construct(p);
			}

			template<typename Arg>
			static void Construct(pointer p, const Arg& value)
			{
				// initialize memory with placement new
				//__Construct(p, value);
			}

			// destroy elements of initialized storage p
			static void Destroy(pointer p) 
			{
				// destroy objects by calling their destructor
				//__Destroy(p);
			}
		};
		template<typename T, typename AllocT> 
		AllocT Allocator<T, AllocT>::m_alloc;




		// return that all specializations of this allocator are interchangeable
		template<typename T, typename AllocT>
		bool operator==(const Allocator<T, AllocT>&, const Allocator<T, AllocT>&)
		{
			return true;
		}
		template<typename T, typename AllocT>
		bool operator!=(const Allocator<T, AllocT>&, const Allocator<T, AllocT>&)
		{
			return false;
		}

	}
}




#endif