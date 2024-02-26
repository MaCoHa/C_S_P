#include <atomic>
#include <tuple>
#include <vector>

using namespace std;
namespace CountThenMove{
    void run(vector<pair<uint64_t, uint64_t>> tuples, const int NUM_THREADS, const int PARTITIONS);
}
