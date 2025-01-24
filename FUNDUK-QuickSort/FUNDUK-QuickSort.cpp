#include <iostream>
#include <type_traits>//for concepts usage
#include <string>
#include <fstream>
#include <regex>
#include <chrono>
//struct for storing phone numbers (from the task) first field is country code, second is number
struct phoneNumber {//in this case struct stores phoneNumber
	unsigned int number = 0;
	unsigned long int countryCode = 0;

	inline bool operator==(const phoneNumber& other) const
	{
		return (this->countryCode == other.countryCode) && (this->number == other.number);
	}

	inline bool operator>(const phoneNumber& other) const
	{
		return ((this->countryCode == other.countryCode) && (this->number > other.number))
			|| (this->countryCode > other.countryCode);
	}

	inline bool operator<=(const phoneNumber& other) const
	{
		return !this->operator>(other);
	}

	inline bool operator<(const phoneNumber& other) const
	{
		return ((this->countryCode == other.countryCode) && (this->number < other.number)) ||
			(this->countryCode < other.countryCode);
	}

	inline bool operator>=(const phoneNumber& other) const
	{
		return !this->operator>(other);
	}

	std::string toString() {
		std::string output;
		output = std::to_string(countryCode) + "-" + std::to_string(number);
		return output;
	}
};
struct NLM {
	std::string lastName;
	std::string firstName;
	std::string middleName;

	inline bool operator==(const NLM& other) const
	{
		return (this->lastName == other.lastName) && (this->firstName == other.firstName) && (this->middleName == other.middleName);
	}

	inline bool operator>(const NLM& other) const
	{
		return (this->lastName > other.lastName) || ((this->lastName == other.lastName) && (this->firstName >= other.firstName)) || ((this->lastName == other.lastName) && (this->firstName == other.firstName) && (this->middleName > other.middleName));
	}

	inline bool operator<=(const NLM& other) const
	{
		return !this->operator>(other);
	}

	inline bool operator<(const NLM& other) const
	{
		return (this->lastName < other.lastName) || ((this->lastName == other.lastName) && (this->firstName <= other.firstName)) || ((this->lastName == other.lastName) && (this->firstName == other.firstName) && (this->middleName < other.middleName));
	}

	inline bool operator>=(const NLM& other) const
	{
		return !this->operator>(other);
	}

	std::string toString() {
		std::string output;
		output = lastName + " " + firstName + middleName;
		return output;
	}

};
struct taskKey {
	struct phoneNumber phone;
	struct NLM nlm;
	unsigned short UUID = 0;;
	inline bool operator==(const taskKey& other) const
	{
		return (this->phone == other.phone) && (this->nlm == other.nlm);
	}

	inline bool operator>(const taskKey& other) const
	{
		return ((this->phone == other.phone) && (this->nlm < other.nlm))
			|| (this->phone > other.phone);
	}

	inline bool operator<=(const taskKey& other) const
	{
		return !this->operator>(other);
	}

	inline bool operator<(const taskKey& other) const
	{
		return ((this->phone == other.phone) && (this->nlm > other.nlm)) ||
			(this->phone < other.phone);
	}

	inline bool operator>=(const taskKey& other) const
	{
		return !this->operator>(other);
	}

	std::string toString() {
		std::string output;
		output = phone.toString() + " - " + nlm.toString() + "UUID:" + std::to_string(UUID);
		return output;
	}

};

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

	do {
		while ((((*i < pivot) == isAscending) || (*i == pivot)) && (i < arr + arrSize)) {
			i++;//move until finding arr[i] > pivot
		}
		while ((((*j > pivot) == isAscending) || (*i == pivot)) && (j > arr)) {
			j--;// -- < -- 
		}//swap values

		if (i < j) {

			*temp = *i;
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

	quickSort(arr, (j - arr) + 1, isAscending);
	quickSort(j + 1, arrSize - (j - arr + 1), isAscending);

}

template <class T>
void selectionsSort(T sortedPart[], size_t  arrSize, bool isAscending)requires isComparable<T> {
	if (arrSize < 2) {
		return;//already sorted
	}
	T* locMinPtr = sortedPart;
	T* temp = new T;//using a pointer to not run destructor while copying the object
	while (arrSize > 0) {
		for (size_t i = 0; i < arrSize; i++) {//find minimal element in the array
			if (isAscending == (sortedPart[i] < *locMinPtr)) {
				locMinPtr = sortedPart + i;
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
	//load data from file
	std::ifstream dataFile;
	std::string filePath;

	while (true) {//load file 
		std::cout << "Enter the file path: ";
		// std::getline(std::cin, filePath);

		std::cout << "\n";
		std::cin.clear();
		//check if file exists
		dataFile.open(filePath);
		if (dataFile.is_open()) {
			break;
		}
		else {
			std::cout << "File " << filePath << " not found. Try again.\n";
		}
	}

	std::ofstream outFile(filePath + ".sorted.txt");
	if (outFile.is_open()) {

	}
	else {
		std::cerr << "Unable to open output file." << std::endl;
	}

	std::string line;
	size_t fileReadCounter = 0;
	bool isCorrect = true;
	size_t totalLineCount = std::count(std::istreambuf_iterator<char>(dataFile), std::istreambuf_iterator<char>(), '\n');
	totalLineCount = 10000;
	dataFile.clear();
	dataFile.seekg(0);//return to the begining

	struct taskKey* arr = new struct taskKey[totalLineCount];//allocating memory
	struct taskKey* arr1 = new struct taskKey[totalLineCount];//allocating memory


	for (size_t loadedCounter = 0; loadedCounter < totalLineCount; loadedCounter++)//read file line by line
	{
		if (!std::getline(dataFile, line))
		{
			break;
		}
		std::regex pattern(R"((\d{3}-\d{7})\s+([A-Za-zÀ-ÿ]+)\s+([A-Za-zÀ-ÿ]+)\s+([A-Za-zÀ-ÿ]+))");
		std::smatch matches;

		if (std::regex_match(line, matches, pattern)) {
			std::string countryCode = matches[1].str().substr(0, 3);
			std::string number = matches[1].str().substr(4, 7);
			std::string lastName = matches[2];
			std::string firstName = matches[3];
			std::string  middleName = matches[4];
			arr[loadedCounter].phone.countryCode = std::stoul(countryCode);
			arr[loadedCounter].phone.number = std::stoul(number);
			arr[loadedCounter].nlm.firstName = firstName;
			arr[loadedCounter].nlm.middleName = middleName;
			arr[loadedCounter].nlm.lastName = lastName;
			arr[loadedCounter].UUID = (loadedCounter % 16384);
		}
		else {
			std::cout << "Error in line " << (fileReadCounter + 1) << ": " << line << "\n";
			isCorrect = false;
		}
		fileReadCounter++;
	}
	dataFile.close();
	std::memcpy(arr1, arr, (sizeof arr[0]) * totalLineCount);

	if (!isCorrect) {
		std::cout << "The file contains errors. Please correct them. every line should have a format of 123-1234567 \n";
		exit(0);
	}
	else {
		std::cout << "File loaded successfully (" << fileReadCounter << " lines)\n";
	}



	//qSort on random data
	outFile << "Sorting with qSort...\n";
	std::cout << "sorting using qSort:\n";
	auto start = std::chrono::high_resolution_clock::now();
	selectionsSort(arr1, totalLineCount, true);
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
		elapsed).count();
	outFile << "took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n ";
	std::cout << " done! took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n";

	//insertions sort on random data

	outFile << "Sorting with insertions...\n";
	std::cout << "sorting using insertions:\n";
	start = std::chrono::high_resolution_clock::now();
	selectionsSort(arr, totalLineCount, true);
	elapsed = std::chrono::high_resolution_clock::now() - start;
	milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
		elapsed).count();
	outFile << "took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n";
	std::cout << " done! took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n";

	//qSort on random data
	outFile << "Sorting with qSort on already sorted array ...\n";
	std::cout << "Sorting with qSort on already sorted array ...\n";
	 start = std::chrono::high_resolution_clock::now();
	selectionsSort(arr1, totalLineCount, true);
	 elapsed = std::chrono::high_resolution_clock::now() - start;
	milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
		elapsed).count();
	outFile << "took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n";
	std::cout << " done! took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n";

	//insertions sort on random data

	outFile << "Sorting with insertions on already sorted array ...\n";
	std::cout << "Sorting with insertions on already sorted array ...\n";
	start = std::chrono::high_resolution_clock::now();
	selectionsSort(arr, totalLineCount, true);
	elapsed = std::chrono::high_resolution_clock::now() - start;
	milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
		elapsed).count();
	outFile << "took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n";
	std::cout << " done! took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n";

	//reversing arrays
	for (size_t i = 0; i < ((totalLineCount - (totalLineCount % 2)) / 2); i++) {
		taskKey temp;
		temp = arr1[i];
		arr1[i] = arr1[(totalLineCount - i - 1)];
		temp = arr[i];
		arr[i] = arr[(totalLineCount - i - 1)];
	}



	// possibly worst case, sorting on reversely sorted array
	//qSort on random data
	outFile << "Sorting with qSort on reverse-sorted array ...\n";
	std::cout << "Sorting with qSort on reverse-sorted  sorted array ...\n";
	start = std::chrono::high_resolution_clock::now();
	selectionsSort(arr1, totalLineCount, true);
	elapsed = std::chrono::high_resolution_clock::now() - start;
	milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
		elapsed).count();
	outFile << "took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n sorted:\n";
	std::cout << " done! took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n";

	//insertions sort on random data

	outFile << "Sorting with insertions on reverse-sorted  sorted array ...\n";
	std::cout << "Sorting with insertions on reverse-sorted  sorted array ...\n";
	start = std::chrono::high_resolution_clock::now();
	selectionsSort(arr, totalLineCount, true);
	elapsed = std::chrono::high_resolution_clock::now() - start;
	milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
		elapsed).count();
	outFile << "took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n sorted:\n";
	std::cout << " done! took: " << milliseconds << "ms  (" << ((double)totalLineCount / milliseconds) << ")elements per ms\n sorted:\n";
	
	
	outFile << " Qsort out:\n";

	for (size_t i = 0; i < totalLineCount; i++) {
		outFile << arr[i].toString() << "\n";
	}
	outFile << " insertions out:\n";
	for (size_t i = 0; i < totalLineCount; i++) {
		outFile << arr1[i].toString() << "\n";
	}

	outFile.close();
	return 0;
}