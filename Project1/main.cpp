#include <iostream>
#include "Concurrent.cpp"
#include "Count_then_move.cpp"
#include "utils/inputGen.cpp"
#include "includes/Concurrent.hpp"
#include "includes/Count_then_move.hpp"
#include "includes/utils/inputGen.hpp"
#include <math.h>

using namespace std;
int main(int argc, char *argv[]) 
{
    vector<pair<uint64_t, uint64_t>> tuples = InputGen::gen_input(pow(2, 24));
    //Concurrent::run(tuples, 6, 4);
    CountThenMove::run(tuples, 6, 4);
    return 0;
}