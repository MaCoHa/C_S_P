package quicksort

func partitionREC(array []int, low int, high int) int {
	pivot := array[high]
	i := low - 1
	for j := low; j < high; j++ {
		if array[j] <= pivot {
			i += 1
			array[i], array[j] = array[j], array[i]
		}
	}
	array[i+1], array[high] = array[high], array[i+1]
	return i + 1
}

func quicksortREC(array []int, low int, high int) {
	if low < high {
		pi := partitionREC(array, low, high)
		quicksortREC(array, low, pi-1)
		quicksortREC(array, pi+1, high)
	}
}

func QuickSortREC(array []int) {
	quicksortREC(array, 0, len(array)-1)
}
