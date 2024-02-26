#include <atomic>

namespace CountThenMove{
    void countTask(std::vector<std::pair<uint64_t, uint64_t>> &tuples, std::vector<int> &keys, const int START, const int END, const int PARTITIONS);
    void moveTask(std::vector<std::pair<uint64_t, uint64_t>> &tuples, std::vector<std::pair<uint64_t, uint64_t>> &buffer, std::vector<int> key_indexs, const int START, const int END, int PARTITIONS);
    void runCount(std::vector<std::pair<uint64_t, uint64_t>> tuples, const int NUM_THREADS, const int PARTITIONS);
}