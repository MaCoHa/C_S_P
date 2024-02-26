#!/bin/bash

# Define an array of variables
my_array=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10" "11" "12" "13" "14" "15" "16" "17" "18")

cat test_log.csv
echo "1,2,4,8,16,32" > test-gen.csv; \

# Loop through the array
for var in "${my_array[@]}"
do
    echo "Running Concurrent with : $var Partitions"
    ./main 1,2,4,8,16,32 $var 1
    #<arg1> <arg2> <arg3> > test-gen.csv
    break;
done

# Loop through the array
for var in "${my_array[@]}"
do
    echo "Running Cound_then_move with : $var Partitions"
    ./main 1,2,4,8,16,32 $var 2
    break;

done
