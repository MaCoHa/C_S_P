#include <atomic>
#include <vector>

namespace CountThenMove{
    void run(std::vector<std::pair<uint64_t, uint64_t>> tuples, const int NUM_THREADS, const int PARTITIONS);
}