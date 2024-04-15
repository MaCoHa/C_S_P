// C++ Implementation of the Quick Sort Algorithm.
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int partition(int arr[], int start, int end)
{

	int pivot = arr[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);

	// Sorting left and right parts of the pivot element
	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (arr[i] <= pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
		}
	}

	return pivotIndex;
}

void quickSort(int arr[], int start, int end)
{

	// base case
	if (start >= end)
		return;

	// partitioning the array
	int p = partition(arr, start, end);

	// Sorting the left part
	quickSort(arr, start, p - 1);

	// Sorting the right part
	quickSort(arr, p + 1, end);
}
void printArray(int  A[], int size)
{
	for (int i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << endl;
}
void validate(int A[], int size){
    bool sorted = true;
    for (int i = 1; i < size; i++){
        if (A[i] > A[i - 1]){
           sorted = false;
        }
        if (!sorted){ 
            break;
        }
    }
    cout << "The list is sorted: " << sorted << endl;

}
int main(int argc, char *argv[])
{

	string path = ("../../data/");
	path += argv[1];
	
	ifstream file(path);
	
    vector<int> numbers;
    int num;
	int numbers_size = 0;
    while (file >> num) {
        numbers.push_back(num);
		numbers_size = numbers_size + 1;
    }


 	file.close();

    // Convert vector to array if needed
    int array[numbers.size()];
    for (size_t i = 0; i < numbers_size; ++i) {
        array[i] = numbers[i];
    }

    validate(array,numbers_size-1);
	if (*argv[2] == '1'){
		quickSort(array, 0, numbers_size-1);
	}
    validate(array,numbers_size-1);

	return 0;
}
