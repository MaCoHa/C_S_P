def mergeSort(seq):
    if len(seq) == 1:
        return seq
    left = mergeSort(seq[:len(seq) // 2])
    right = mergeSort(seq[len(seq) // 2:])

    return merge(left, right)


def merge(left, right):
    result = []
    left_count = 0
    right_count = 0
    try:
        while True:
            if left[left_count] > right[right_count]:
                result.append(right[right_count])
                right_count += 1
            else:
                result.append(left[left_count])
                left_count += 1
    except:
        return result + left[left_count:] + right[right_count:]

