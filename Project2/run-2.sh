#!/bin/bash

# Psudo code:
# --------
# setup python
# setup c#
# setup C
#
# for 1-8:
#   for [2,4,8,16,32,64]:
#       Run data gen
#
#    Run python test for [2,4,8,16,32,64]
#    Run C# test for [2,4,8,16,32,64]
#    Run C test for [2,4,8,16,32,64]
#
#   Cleanup
#
# -------
cd "$(dirname "${BASH_SOURCE[0]}")"

time=$(date +"%Y-%m-%d-%H:%M:%S")
[ ! -d "./data" ] && mkdir ./data
mkdir data/$time

languages=("c_plus_plus" "golang" "pypy" "cpython")
algorithms=("mergesort" "quicksort") # Same as bash script name excluding "run-" prefix (Ex. run-mergesort.sh = mergesort)
dataTypes=("1" "2")
SECONDS=0

# Setup
for language in "${languages[@]}"
do
    bash ./$language/setup.sh
done

[ ! -d "./tmp-data" ] && mkdir ./tmp-data
for dataType in "${dataTypes[@]}"
do
    echo "Making data $dataType for 4 million"
    go run ./input_gen/main.go 4 $dataType > ./tmp-data/4-$dataType.txt
done

path="data/$time"
mkdir $path
for language in "${languages[@]}"
do
    mkdir $path/$language
    for algorithm in "${algorithms[@]}"
    do
        folder="$path/$language/$algorithm"
        mkdir $folder
        echo "Creating base case for $language with 4 million elements"
        perf stat -o $folder/base.txt -e cycles,instructions,iTLB-load-misses bash ./$language/run-$algorithm.sh 4-1.txt 1
        
    done
done

mkdir $path
for dataType in "${dataTypes[@]}"
do
    for language in "${languages[@]}"
    do
        [ ! -d $path/$language ] && mkdir $path/$language
        for algorithm in "${algorithms[@]}"
        do
            folder="$path/$language/$algorithm"
            echo $folder
            [ ! -d $folder ] && mkdir $folder
            echo "Running $algorithm with $language and $element_amount million elements for datatype: $dataType"
            perf stat -o $folder/output.txt -e cycles,instructions,iTLB-load-misses bash ./$language/run-$algorithm.sh 4-$dataType.txt 0
            
        done
    done
done

# Cleanup
rm -r ./tmp-data

duration=$SECONDS
minutes=$((duration / 60))
seconds=$((duration % 60))
hours=$((minutes / 60))
minutes=$((minutes % 60))

echo "$hours hours, $minutes minutes, and $seconds seconds elapsed." > data/$time/meta.txt
