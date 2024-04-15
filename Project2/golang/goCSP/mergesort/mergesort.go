package mergesort

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

func MergeSort(array []int) {
	mergeSort(array, 0, len(array)-1)
}
