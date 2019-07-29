#ifndef __POOL_HPP
#define __POOL_HPP

// 这个是Bjarne大师的
namespace Bjarne
{



	class Pool
	{
	private:
		struct Link
		{
			Link *next_;
		};

		struct Chunk
		{
			enum { SIZE = 8 * 1024 - 16 };
			char storage_[SIZE];
			Chunk *next_;
		};


	private:
		Chunk *chunks_;
		Link *head_;
		const size_t size_;


	public:
		explicit Pool(size_t sz)
			: head_(0)
			, chunks_(0)
			, size_(sz < sizeof(Link) ? sizeof(Link) : sz)
		{}
		~Pool()
		{
			Chunk *cur = chunks_;
			while(cur)
			{
				Chunk *p = cur;
				cur = cur->next_;

				delete p;
			}
		}

	public:
		void *Alloc()
		{
			if( head_ == NULL )
				_Grow();

			Link *p = head_;
			head_ = p->next_;

			return p;
		}

		void Free(void *p)
		{
			Link *link	= static_cast<Link *>(p);
			link->next_ = head_;
			head_		= link;
		}

	private:
		Pool(const Pool &);
		Pool &operator=(const Pool &);

	private:
		void _Grow()
		{
			Chunk *p = new Chunk;
			p->next_ = chunks_;
			chunks_ = p;

			const size_t elem = Chunk::SIZE / size_;
			char *start = p->storage_;
			char *last = &start[(elem - 1) * size_];

			for(char *p = start; p < last; p += size_)
				reinterpret_cast<Link *>(p)->next_ = reinterpret_cast<Link *>(p + size_);

			reinterpret_cast<Link *>(last)->next_ = 0;
			head_ = reinterpret_cast<Link *>(start);
		}
	};


}


#endif