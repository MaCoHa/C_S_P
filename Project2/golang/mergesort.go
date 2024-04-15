package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func Slice_Atoi(strArr []string) ([]int, error) {
	// NOTE:  Read Arr as Slice as you like
	var str string // O
	var i int      // O
	var err error  // O

	iArr := make([]int, 0, len(strArr))
	for _, str = range strArr {
		i, err = strconv.Atoi(str)
		if err != nil {
			return nil, err // O
		}
		iArr = append(iArr, i)
	}
	return iArr, nil
}

func merge(array []int, left int, mid int, right int) {
	subArrayOne := mid - left + 1
	subArrayTwo := right - mid

	// Create temp arrays
	leftArray := make([]int, subArrayOne)
	rightArray := make([]int, subArrayTwo)

	// Copy data to temp arrays leftArray[] and rightArray[]
	for i := 0; i < subArrayOne; i++ {
		leftArray[i] = array[left+i]
	}
	for j := 0; j < subArrayTwo; j++ {
		rightArray[j] = array[mid+1+j]
	}

	indexOfSubArrayOne := 0
	indexOfSubArrayTwo := 0
	indexOfMergedArray := left

	// Merge the temp arrays back into array[left..right]
	for indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo {
		if leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo] {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne]
			indexOfSubArrayOne++
		} else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo]
			indexOfSubArrayTwo++
		}
		indexOfMergedArray++
	}

	// Copy the remaining elements of left[], if there are any
	for indexOfSubArrayOne < subArrayOne {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne]
		indexOfSubArrayOne++
		indexOfMergedArray++
	}

	// Copy the remaining elements of right[], if there are any
	for indexOfSubArrayTwo < subArrayTwo {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo]
		indexOfSubArrayTwo++
		indexOfMergedArray++
	}
}

// mergeSort is the main function that sorts array[]
func mergeSort(array []int, begin int, end int) {
	if begin >= end {
		return
	}

	mid := begin + (end-begin)/2
	mergeSort(array, begin, mid)
	mergeSort(array, mid+1, end)
	merge(array, begin, mid, end)
}

func main() {

	args := os.Args
	fmt.Println(args[0], args[1])

	data, err := os.ReadFile("../data/" + args[1])
	if err != nil {
		log.Panicf("failed reading data from file: %s", err)
	}

	strArr := strings.Split(string(data), " ")

	iArr, err := Slice_Atoi(strArr)
	if err != nil {
		log.Print("Slice_Atoi failed: ", err)
		return
	}

	if args[2] == "1" {
		mergeSort(iArr, 0, len(iArr)-1)
	}
}
