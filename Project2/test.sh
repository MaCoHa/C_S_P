#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]}")"
echo "Tests pass if no output"
echo " "
echo "Python testing"
bash ./python/run-mergesort.sh 1.txt 0
bash ./python/run-mergesort.sh 1.txt 1
bash ./python/run-quicksort.sh 1.txt 0
bash ./python/run-quicksort.sh 1.txt 1

echo "C_plus_plus testing"
bash ./c_plus_plus/setup.sh
bash ./c_plus_plus/run-mergesort.sh 1.txt 0
bash ./c_plus_plus/run-mergesort.sh 1.txt 1
bash ./c_plus_plus/run-quicksort.sh 1.txt 0
bash ./c_plus_plus/run-quicksort.sh 1.txt 1

echo "Golang testing"
bash ./golang/setup.sh
bash ./golang/run-mergesort.sh 1.txt 0
bash ./golang/run-mergesort.sh 1.txt 1
bash ./golang/run-quicksort.sh 1.txt 0
bash ./golang/run-quicksort.sh 1.txt 1


echo ""
echo "All done"