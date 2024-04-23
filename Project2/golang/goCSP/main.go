package main

import (
	"goCSP/mergesort"
	"goCSP/quicksort"
	"log"
	"os"
	"strconv"
	"strings"
)

func validate(A []int, size int) {
	sorted := true
	for i := 1; i < size; i++ {
		if A[i] < A[i-1] {
			sorted = false
			break
		}
	}
	log.Printf("The list is sorted: %t", sorted)
}

func Slice_Atoi(strArr []string) ([]int, error) {
	var str string
	var i int
	var err error

	iArr := make([]int, 0, len(strArr))
	for _, str = range strArr {
		i, err = strconv.Atoi(str)
		if err != nil {
			return nil, err
		}
		iArr = append(iArr, i)
	}
	return iArr, nil
}

func main() {

	args := os.Args
	if len(args) <= 3 {
		log.Fatalln("Not enough parameters. Arguments: algorithm fileName isBaseCase")
	}
	algorithm := args[1]
	fileName := args[2]
	isBaseCase := args[3] == "1" || strings.ToLower(args[3]) == "true"

	data, err := os.ReadFile("../../tmp-data/" + fileName)
	if err != nil {
		log.Fatalf("failed reading data from file: %s", err)
	}

	strArr := strings.Split(string(data), " ")

	iArr, err := Slice_Atoi(strArr)
	if err != nil {
		log.Fatalln("Slice_Atoi failed: ", err)
		return
	}
	if !isBaseCase {
		if algorithm == "mergesort" {
			mergesort.MergeSort(iArr)
		} else if algorithm == "quicksort" {
			quicksort.QuickSort(iArr)
		} else {
			log.Fatalln("Unsupported algorithm in python: " + algorithm)
		}
	}
	//validate(iArr, len(iArr))
}
