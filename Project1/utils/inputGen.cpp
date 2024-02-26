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

using namespace std;
namespace InputGen
{

    uint64_t rand_64bit()
    {
        return (((uint64_t)rand()) << 32) | rand();
    }

    vector<pair<uint64_t, uint64_t>> gen_input(int n)
    {
        vector<pair<uint64_t, uint64_t>> result;
        set<uint64_t> keys;
        // Generate tuples
        for (int i = 0; i < n; ++i)
        {

            // Gen key
            uint64_t key = rand_64bit();

            // check key dosent exsits

            while (keys.find(key) != keys.end())
            {
                key = rand_64bit();
            }
            keys.insert(key);

            // gen payload
            uint64_t payload = rand_64bit();

            // add to results

            result.push_back(make_pair(key, payload));
        }

        return result;
    }


}