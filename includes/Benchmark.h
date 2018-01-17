#ifndef BENCHMARK_H
#define BENCHMARK_H

#if defined(_MSC_VER)
#include <windows.h>	// LARGE_INTEGER & QueryPerformanceCounter
#else
#include <time.h> // timespec
#endif
#include <cstddef> // std::size_t
#include <vector>
#include "Allocator.h" // base class allocator

struct BenchmarkResults {
	long nOperations;
	double elapsedTime;
	double operationsPerSec;
	double timePerOperation;
	std::size_t memoryPeak;
};

class Benchmark {
public:
	Benchmark(const unsigned int nOperations);

	void SingleAllocation(Allocator* allocator, const std::size_t size, const std::size_t alignment);
	void SingleFree(Allocator* allocator, const std::size_t size, const std::size_t alignment);

	void MultipleAllocation(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments);
	void MultipleFree(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments);

	void RandomAllocation(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments);
	void RandomFree(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments);
private:
	void printResults(const BenchmarkResults& results) const;

#ifndef _MSC_VER
	void setTimer(timespec& timer);
#else
	void setTimer(__int64& timer);
#endif

	void RandomAllocationAttr(const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments, std::size_t & size, std::size_t & alignment);

	double calculateElapsedTime() const;
	const BenchmarkResults buildResults(unsigned int nOperations, double elapsedTime, std::size_t memoryUsed) const;
private:
	unsigned int m_nOperations;

#ifndef _MSC_VER
	timespec m_start, m_end;
#else
	unsigned int pad_ ;			// 32 bit pad
	__int64 m_start, m_end, m_frequency ;
#endif

};

#endif /* BENCHMARK_H */