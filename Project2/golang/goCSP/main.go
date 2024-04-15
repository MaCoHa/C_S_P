package main

import (
	"goCSP/mergesort"
	"goCSP/quicksort"
	"log"
	"os"
	"strconv"
	"strings"
)

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

	data, err := os.ReadFile("../../data/" + fileName)
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
			log.Print(iArr)
		} else if algorithm == "quicksort" {
			quicksort.QuickSort(iArr)
			log.Print(iArr)
		} else {
			log.Fatalln("Unsupported algorithm in python: " + algorithm)
		}
	}
}
