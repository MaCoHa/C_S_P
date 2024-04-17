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


time=$(date +"%Y-%m-%d-%H:%M:%S")
mkdir $time
mkdir "data"

million_elements=("2" "4" "8" "16" "32" "64")
languages=("python" "golang" "c_plus_plus") # Same as folder name
algorithms=("mergesort") # Same as bash script name excluding "run-" prefix (Ex. run-mergesort.sh = mergesort)
SECONDS=0

# Setup
for language in "${languages[@]}"
do
    bash ./$language/setup.sh
done

for i in 1 2 3 4 5 6 7 8
do
    [ ! -d "./tmp-data" ] && mkdir ./tmp-data
    for element_amount in "${million_elements[@]}"
    do
        echo "Making data for $element_amount"
        go run ./input_gen/main.go $element_amount > ./tmp-data/$element_amount.txt
    done

    path="$time/test-$i"
    mkdir $path
    for language in "${languages[@]}"
    do
        mkdir $path/$language
        for algorithm in "${algorithms[@]}"
        do  
            folder="$path/$language/$algorithm"
            mkdir $folder
            timingsBaseFile="$folder/timings-base.csv"
            cachemissBaseFile="$folder/perf-cache-miss-base.csv"
            dTLBBaseFile="$folder/perf-dTLB-misses-base.csv"
            for element_amount in "${million_elements[@]}"
            do
                echo "Creating base case for $language with $element_amount million elements"
                perf stat -o output.txt -e cache-misses,dTLB-load-misses bash ./$language/run-$algorithm.sh $element_amount.txt 1
                grep -E 'cache-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n'   >> $cachemissBaseFile
                grep -E 'dTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n' >> $dTLBBaseFile
                grep -A 1 "seconds time elapsed" output.txt | tr -d 'seconds time elapsed' >> $timingsBaseFile
            done
        done
    done

    #Cleanup
    rm output.txt
done

for i in 1 2 3 4 5 6 7 8
do
    path="$time/test-$i"
    mkdir $path
    for language in "${languages[@]}"
    do
        mkdir $path/$language
        for algorithm in "${algorithms[@]}"
        do        
            folder="$path/$language/$algorithm"
            mkdir $folder
            timingsFile="$folder/timings.csv"
            cachemissFile="$folder/perf-cache-miss.csv"
            dTLBFile="$folder/perf-dTLB-misses.csv"
            for element_amount in "${million_elements[@]}"
            do
                echo "Running $language with $element_amount million elements"
                perf stat -o output.txt -e cache-misses,dTLB-load-misses bash ./$language/run-$algorithm.sh $element_amount.txt 0
                grep -E 'cache-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n'   >> $cachemissFile
                grep -E 'dTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n' >> $dTLBFile
                grep -A 1 "seconds time elapsed" output.txt | tr -d 'seconds time elapsed' >> $timingsFile
            done
        done
    done
    # Cleanup
    rm ./tmp-data
    rm output.txt

done

duration=$SECONDS
minutes=$((duration / 60))
seconds=$((duration % 60))
hours=$((minutes / 60))
minutes=$((minutes % 60))

echo "$hours hours, $minutes minutes, and $seconds seconds elapsed." > $time/meta.txt
