#include <iostream>

void printArr(float arr[], size_t arrSize)
{
	std::cout << "{";
	for (size_t i = 0; i < (arrSize - 1); i++) {
		std::cout << arr[i] << ", ";
	}
	std::cout << arr[arrSize - 1] << "}";
}

void quickSort(float arr[], size_t arrSize, bool isAscending) {
	if (arrSize < 2) {
		return;
	}

	float pivot = arr[0];
	float* i = arr + 1;
	float* j = arr + arrSize - 1;

	do{
		while ((((*i < pivot)== isAscending)||(*i==pivot)) && (i < arr + arrSize)) {
			i++;//move until finding arr[i] > pivot
		}
		while ((((*j > pivot) == isAscending) || (*i == pivot)) &&(j>arr)) {
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

	quickSort(arr, (j - arr)+1,isAscending);
	quickSort(j + 1, arrSize - (j - arr + 1), isAscending);
}

void selectionsSort(float sortedPart[], size_t  arrSize,bool isAscending) {
	if (arrSize < 2) {
		return;//already sorted
	}
	float* locMinPtr = sortedPart;

	while (arrSize >0) {
		for (size_t i = 0; i < arrSize; i++) {//find minimal element in the array
			if (isAscending ==(sortedPart[i] < *locMinPtr)) {
				locMinPtr = sortedPart+i ;
			}
		}
		
		auto temp = *sortedPart;
		*sortedPart = *locMinPtr;
		*locMinPtr = temp;//write values

		locMinPtr = sortedPart + 1;
		sortedPart++;
		arrSize--;
	}
}

bool isSorted(float arr[], size_t arrSize, bool isAscending) {
	for (size_t i = 0; i < (arrSize - 1); i++) {
		if ((isAscending == (arr[i] > arr[i + 1])) && (arr[i] != arr[i + 1])) {
			return false;
		}
	}
	return true;
}

int main()
{
	float aboba[] = { 1,4,3,5,8,7,9,0 };
	size_t abS = sizeof(aboba) / sizeof(aboba[0]);

	quickSort(aboba, abS,0);
	std::cout << "\n final array:";
	printArr(aboba, abS);
	std::cout << isSorted(aboba, abS, true);

}