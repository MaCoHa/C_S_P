#!/bin/bash
cmake CMakeLists.txt
make

# Define an array of variables
hash_bits=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10" "11" "12" "13" "14" "15" "16" "17" "18")
num_threads=("1" "2" "4" "8" "16" "32")
#num_threads="1,2"

time=$(date +"%Y-%m-%d-%H:%M:%S")
mkdir $time
SECONDS=0
for i in 1 2 3 4 5 6 7 8
do
    path="$time/test-$i"
    mkdir $path
    concurrentFolder="$path/concurrent-no-affinity"
    concurrentAffinityFolder="$path/concurrent-with-affinity"
    countthenmoveFolder="$path/countthenmove-no-affinty"
    countthenmoveAffinityFolder="$path/countthenmove-with-affinty"
    
    folders=($concurrentFolder $concurrentAffinityFolder $countthenmoveFolder $countthenmoveAffinityFolder)
    for folder in "${folders[@]}"
    do
        mkdir $folder
        echo ",1,2,4,8,16,32" > $folder/timings.csv;
        echo ",1,2,4,8,16,32" > $folder/perf-cache-miss.csv;
        echo ",1,2,4,8,16,32" > $folder/perf-dTLB.csv;
        echo ",1,2,4,8,16,32" > $folder/perf-iTLB.csv;
    done
    
    # Concurrent
    for partitions in "${hash_bits[@]}"
    do
        concurrentFile="$concurrentFolder/timings.csv"
        cachemissFile="$concurrentFolder/perf-cache-miss.csv"
        dTLBFile="$concurrentFolder/perf-dTLB.csv"
        iTLFFile="$concurrentFolder/perf-iTLB.csv"
        echo -n $partitions >> $concurrentFile
        echo -n $partitions >> $cachemissFile
        echo -n $partitions >> $dTLBFile
        echo -n $partitions >> $iTLFFile
        for threads in "${num_threads[@]}"
        do
            echo -n "," >> $cachemissFile
            echo -n "," >> $dTLBFile
            echo -n "," >> $iTLFFile
            echo "Running Concurrent with : $partitions Partitions and $threads threads"
            perf stat -o output.txt -e cache-misses,dTLB-load-misses,iTLB-load-misses ./main $threads $partitions 1 0 >> $concurrentFile
            grep -E 'cache-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n'   >> $cachemissFile
            grep -E 'dTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n' >> $dTLBFile
            grep -E 'iTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | sed 's/,//' | tr -d '\n' >> $iTLFFile
        done
        echo "" >> $concurrentFile
        echo "" >> $cachemissFile
        echo "" >> $dTLBFile
        echo "" >> $iTLFFile
    done
    Concurrent with affinity
    for partitions in "${hash_bits[@]}"
    do
        currentFile="$concurrentAffinityFolder/timings.csv"
        cachemissFile="$concurrentAffinityFolder/perf-cache-miss.csv"
        dTLBFile="$concurrentAffinityFolder/perf-dTLB.csv"
        iTLFFile="$concurrentAffinityFolder/perf-iTLB.csv"
        echo -n $partitions >> $currentFile
        echo -n $partitions >> $cachemissFile
        echo -n $partitions >> $dTLBFile
        echo -n $partitions >> $iTLFFile
        for threads in "${num_threads[@]}"
        do
            echo -n "," >> $cachemissFile
            echo -n "," >> $dTLBFile
            echo -n "," >> $iTLFFile
            echo "Running Concurrent with affinty : $partitions Partitions and $threads threads"
            perf stat -o output.txt -e cache-misses,dTLB-load-misses,iTLB-load-misses ./main $threads $partitions 1 1 >> $currentFile
            grep -E 'cache-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n'   >> $cachemissFile
            grep -E 'dTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n' >> $dTLBFile
            grep -E 'iTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | sed 's/,//' | tr -d '\n' >> $iTLFFile
        done
        echo "" >> $currentFile
        echo "" >> $cachemissFile
        echo "" >> $dTLBFile
        echo "" >> $iTLFFile
    done
    #CountThenMove 
    for partitions in "${hash_bits[@]}"
    do
        concurrentFile="$countthenmoveFolder/timings.csv"
        cachemissFile="$countthenmoveFolder/perf-cache-miss.csv"
        dTLBFile="$countthenmoveFolder/perf-dTLB.csv"
        iTLFFile="$countthenmoveFolder/perf-iTLB.csv"
        echo -n $partitions >> $concurrentFile
        echo -n $partitions >> $cachemissFile
        echo -n $partitions >> $dTLBFile
        echo -n $partitions >> $iTLFFile
        for threads in "${num_threads[@]}"
        do
            echo -n "," >> $cachemissFile
            echo -n "," >> $dTLBFile
            echo -n "," >> $iTLFFile
            echo "Running CountThenMove with : $partitions Partitions and $threads threads"
            perf stat -o output.txt -e cache-misses,dTLB-load-misses,iTLB-load-misses ./main $threads $partitions 2 0 >> $concurrentFile
            grep -E 'cache-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n'   >> $cachemissFile
            grep -E 'dTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n' >> $dTLBFile
            grep -E 'iTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | sed 's/,//' | tr -d '\n' >> $iTLFFile
        done
        echo "" >> $concurrentFile
        echo "" >> $cachemissFile
        echo "" >> $dTLBFile
        echo "" >> $iTLFFile
    done
    #CountThenMove with affinity
    for partitions in "${hash_bits[@]}"
    do
        currentFile="$countthenmoveAffinityFolder/timings.csv"
        cachemissFile="$countthenmoveAffinityFolder/perf-cache-miss.csv"
        dTLBFile="$countthenmoveAffinityFolder/perf-dTLB.csv"
        iTLFFile="$countthenmoveAffinityFolder/perf-iTLB.csv"
        echo -n $partitions >> $currentFile
        echo -n $partitions >> $cachemissFile
        echo -n $partitions >> $dTLBFile
        echo -n $partitions >> $iTLFFile
        for threads in "${num_threads[@]}"
        do
            echo -n "," >> $cachemissFile
            echo -n "," >> $dTLBFile
            echo -n "," >> $iTLFFile
            echo "Running CountThenMove with affinity: $partitions Partitions and $threads threads"
            perf stat -o output.txt -e cache-misses,dTLB-load-misses,iTLB-load-misses ./main $threads $partitions 2 1 >> $currentFile
            grep -E 'cache-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n'   >> $cachemissFile
            grep -E 'dTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | tr -d ',' | tr -d '\n' >> $dTLBFile
            grep -E 'iTLB-load-misses' output.txt | sed 's/[^0-9,]//g' | sed 's/,//' | tr -d '\n' >> $iTLFFile
        done
        echo "" >> $currentFile
        echo "" >> $cachemissFile
        echo "" >> $dTLBFile
        echo "" >> $iTLFFile
    done
    
done
duration=$SECONDS
minutes=$((duration / 60))
seconds=$((duration % 60))
hours=$((minutes / 60))
minutes=$((minutes % 60))

echo "$hours hours, $minutes minutes, and $seconds seconds elapsed." > $time/meta.txt