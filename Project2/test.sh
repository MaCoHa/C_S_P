#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]}")"
echo "Creating test data"
[ ! -d "./tmp-data" ] && mkdir ./tmp-data
go run ./input_gen/main.go 32 1 > ./tmp-data/test.txt

echo "Tests pass if no output"
echo " "

echo "C_plus_plus testing"
bash ./c_plus_plus/setup.sh
time bash ./c_plus_plus/run-mergesort.sh test.txt 0
#time bash ./c_plus_plus/run-mergesort.sh test.txt 1
time bash ./c_plus_plus/run-quicksort.sh test.txt 0
#time bash ./c_plus_plus/run-quicksort.sh test.txt 1

echo "Golang testing"
bash ./golang/setup.sh
time bash ./golang/run-mergesort.sh test.txt 0
#time bash ./golang/run-mergesort.sh test.txt 1
time bash ./golang/run-quicksort.sh test.txt 0
#time bash ./golang/run-quicksort.sh test.txt 1

echo "Python testing"
time bash ./python/run-mergesort.sh test.txt 0
#time bash ./python/run-mergesort.sh test.txt 1
time bash ./python/run-quicksort.sh test.txt 0
#time bash ./python/run-quicksort.sh test.txt 1

echo "Cleanup"
rm ./tmp-data/test.txt
echo ""
echo "All done"