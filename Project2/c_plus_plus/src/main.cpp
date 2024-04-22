#include <iostream>
#include <fstream>
#include <vector>
#include "includes/mergesort.hpp"
#include "includes/quicksort.hpp"

using namespace std;

void printArray(int A[], int size)
{
	for (int i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << endl;
}
void validate(int A[], int size)
{
	bool sorted = true;
	for (int i = 1; i < size; i++)
	{
		if (A[i] < A[i - 1])
		{
			sorted = false;
			break;
		}
	}
	cout << "The list is sorted: " << sorted << endl;
}

int main(int argc, char *argv[])
{
	if(argc <= 3){
		throw invalid_argument("Too Few arguments. Usage: ./main (file_name) (algorithm) (is_base_case)");
	}
	string path = ("../../data/");
	path += argv[1];

	ifstream file(path);

	vector<int> numbers;
	int num;
	int numbers_size = 0;
	while (file >> num)
	{
		numbers.push_back(num);
		numbers_size = numbers_size + 1;
	}

	file.close();
	int* array = &numbers[0];
	if(*argv[3] == '1'){
		return 0;
	}

	//validate(array, numbers_size - 1);

	if (argv[2] == string("mergesort"))
	{
		MergeSort::MergeSort(array, numbers_size);
	}
	else if (argv[2] == string("quicksort"))
	{
		QuickSort::QuickSort(array, numbers_size);
	}else{
		throw invalid_argument("Must give a valid algorithm");
	}
	//validate(array, numbers_size - 1);

	return 0;
}
