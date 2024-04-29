package mergesort

func merge(arr []int, l, m, r int) {
	n1 := m - l + 1
	n2 := r - m

	L := make([]int, n1)
	R := make([]int, n2)

	for i := 0; i < n1; i++ {
		L[i] = arr[l+i]
	}
	for j := 0; j < n2; j++ {
		R[j] = arr[m+1+j]
	}

	i := 0
	j := 0
	k := l
	for i < n1 && j < n2 {
		if L[i] <= R[j] {
			arr[k] = L[i]
			i++
		} else {
			arr[k] = R[j]
			j++
		}
		k++
	}

	for i < n1 {
		arr[k] = L[i]
		i++
		k++
	}

	for j < n2 {
		arr[k] = R[j]
		j++
		k++
	}
}

func mergeSort(arr []int, n int) {
	for currSize := 1; currSize <= n-1; currSize = 2 * currSize {
		for leftStart := 0; leftStart < n-1; leftStart += 2 * currSize {
			mid := min(leftStart+currSize-1, n-1)
			rightEnd := min(leftStart+2*currSize-1, n-1)
			merge(arr, leftStart, mid, rightEnd)
		}
	}
}

func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}

func MergeSort(array []int) {
	mergeSort(array, len(array))
}
