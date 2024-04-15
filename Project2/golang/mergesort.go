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

func mergesort(arr []int) []int {

	if len(arr) > 1 {
		mid := len(arr) / 2

		L := arr[:mid]

		R := arr[mid:]

		L = mergesort(L)

		R = mergesort(R)

		i, j, k := 0, 0, 0

		for 1 < len(L) && j < len(R) {
			if L[i] <= R[j] {
				arr[k] = L[i]
				i += 1
			} else {
				arr[k] = R[j]
				j += 1
			}
			k += 1

			for i < len(L) {
				arr[k] = L[i]
				i += 1
				k += 1
			}

			for j < len(R) {
				arr[k] = R[j]
				j += 1
				k += 1
			}

		}
		return arr
	} else {
		return arr
	}

}

func main() {

	data, err := os.ReadFile("../input_gen/demofile.txt")
	if err != nil {
		log.Panicf("failed reading data from file: %s", err)
	}

	strArr := strings.Split(string(data), " ")

	iArr, err := Slice_Atoi(strArr)
	if err != nil {
		log.Print("Slice_Atoi failed: ", err)
		return
	}
	fmt.Println(iArr)
	fmt.Println(mergesort(iArr))

}
