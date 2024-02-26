
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>
#include <tuple>
#include <thread>
#include <atomic>
 
#include "includes/Concurrent.hpp"

using namespace std;
namespace Concurrent{


    /* 
        hash = [ref1,1[],refn,1[]]
        list [atomic(ref1,1),atomic(refn,1)]

        add value to ref1,1
        update atomic get_and_inc, update hash ref1,1

        hash = [ref1,2[1],refn,1[]]
        list [atomic(ref1,2),atomic(refn,1)]
    
    */

    void task(vector<pair<uint64_t, uint64_t>> &tuples, vector<vector<pair<uint64_t, uint64_t>>> &buffers, vector<atomic_int> &partition_indexes, const int START, const int END){
      
        for (int i = START; i < END; i++)
        {
            // Read tuple at i
            pair<uint64_t, uint64_t> tuple = tuples[i];

            // Find hash index
            uint64_t key = get<0>(tuple);
            int partition = key%partition_indexes.size();

            uint64_t hash_index = partition_indexes[partition].fetch_add(1);

            // insert into hash index;
            buffers[partition][hash_index] = tuple;

        }
        
    }
    
    void run(vector<pair<uint64_t, uint64_t>> tuples, const int NUM_THREADS, const int PARTITIONS){

        /* 
            We expect data to be uniformly distributede such that each buffer would store tuples.size / PARTITIONS
            but as a safety measure we expand the buffer with 1.5.
        */
        vector<vector<pair<uint64_t, uint64_t>>> buffers(PARTITIONS, vector<pair<uint64_t, uint64_t>>((tuples.size()/PARTITIONS)*1.1));
        vector<atomic_int> partition_indexes(PARTITIONS);
        
        thread threads[NUM_THREADS];
        

        const int TUPLES_PER_THREAD = tuples.size()/NUM_THREADS;
        int start = 0;
        int end = TUPLES_PER_THREAD;
        for (int i = 0; i < NUM_THREADS; ++i)
        {
            if (i == NUM_THREADS-1){
                end = tuples.size();
            }
            cout << " START: " << start << " END: " << end << endl;

            threads[i] = thread(task, ref(tuples), ref(buffers), ref(partition_indexes), start, end); 
            start = end;
            end = start + TUPLES_PER_THREAD;

        };
        
        for (int i = 0; i < NUM_THREADS; i++)
        { 
            threads[i].join();
        };

            cout << " partition_indexes 0: " << partition_indexes[0] << endl;
            const auto first = buffers[0][partition_indexes[0]-1];
            const auto second = buffers[0][partition_indexes[0]];
            cout << " buffer 0: " << first.first << endl;
            cout << " buffer 0: " << second.first << endl;


            cout << " partition_indexes 1: " << partition_indexes[1] << endl;
            const auto first1 = buffers[1][partition_indexes[1]-1];
            const auto second1 = buffers[1][partition_indexes[1]];
            cout << " buffer 1: " << first1.first << endl;
            cout << " buffer 1: " << second1.first << endl;

            cout << " partition_indexes 2: " << partition_indexes[2] << endl;
            const auto first2 = buffers[2][partition_indexes[2]-1];
            const auto second2 = buffers[2][partition_indexes[2]];
            cout << " buffer 2: " << first2.first << endl;
            cout << " buffer 2: " << second2.first << endl;

            cout << " partition_indexes 3: " << partition_indexes[3] << endl;
            const auto first3 = buffers[3][partition_indexes[3]-1];
            const auto second3 = buffers[3][partition_indexes[3]];
            cout << " buffer 3: " << first3.first << endl;
            cout << " buffer 3: " << second3.first << endl;




        

        
    }



}
