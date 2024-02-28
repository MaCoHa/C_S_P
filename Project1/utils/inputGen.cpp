/*
    input
    should be a list of tuples containing an partition key and a payload.
    partition keys are uniqe

    Partitioning Key:  0x3A7F9D2B1E6C8F45 = PK
    Payload:           0xAB1234567890DEFF = PL

    input format list of tuples
    [(PK,PL),(PK1,PL1),(PKn,PLn)]






 */
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <list>
#include <algorithm>
#include <random>

auto rng = std::default_random_engine{};
using namespace std;
namespace InputGen
{

    uint64_t rand_64bit()
    {
        return (((uint64_t)rand()) << 32) | rand();
    }

    vector<pair<uint64_t, uint64_t>> gen_input(int n)
    {
        vector<pair<uint64_t, uint64_t>> result(n);
        vector<bool> keys(n, false);
        // Generate tuples
        for (uint64_t i = 0; i < n; ++i)
        {
            // Gen key
            // check key dosent exsits
            // gen payload
            uint64_t payload = rand_64bit();

            // add to results

            result[i] = make_pair(i, payload);
        }

        shuffle(begin(result), end(result), rng);
        return result;
    }

}
