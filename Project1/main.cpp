#include <iostream>
#include "includes/Concurrent.hpp"
#include "includes/utils/inputGen.hpp"

using namespace std;
int main(int argc, char *argv[]) 
{
    vector<pair<uint64_t, uint64_t>> tuples = InputGen::gen_input(400);
    Concurrent::run(tuples, 4, 5);
    return 0;
}