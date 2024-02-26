
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>
#include <tuple>
#include <thread>
#include <atomic>
#include <chrono>

#include "includes/Concurrent.hpp"

using namespace std;
using namespace std::chrono;
namespace Concurrent
{

    /*
        hash = [ref1,1[],refn,1[]]
        list [atomic(ref1,1),atomic(refn,1)]

        add value to ref1,1
        update atomic get_and_inc, update hash ref1,1

        hash = [ref1,2[1],refn,1[]]
        list [atomic(ref1,2),atomic(refn,1)]

    */

    void task(vector<pair<uint64_t, uint64_t>> &tuples, vector<vector<pair<uint64_t, uint64_t>>> &buffers, vector<atomic_int> &partition_indexes, const int START, const int END)
    {

        for (int i = START; i < END; i++)
        {
            // Read tuple at i
            pair<uint64_t, uint64_t> tuple = tuples[i];

            // Find hash index
            uint64_t key = get<0>(tuple);
            int partition = key % partition_indexes.size();

            uint64_t hash_index = partition_indexes[partition].fetch_add(1);

            // insert into hash index;
            buffers[partition][hash_index] = tuple;
        }
    }

    long long run(vector<pair<uint64_t, uint64_t>> tuples, const int NUM_THREADS, const int PARTITIONS)
    {

        /*
            We expect data to be uniformly distributede such that each buffer would store tuples.size / PARTITIONS
            but as a safety measure we expand the buffer with 1.5.
        */
        vector<vector<pair<uint64_t, uint64_t>>> buffers(PARTITIONS, vector<pair<uint64_t, uint64_t>>((tuples.size() / PARTITIONS) * 1.1));
        vector<atomic_int> partition_indexes(PARTITIONS);

        thread threads[NUM_THREADS];

        const int TUPLES_PER_THREAD = tuples.size() / NUM_THREADS;
        int start = 0;
        int end = TUPLES_PER_THREAD;
        auto timer_start = high_resolution_clock::now();
        for (int i = 0; i < NUM_THREADS; ++i)
        {
            if (i == NUM_THREADS - 1)
            {
                end = tuples.size();
            }

            threads[i] = thread(task, ref(tuples), ref(buffers), ref(partition_indexes), start, end);
            start = end;
            end = start + TUPLES_PER_THREAD;
        };

        for (int i = 0; i < NUM_THREADS; i++)
        {
            threads[i].join();
        };
        auto timer_end = high_resolution_clock::now();
 
        auto time = duration_cast<milliseconds>(timer_end-timer_start).count();
        //(16777216/(480/1000))*(10^-6)
        return static_cast<double>(tuples.size()) / (time / 1000.0) * 1e-6;
    }

}
