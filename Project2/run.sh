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

million_elements=("2" "4" "8" "16" "32") #Missing 64
languages=("golang" "c_plus_plus" "python") # Same as folder name
algorithms=("mergesort" "quicksort") # Same as bash script name excluding "run-" prefix (Ex. run-mergesort.sh = mergesort)
dataTypes=("1" "2" "3" "4")
SECONDS=0

# Setup
for language in "${languages[@]}"
do
    bash ./$language/setup.sh
done

[ ! -d "./tmp-data" ] && mkdir ./tmp-data
#for element_amount in "${million_elements[@]}"
#do
#    for dataType in "${dataTypes[@]}"
#    do
##        echo "Making data $dataType for $element_amount million"
 #       go run ./input_gen/main.go $element_amount $dataType > ./tmp-data/$element_amount-$dataType.txt
#    done
#done

path="data/$time/base"
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
        baseCounter=1
        for element_amount in "${million_elements[@]}"
        do
            if [ "${counter}" != "1" ]
            then
                echo -n "," >> $timingsBaseFile
                echo -n "," >> $cachemissBaseFile
                echo -n "," >> $dTLBBaseFile
            fi
            counter=$((counter +1))
            echo "Creating base case for $language with $element_amount million elements"
            perf stat -o output.txt -e cache-misses,dTLB-load-misses bash ./$language/run-$algorithm.sh $element_amount-1.txt 1
            grep -E 'cache-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n'   >> $cachemissBaseFile
            grep -E 'dTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n' >> $dTLBBaseFile
            grep -A 1 "seconds time elapsed" output.txt | tr -d 'seconds time elapsed' | tr -d '\n' >> $timingsBaseFile
        done
        echo "" >> $timingsBaseFile
        echo "" >> $cachemissBaseFile
        echo "" >> $dTLBBaseFile
    done
done

#Cleanup
rm output.txt

for i in 1 2 3 4 5 6 7 8
do
    path="data/$time/test-$i"
    mkdir $path
    for dataType in "${dataTypes[@]}"
    do
        counter=1
        for element_amount in "${million_elements[@]}"
        do
            for language in "${languages[@]}"
            do
                [ ! -d $path/$language ] && mkdir $path/$language
                for algorithm in "${algorithms[@]}"
                do
                    folder="$path/$language/$algorithm"
                    echo $folder
                    [ ! -d $folder ] && mkdir $folder
                    timingsFile="$folder/timings-$dataType.csv"
                    cachemissFile="$folder/perf-cache-miss-$dataType.csv"
                    dTLBFile="$folder/perf-dTLB-misses-$dataType.csv"
                    if [ "${counter}" != "1" ]
                    then
                        echo -n "," >> $timingsFile
                        echo -n "," >> $cachemissFile
                        echo -n "," >> $dTLBFile
                    fi
                    
                    echo "Running $algorithm with $language and $element_amount million elements for datatype: $datatype"
                    perf stat -o output.txt -e cache-misses,dTLB-load-misses bash ./$language/run-$algorithm.sh $element_amount-$dataType.txt 0
                    grep -E 'cache-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n'   >> $cachemissFile
                    grep -E 'dTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n' >> $dTLBFile
                    grep -A 1 "seconds time elapsed" output.txt | tr -d 'seconds time elapsed' | tr -d '\n' >> $timingsFile
                done
            done
            counter=$((counter +1))
        done
    done
    # Cleanup
    rm -r ./tmp-data
    rm output.txt
done

duration=$SECONDS
minutes=$((duration / 60))
seconds=$((duration % 60))
hours=$((minutes / 60))
minutes=$((minutes % 60))

echo "$hours hours, $minutes minutes, and $seconds seconds elapsed." > data/$time/meta.txt
