package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func Percent(x int, y int) int {
	p := float64(x) / float64(y)
	return int(p)
}

func FullListShuffle(amount int) []int {

	length := amount * 1000000
	numbers := make([]int, length)
	for i := 0; i < length; i++ {
		numbers[i] = i + 1
	}
	rand.Shuffle(length, func(i, j int) {
		numbers[i], numbers[j] = numbers[j], numbers[i]
	})

	return numbers

}

func PartialListShuffle(amount int) []int {

	length := amount * 1_000_000
	/* 	shuffled := Percent(length, 20) */
	numbers := make([]int, length)

	for i := 0; i < length; i++ {
		numbers[i] = i + 1
	}

	/* for z := 0; z < shuffled; z++ {
		i := rand.Int() % length
		j := rand.Int() % length

		numbers[i], numbers[j] = numbers[j], numbers[i]

	} */

	return numbers

}

func main() {
	args := os.Args[1:]

	if len(args) < 2 {
		fmt.Println("Usage: go run main.go <Number of millions of elements> <shuffle type (1,2,3)>[test seed (int)]")
		return
	}

	n, err := strconv.Atoi(args[0])
	if err != nil {
		fmt.Println("Invalid input for number of millions of elements:", err)
		return
	}

	var testSeed int64

	isTest := false
	if len(args) > 2 {

		i, err := strconv.ParseInt(args[2], 10, 64)
		if err != nil {
			// ... handle error
			panic(err)
		}
		testSeed = i
		isTest = true
	}

	if isTest {
		rand.Seed(testSeed)
	} else {
		rand.Seed(time.Now().UnixNano())
	}

	numbers := make([]int, 0)

	choice, err := strconv.Atoi(args[1])
	if choice == 1 {
		numbers = FullListShuffle(n)

	} else if choice == 2 {
		numbers = PartialListShuffle(n)
	} else if choice == 3 {
		numbers = PartialListShuffle(n)

	} else {
		numbers = nil

	}
	b := bufio.NewWriter(os.Stdout)
	for i, n := range numbers {
		fmt.Println(i)

		if i == 0 {
			b.WriteString(fmt.Sprint(n))
		} else {
			b.WriteString(" " + fmt.Sprint(n))
		}
	}
}
