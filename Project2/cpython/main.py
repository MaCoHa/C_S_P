import sys
import mergesort
import quicksort

def validate(arr):
	sorted = True
	for i in range(1,len(arr)):
		if arr[i] < arr[i-1]:
			sorted = False
			break
	print(sorted)

def main():
    if len(sys.argv) <= 3:
         raise Exception("Not enough parameters. Usage: python3 main.py algorithm fileName isBaseCase")
    algorithm = sys.argv[1]
    fileName = sys.argv[2]
    isBaseCase = sys.argv[3].lower() in ["1" , "true"]
    
    file = open("../tmp-data/" + fileName, "r")

    # Split the content into individual numbers
    inputData = file.read().split()

    # Convert the numbers from strings to integers
    inputData = [int(num) for num in inputData]
    #validate(inputData)
    if not isBaseCase:
        if algorithm == "mergesort":
            mergesort.mergeSort(inputData)
        elif algorithm == "quicksort":
            quicksort.quickSortBase(inputData)
        else:
            raise Exception("Unsupported algorithm in python: " + algorithm)
    #print(inputData)
    
    #validate(inputData)
    

if __name__ == "__main__":
    main()