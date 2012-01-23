#ifndef UTILS_MEMORY_POOL_H
#define UTILS_MEMORY_POOL_H

#include <cassert>

#include "Types.h"

namespace Utils
{
	class MemoryPool
	{
	public:
		MemoryPool(const uint32_t howMany, const size_t size);
		~MemoryPool();

		inline void* Alloc(const size_t size);
		inline void Free(void *someElement);

	private:
		struct MemoryBlock
		{
			MemoryBlock *mNextBlock;
		};

		MemoryBlock *mCurrentFreeBlock; // Next element on the free list.

		const size_t mBlockSize; // Size of each block to expand.
		const uint32_t mNumberOfBlocksToExpand; // Number of blocks to expand in the pool.

		// Add free elements to the free list.
		void ExpandTheFreeList();
	};

	void* MemoryPool::Alloc(const size_t size)
	{
		assert(size <= mBlockSize && "MemoryPool::Alloc: The requested size is bigger than the block size");

		// If there are not free blocks, we need to
		// expand the pool.
		if(!mCurrentFreeBlock)
			ExpandTheFreeList();

		MemoryBlock * const head = mCurrentFreeBlock;
		mCurrentFreeBlock = head->mNextBlock;

		return head;
	}

	void MemoryPool::Free(void *someElement)
	{
		MemoryBlock * const head = static_cast <MemoryBlock*> (someElement);
		head->mNextBlock = mCurrentFreeBlock;
		mCurrentFreeBlock = head;
	}
}

#endif // UTILS_MEMORY_POOL_H
