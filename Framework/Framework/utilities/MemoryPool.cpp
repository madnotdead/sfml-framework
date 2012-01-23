#include "MemoryPool.h"

#include <malloc.h>

namespace Utils
{
	MemoryPool::MemoryPool(const uint32_t howMany, const size_t size)
		: mCurrentFreeBlock(0)
		, mBlockSize((sizeof(MemoryBlock*) <= size) ? size : sizeof(MemoryBlock*))
		, mNumberOfBlocksToExpand(howMany)
	{
		assert(0 < howMany && "MemoryPool::MemoryPool: The number of blocks cannot be zero.");
		assert(0 < size && "MemoryPool::MemoryPool: The size of blocks cannot be zero.");

		ExpandTheFreeList();
	}

	MemoryPool::~MemoryPool()
	{
		MemoryBlock *nextToDelete = mCurrentFreeBlock;
		while(nextToDelete)
		{
			// Delete the current block.
			mCurrentFreeBlock = mCurrentFreeBlock->mNextBlock;
			delete[] reinterpret_cast<uint8_t*> (nextToDelete);

			// Go to the new current free block.
			nextToDelete = mCurrentFreeBlock;
		}
	}

	void MemoryPool::ExpandTheFreeList()
	{
		assert(0 < mNumberOfBlocksToExpand && "MemoryPool::ExpandTheFreeList: The number of elements cannot be zero.");
		assert(0 < mBlockSize && "MemoryPool::ExpandTheFreeList: The size of elements cannot be zero.");

		// Allocate the first element and update the next free element.
		MemoryBlock *block = reinterpret_cast<MemoryBlock*> (new uint8_t [mBlockSize]);
		mCurrentFreeBlock = block;

		// Allocate the others  and link them.
		const uint32_t allocationsRemaining = mNumberOfBlocksToExpand - 1;
		for (uint32_t i = 0; i < allocationsRemaining; ++i)
		{
			block->mNextBlock = reinterpret_cast<MemoryBlock*> (new uint8_t [mBlockSize]);
			block = block->mNextBlock;
		}

		// Finish the free list.
		block->mNextBlock = 0;
	}
}
