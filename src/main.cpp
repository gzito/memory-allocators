#include <iostream>
#include <cstddef>
#include <vector>
#include <memory>

#include "Benchmark.h"
#include "Allocator.h"
#include "StackAllocator.h"
#include "CAllocator.h"
#include "LinearAllocator.h"
#include "PoolAllocator.h"
#include "FreeListAllocator.h"

int main() {
	try {
		const std::vector<std::size_t> ALLOCATION_SIZES {32, 64, 256, 512, 1024, 2048, 4096};
		const std::vector<std::size_t> ALIGNMENTS {8, 8, 8, 8, 8, 8, 8};

		auto cAllocator = std::make_unique<CAllocator>() ;
		auto linearAllocator = std::make_unique<LinearAllocator>((std::size_t)1e9) ;		// 1 GB
		auto stackAllocator = std::make_unique<StackAllocator>((std::size_t)1e9);		// 1 GB
		auto poolAllocator = std::make_unique<PoolAllocator>(16777216, 4096);	// 16 MB
		auto freeListAllocator = std::make_unique<FreeListAllocator>((std::size_t)1e8, FreeListAllocator::PlacementPolicy::FIND_FIRST);	// 100 MB

		Benchmark benchmark(10);

		std::cout << "C" << std::endl;
		benchmark.MultipleAllocation(cAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
		benchmark.MultipleFree(cAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
		benchmark.RandomAllocation(cAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
		benchmark.RandomFree(cAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS); 

		std::cout << "LINEAR" << std::endl;
		benchmark.MultipleAllocation(linearAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
		benchmark.RandomAllocation(linearAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);

		std::cout << "STACK" << std::endl;
		benchmark.MultipleAllocation(stackAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
		benchmark.MultipleFree(stackAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
		benchmark.RandomAllocation(stackAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
		benchmark.RandomFree(stackAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);

		std::cout << "POOL" << std::endl;
		benchmark.SingleAllocation(poolAllocator.get(), 4096, 8);
		benchmark.SingleFree(poolAllocator.get(), 4096, 8);

		std::cout << "FREE LIST" << std::endl;
		benchmark.MultipleAllocation(freeListAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
		benchmark.MultipleFree(freeListAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
		benchmark.RandomAllocation(freeListAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
		benchmark.RandomFree(freeListAllocator.get(), ALLOCATION_SIZES, ALIGNMENTS);
	}
	catch( std::exception& ex ) {
		std::cout << "Error: " << ex.what() << std::endl ;
	}
    return 1;
}




