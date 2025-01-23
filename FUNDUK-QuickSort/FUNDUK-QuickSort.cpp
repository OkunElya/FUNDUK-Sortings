#include <iostream>
#include <type_traits>//for concepts usage

template <typename T>
concept isComparable = requires(T a, T b) { // a concept to check if type is comparable
	{ a > b } -> std::same_as<bool>;
	{ a < b } -> std::same_as<bool>;
	{ a == b } -> std::same_as<bool>;
};

template <class T>
void printArr(T arr[], size_t arrSize)
{
	std::cout << "{";
	for (size_t i = 0; i < (arrSize - 1); i++) {
		std::cout << arr[i] << ", ";
	}
	std::cout << arr[arrSize - 1] << "}";
}

template <class T>
void quickSort(T arr[], size_t arrSize, bool isAscending)requires isComparable<T> {
	if (arrSize < 2) {
		return;
	}

	T pivot = arr[0];
	T* i = arr + 1;
	T* j = arr + arrSize - 1;
	T* temp = new T;

	do{
		while ((((*i < pivot)== isAscending)||(*i==pivot)) && (i < arr + arrSize)) {
			i++;//move until finding arr[i] > pivot
		}
		while ((((*j > pivot) == isAscending) || (*i == pivot)) &&(j>arr)) {
			j--;// -- < -- 
		}//swap values
		
		if (i < j) {
			
			*temp=*i;
			*i = *j;
			*j = *temp;
			i++;
			j--;
		}
	} while (i < j);

	arr[0] = *j;
	*j = pivot;
	temp = nullptr;
	delete temp;

	quickSort(arr, (j - arr)+1,isAscending);
	quickSort(j + 1, arrSize - (j - arr + 1), isAscending);

}

template <class T>
void selectionsSort(T sortedPart[], size_t  arrSize,bool isAscending)requires isComparable<T> {
	if (arrSize < 2) {
		return;//already sorted
	}
	T* locMinPtr = sortedPart;
	T* temp = new T;//using a pointer to not run destructor while copying the object
	while (arrSize >0) {
		for (size_t i = 0; i < arrSize; i++) {//find minimal element in the array
			if (isAscending ==(sortedPart[i] < *locMinPtr)) {
				locMinPtr = sortedPart+i ;
			}
		}
		
		*temp = *sortedPart;
		*sortedPart = *locMinPtr;
		*locMinPtr = *temp;//write values
		locMinPtr = sortedPart + 1;
		sortedPart++;
		arrSize--;
	}
	temp = nullptr;
	delete temp;
}

template <class T>
bool isSorted(T arr[], size_t arrSize, bool isAscending)requires isComparable<T> {
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

	selectionsSort(aboba, abS,0);
	std::cout << "\n final array:";
	printArr(aboba, abS);
	std::cout << isSorted(aboba, abS, true);

}