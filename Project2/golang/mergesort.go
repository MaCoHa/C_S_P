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

}
