#include <atomic>

namespace Concurrent{
    void task(std::vector<std::pair<uint64_t, uint64_t>> &tuples, std::vector<std::vector<std::pair<uint64_t, uint64_t>>> &buffers, std::vector<std::atomic_int> &partition_indexes, const int START, const int END);
    long long run(std::vector<std::pair<uint64_t, uint64_t>> tuples, const int NUM_THREADS, const int PARTITIONS);
}