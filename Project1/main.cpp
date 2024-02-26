#include <iostream>
#include "includes/Concurrent.hpp"
#include "includes/CountThenMove.hpp"
#include "includes/utils/inputGen.hpp"
#include <iostream>
#include <math.h>

using namespace std;
vector<uint16_t> parse_threads(string threads)
{
    vector<uint16_t> threads_arr;
    string delimiter = ",";
    size_t pos = 0;
    string token;
    while ((pos = threads.find(delimiter)) != string::npos)
    {
        token = threads.substr(0, pos);
        threads_arr.push_back(stoi(token));
        threads.erase(0, pos + delimiter.length());
    }
    threads_arr.push_back(stoi(threads));
    return threads_arr;
}

int main(int argc, char *argv[])
{
    // Args: ./main <num_threads> <num_partitions> <algorithm>
    // Example ./main 1,2,3,4 4 1
    if (argc != 4)
    {
        cout << "Invalid number of arguments" << endl;
        return 1;
    }
    vector<uint16_t> threads_arr = parse_threads(argv[1]);
    int partitions = atoi(argv[2]);
    int algorithm = atoi(argv[3]);
    uint64_t tuples_size = pow(2, 24);
    vector<pair<uint64_t, uint64_t>> tuples = InputGen::gen_input(tuples_size);
    cout << partitions;
    for (int i = 0; i < threads_arr.size(); i++)
    {
        auto nr_threads = threads_arr[i];
        if (algorithm == 1)
        {
            auto result = Concurrent::run(tuples, nr_threads, partitions);
            cout << "," << result;
        }
        else if (algorithm == 2)
        {
            auto result = CountThenMove::runCount(tuples, nr_threads, partitions);
            cout << "," << result;
        }
        else
        {
            cout << "Invalid algorithm" << endl;
            return 1;
        }
    }
    cout << endl;
    return 0;
}