package quicksort

// A utility function to swap two elements
func swap(a *int, b *int) {
	t := *a
	*a = *b
	*b = t
}

// This function is same in both iterative and recursive
func partition(arr []int, l int, h int) int {
	x := arr[h]
	i := l - 1

	for j := l; j <= h-1; j++ {
		if arr[j] <= x {
			i++
			swap(&arr[i], &arr[j])
		}
	}
	swap(&arr[i+1], &arr[h])
	return i + 1
}

// A[] --> Array to be sorted,
// l --> Starting index,
// h --> Ending index
func quickSortIterative(arr []int, l int, h int) {
	// Create an auxiliary stack
	stack := make([]int, h-l+1)

	// initialize top of stack
	top := -1

	// push initial values of l and h to stack
	top++
	stack[top] = l
	top++
	stack[top] = h

	// Keep popping from stack while is not empty
	for top >= 0 {
		// Pop h and l
		h = stack[top]
		top--
		l = stack[top]
		top--

		// Set pivot element at its correct position
		// in sorted array
		p := partition(arr, l, h)

		// If there are elements on left side of pivot,
		// then push left side to stack
		if p-1 > l {
			top++
			stack[top] = l
			top++
			stack[top] = p - 1
		}

		// If there are elements on right side of pivot,
		// then push right side to stack
		if p+1 < h {
			top++
			stack[top] = p + 1
			top++
			stack[top] = h
		}
	}
}

func QuickSort(array []int) {
	quickSortIterative(array, 0, len(array)-1)
}
