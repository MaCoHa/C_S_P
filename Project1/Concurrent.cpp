
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>
#include <tuple>
#include <thread>
 

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
        /*for (int i = START; i <= END; i++)
        {
            
        }*/
        cout << "Tuple size: " << tuples.size() << " START: " << START << " END: " << END << endl;
        
    }
    
    void run(vector<pair<uint64_t, uint64_t>> tuples, const int NUM_THREADS, const int PARTITIONS){

        /* 
            We expect data to be uniformly distributede such that each buffer would store tuples.size / PARTITIONS
            but as a safety measure we expand the buffer with 1.5.
        */
        vector<vector<pair<uint64_t, uint64_t>>> buffers(PARTITIONS, vector<pair<uint64_t, uint64_t>>((tuples.size()/PARTITIONS)*1.5));
        vector<atomic_int> partition_indexes(PARTITIONS);
        
        thread threads[NUM_THREADS];
        

        const int TUPLES_PER_THREAD = tuples.size()/NUM_THREADS;
        int start = 0;
        int end = TUPLES_PER_THREAD;
        for (int i = 0; i < NUM_THREADS; ++i)
        {
            threads[i] = thread(task, ref(tuples), ref(buffers), ref(partition_indexes), start, end); 
            start = end+1;
            end = start + TUPLES_PER_THREAD;
        };
        
        for (int i = 0; i < NUM_THREADS; i++)
        { 
            threads[i].join();
        };
    }



}
