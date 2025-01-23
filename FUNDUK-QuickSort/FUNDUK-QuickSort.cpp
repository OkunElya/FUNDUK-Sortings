
#include <iostream>

void printArr(float arr[], size_t arrSize)
{
	std::cout << "{";
	for (size_t i = 0; i < (arrSize - 1); i++) {
		std::cout << arr[i] << ", ";
	}
	std::cout << arr[arrSize - 1] << "}";
}

void quickSort(float arr[], size_t arrSize) {
	if (arrSize < 2) {
		return;
	}

	float pivot = arr[0];
	float* i = arr + 1;
	float* j = arr + arrSize - 1;

	do{
		while ((*i <= pivot) && (i < arr + arrSize)) {
			i++;//move until finding arr[i] > pivot
		}
		while ((*j >= pivot)&&(j>arr)) {
			j--;// -- < -- 
		}//swap values
		
		if (i < j) {
			float temp = *i;
			*i = *j;
			*j = temp;
			i++;
			j--;
		}
	} while (i < j);

	arr[0] = *j;
	*j = pivot;

	quickSort(arr, (j - arr)+1);
	quickSort(j + 1, arrSize - (j - arr + 1));
}

void selectionsSort(float arr[], size_t  arrSize) {
	if (arrSize < 2) {
		return;//already sorted
	}

	float* sortedPart = arr-1;
	float* locMinPtr = arr;

	while (arrSize >0) {
		for (size_t i = 0; i < arrSize; i++) {//find minimal element in the array
			std::cout << *locMinPtr << "\n";
			if (sortedPart[i+1] < *locMinPtr) {
				locMinPtr = sortedPart + (i + 1);
			}
		}
		sortedPart++;
		auto temp = *sortedPart;
		*sortedPart = *locMinPtr;
		*locMinPtr = temp;//write values
		locMinPtr = sortedPart + 1;
		arrSize--;
	}

}


bool isSorted(float arr[], size_t arrSize, bool ascending) {
	for (size_t i = 0; i < (arrSize - 1); i++) {
		if ((ascending != (arr[i] < arr[i + 1])) && (arr[i] != arr[i + 1])) {
			return false;
		}
	}
	return true;
}

int main()
{
	float aboba[] = { 1,4,3,5 };
	size_t abS = sizeof(aboba) / sizeof(aboba[0]);

	selectionsSort(aboba, abS);
	std::cout << "\n final array:";
	printArr(aboba, abS);
	std::cout << isSorted(aboba, abS, true);

}