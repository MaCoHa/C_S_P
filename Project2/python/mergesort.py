def mergeSort(arr):
    n = len(arr)
    current_size = 1

    # Outer loop for traversing subarrays of current_size
    while True:
        left = 0
        # Inner loop for merge call in a subarray
        # Each complete iteration sorts a subarray of current_size
        while left < n - 1:
            #We save a few seconds in the long run with this:
            mid = left + current_size - 1 if (left + current_size) - 1 < n-1 else n - 1
            right = left + 2 * current_size-1 if (left + 2 * current_size-1) < n-1 else n - 1
            # Merge subarrays arr[left...mid] and arr[mid+1...right]
            merge(arr, left, mid, right)
            left += 2 * current_size
        current_size *= 2
        #print("double")
        if current_size >= n:
            break

def merge(arr, left, mid, right):
    temp = arr[left:right + 1]  # Temporary array to store merged subarrays
    i = left    # Initial index of left subarray
    j = mid + 1  # Initial index of right subarray
    k = 0       # Initial index of temporary array

    # Merge the subarrays
    while i <= mid and j <= right:
        if arr[i] < arr[j]:
            temp[k] = arr[i]
            i += 1
        else:
            temp[k] = arr[j]
            j += 1
        k += 1

    # Copy the remaining elements of left subarray
    while i <= mid:
        temp[k] = arr[i]
        i += 1
        k += 1

    # Copy the remaining elements of right subarray
    while j <= right:
        temp[k] = arr[j]
        j += 1
        k += 1

    # Copy the merged elements back to the original array
    arr[left:right + 1] = temp
