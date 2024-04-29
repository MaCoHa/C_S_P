#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]}")"
echo "Creating test data"
[ ! -d "./tmp-data" ] && mkdir ./tmp-data
go run ./input_gen/main.go 1 1 > ./tmp-data/test.txt

echo "Tests pass if no output"
echo " "
echo "Python testing"
bash ./python/run-mergesort.sh test.txt 0
bash ./python/run-mergesort.sh test.txt 1
bash ./python/run-quicksort.sh test.txt 0
bash ./python/run-quicksort.sh test.txt 1

echo "C_plus_plus testing"
bash ./c_plus_plus/setup.sh
bash ./c_plus_plus/run-mergesort.sh test.txt 0
bash ./c_plus_plus/run-mergesort.sh test.txt 1
bash ./c_plus_plus/run-quicksort.sh test.txt 0
bash ./c_plus_plus/run-quicksort.sh test.txt 1

echo "Golang testing"
bash ./golang/setup.sh
bash ./golang/run-mergesort.sh test.txt 0
bash ./golang/run-mergesort.sh test.txt 1
bash ./golang/run-quicksort.sh test.txt 0
bash ./golang/run-quicksort.sh test.txt 1

echo "Cleanup"
rm ./tmp-data/test.txt
echo ""
echo "All done"
