package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func main() {
	args := os.Args[1:]

	if len(args) < 1 {
		fmt.Println("Usage: go run main.go <Number of millions of elements> [test seed (int)]")
		return
	}

	n, err := strconv.Atoi(args[0])
	if err != nil {
		fmt.Println("Invalid input for number of millions of elements:", err)
		return
	}

	var testSeed int64
	isTest := false
	if len(args) > 1 {

		i, err := strconv.ParseInt(args[1], 10, 64)
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

	length := n * 1000000
	numbers := make([]int, length)
	for i := 0; i < length; i++ {
		numbers[i] = i + 1
	}
	rand.Shuffle(length, func(i, j int) {
		numbers[i], numbers[j] = numbers[j], numbers[i]
	})

	b := bufio.NewWriter(os.Stdout)
	for i, n := range numbers {
		if i == 0 {
			b.WriteString(fmt.Sprint(n))
		} else {
			b.WriteString(" " + fmt.Sprint(n))
		}
	}
}
