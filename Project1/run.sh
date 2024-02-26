#!/bin/bash

# Define an array of variables
my_array=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10" "11" "12" "13" "14" "15" "16" "17" "18")
num_threads="1,2,4,8,16,32"
#num_threads="1,2"

time=$(date +"%Y-%m-%d-%T")
concurrentFile="concurrent-test-$time.csv"
countthenmoveFile="countthenmove-test-$time.csv"

echo ",$num_threads" > $concurrentFile;
echo ",$num_threads" > $countthenmoveFile;

# Loop through the array
for var in "${my_array[@]}"
do
    echo "Running Concurrent with : $var Partitions"
    ./main $num_threads $var 1 >> $concurrentFile
    #<arg1> <arg2> <arg3> > test-gen.csv
    break
done

# Loop through the array
for var in "${my_array[@]}"
do
    echo "Running Cound_then_move with : $var Partitions"
    ./main $num_threads $var 2 >> $countthenmoveFile

done
