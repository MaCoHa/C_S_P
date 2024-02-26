#include "includes/Concurrent.hpp"
#include "includes/CountThenMove.hpp"
#include "includes/utils/inputGen.hpp"
#include <iostream>
#include <math.h>

using namespace std;
int main(int argc, char *argv[]) 
{
    vector<std::pair<uint64_t, uint64_t>> tuples = InputGen::gen_input(pow(2, 24));
    //Concurrent::run(tuples, 6, 4);
    CountThenMove::runCount(tuples, 6, 4);
    return 0;
}