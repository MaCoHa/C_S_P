#include <bits/stdc++.h>
using namespace std;


void merge(int array[] , int const left, int const mid,
		int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne]
			<= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray]
				= leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}


	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}


void mergeSort(int array[] , int const begin, int const end)
{
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
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
		mergeSort(array, 0, numbers_size-1);
	}
    validate(array,numbers_size-1);

	return 0;
}

