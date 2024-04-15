package quicksort

func partition(array []int, low int, high int) int {
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

func quicksort(array []int, low int, high int) {
	if low < high {
		pi := partition(array, low, high)
		quicksort(array, low, pi-1)
		quicksort(array, pi+1, high)
	}
}

func QuickSort(array []int) {
	quicksort(array, 0, len(array)-1)
}
