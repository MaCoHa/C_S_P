
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>
#include <tuple>
#include <thread>
#include <atomic>

using namespace std;
namespace CountThenMove
{
    
    void count(vector<pair<uint64_t, uint64_t>> &tuples, vector<int> &keys, const int START, const int END, const int PARTITIONS)
    {
        for (int i = START; i < END; i++)
        {
            // Read tuple at i
            pair<uint64_t, uint64_t> tuple = tuples[i];

            // Find hash index
            int key = get<0>(tuple) % PARTITIONS;


            keys[key]++;
        }
    }

    void move(vector<pair<uint64_t, uint64_t>> &tuples, vector<pair<uint64_t, uint64_t>> &buffer, vector<int> key_indexs, int START, int END, int PARTITIONS)
    {
        for (int i = START; i < END; i++)
        {
            // Read tuple at i
            pair<uint64_t, uint64_t> tuple = tuples[i];

            // Find hash index
            int key = get<0>(tuple) % PARTITIONS;
            buffer[key_indexs[key]] = tuple;
            key_indexs[key]++;

        }
    }


    void run(vector<pair<uint64_t, uint64_t>> tuples, const int NUM_THREADS, const int PARTITIONS)
    {

        vector<vector<int>> thread_key_count(NUM_THREADS, vector<int>(PARTITIONS));
        // Task 1 spin theards and count number of keys
        thread threads[NUM_THREADS];

        const int TUPLES_PER_THREAD = tuples.size() / NUM_THREADS;
        int start = 0;
        int end = TUPLES_PER_THREAD;
        for (int i = 0; i < NUM_THREADS; ++i)
        {
            if (i == NUM_THREADS-1){
                end = tuples.size();
            }
            cout << " START: " << start << " END: " << end << endl;
            threads[i] = thread(count, ref(tuples), ref(thread_key_count[i]), start, end, PARTITIONS);
            start = end;
            end = start + TUPLES_PER_THREAD;
        };
        vector<int> key_count(PARTITIONS);
        for (int i = 0; i < NUM_THREADS; i++)
        {
            threads[i].join();
            cout << "Thread " << i << endl;
            for (int j = 0; j < PARTITIONS; j++) {
                key_count[j] += thread_key_count[i][j];
                cout << thread_key_count[i][j] << " ";
            }
            cout << endl;
        };

        // Task 2 calc each threads count priviliges and assgin them
        
        vector<int> key_indexes(PARTITIONS);
        for (int j = 1; j < PARTITIONS; j++) 
            key_indexes[j] = key_indexes[j-1]+key_count[j-1];
        start = 0;
        end = TUPLES_PER_THREAD;
        vector<pair<uint64_t, uint64_t>> output_buffer(tuples.size());
        for (int i = 0; i < NUM_THREADS; ++i)
        {
            //subtask 1 start thread
            if (i == NUM_THREADS-1){
                end = tuples.size();
            }
            threads[i] = thread(move, ref(tuples), ref(output_buffer), key_indexes, start, end, PARTITIONS);
            //subtask 2 increase key indexes
            for (int j = 0; j < PARTITIONS; j++) 
                key_indexes[j] += thread_key_count[i][j];
            
            start = end;
            end = start + TUPLES_PER_THREAD;
        };
        for (int i = 0; i < NUM_THREADS; i++)
        { 
            threads[i].join();
        };

        for (int i = 0; i < output_buffer.size(); i++){
            pair<uint64_t, uint64_t> par = output_buffer[i];
            if(par.first == 0){
                cout << "Failed at index: " << i << endl;
            }
        }
        
        // Task 3 spin up new threads then each thread writes/moves the values to the assgined spots 
    }
}
