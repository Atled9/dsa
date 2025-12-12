#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

#define ORDERED true
#define UNORDERED false

#define ALLOW_REPEAT_VALUES true
#define NO_REPEAT_VALUES false

enum SearchAlgo {
	LINEAR,
	BINARY,
	INTERPOLATION
};

enum SortAlgo {
	BUBBLE,
	SELECTION,
	INSERTION,
	MERGE,
	QUICK
};

class ASys {
	private:
		int* a = NULL;
		int size = 0;
		int capacity = 0;

		const int NON_VALUE = std::numeric_limits<int>::min();

		SearchAlgo searchOption = BINARY;
		SortAlgo sortOption = MERGE;
		
		void expand() {
			int* temp = new int[capacity * 2];
			capacity *= 2;

			for (int i = 0; i < size; i++) {
				temp[i] = a[i];
			}
			delete[] a;
			a = temp;
		}
		void shrink() {
			int* temp = new int[capacity / 2];
			capacity /= 2;

			for (int i = 0; i < size; i++) {
				temp[i] = a[i];
			}
			delete[] a;
			a = temp;
		}

		int linearSearch(int val);
		int binarySearch(int val);
		int interpolationSearch(int val);

		void bubbleSort();
		void selectionSort();
		void insertionSort();
		void mergeSort();
		void quickSort();
	public:
		//OVERLOADED CONSTRUCTORS
		ASys() {
		}

		/*WITH SIZE PARAMETER*/
		ASys(int size, bool isOrdered, bool allowRepeats) {
			a = new int[size];

			if (isOrdered && allowRepeats) {
				for (int i = 0; i < size; i++) {
					a[i] = NON_VALUE;
				}
				srand(time(NULL));
				int val;
				int ind;
				for (int i = 0; i < size; i++) {
					ind = 0;
					val = (rand() % size);
					while (a[ind] != NON_VALUE) {
						if (a[ind] >= val) {
							for (int i = size - 1; i > ind; i--) {
								a[i] = a[i - 1];
							}
							a[ind] = NON_VALUE;
						}
						else {
							ind++;
						}
					}
					a[ind] = val;
				}
			}
			else if (isOrdered && !allowRepeats) {
				for (int i = 0; i < size; i++) {
					a[i] = i;
				}
			}
			else if (!isOrdered && allowRepeats) {
				srand(time(NULL));
				for (int i = 0; i < size; i++) {
					a[i] = rand() % size;
				}
			}
			else {
				srand(time(NULL));
				int* possibleValues = new int[size];
				int possibleValuesSize = size;

				for (int i = 0; i < possibleValuesSize; i++) {
					possibleValues[i] = i;
				}

				int pickInd;
				for (int i = 0; i < size; i++) {
					pickInd = rand() % possibleValuesSize;
					a[i] = possibleValues[pickInd];

					for (int j = pickInd; j < possibleValuesSize - 1; j++) {
						possibleValues[j] = possibleValues[j + 1];
					}
					possibleValuesSize--;
				}
				delete[] possibleValues;
			}
			this->size = size;
			capacity = size;
		}

		/*WITH SIZE AND RANGE PARAMETERS*/
		ASys(int size, int range, bool isOrdered, bool allowRepeats) {
			a = new int[size];

			if (isOrdered && allowRepeats) {
				for (int i = 0; i < size; i++) {
					a[i] = NON_VALUE;
				}
				srand(time(NULL));
				int val;
				int ind;
				for (int i = 0; i < size; i++) {
					ind = 0;
					val = (rand() % range);
					while (a[ind] != NON_VALUE) {
						if (a[ind] >= val) {
							for (int i = size - 1; i > ind; i--) {
								a[i] = a[i - 1];
							}
							a[ind] = NON_VALUE;
						}
						else {
							ind++;
						}
					}
					a[ind] = val;
				}
			}
			else if (isOrdered && !allowRepeats) {
				if (range < size) {
					std::cout << "You cannot create an array with a range smaller than its size without repeating values\n";

					for (int i = 0; i < size - range; i++) {
						a[i] = NON_VALUE;
					}
					for (int i = size - range; i < size; i++) {
						a[i] = i - (size - range);
					}
				}
				else {
					for (int i = 0; i < size; i++) {
						a[i] = i * (range / size);
					}
				}
			}
			else if (!isOrdered && allowRepeats) {
				srand(time(NULL));
				for (int i = 0; i < size; i++) {
					a[i] = rand() % range;
				}
			}
			else {
				srand(time(NULL));
				int* possibleValues = new int[size];
				int possibleValuesSize = size;

				if (range < possibleValuesSize) {
					std::cout << "You cannot create an array with a range smaller than its size without repeating values\n";

					for (int i = 0; i < possibleValuesSize - range; i++) {
						possibleValues[i] = NON_VALUE;
					}
					for (int i = possibleValuesSize - range; i < possibleValuesSize; i++) {
						possibleValues[i] = i - (possibleValuesSize - range);
					}
				}
				else {
					for (int i = 0; i < possibleValuesSize; i++) {
						possibleValues[i] = i * (range / possibleValuesSize);
					}
				}

				int pickInd;
				for (int i = 0; i < size; i++) {
					pickInd = rand() % possibleValuesSize;
					a[i] = possibleValues[pickInd];

					for (int j = pickInd; j < possibleValuesSize - 1; j++) {
						possibleValues[j] = possibleValues[j + 1];
					}
					possibleValuesSize--;
				}
				delete[] possibleValues;
			}
			this->size = size;
			capacity = size;
		}

		/*WITH SIZE, RANGE AND START PARAMETERS*/
		ASys(int size, int range, int start, bool isOrdered, bool allowRepeats) {
			a = new int[size];

			if (isOrdered && allowRepeats) {
				for (int i = 0; i < size; i++) {
					a[i] = NON_VALUE;
				}
				srand(time(NULL));
				int val;
				int ind;
				for (int i = 0; i < size; i++) {
					ind = 0;
					val = (rand() % range) + start;
					while (a[ind] != NON_VALUE) {
						if (a[ind] >= val) {
							for (int i = size - 1; i > ind; i--) {
								a[i] = a[i - 1];
							}
							a[ind] = NON_VALUE;
						}
						else {
							ind++;
						}
					}
					a[ind] = val;
				}
			}
			else if (isOrdered && !allowRepeats) {
				if (range < size) {
					std::cout << "You cannot create an array with a range smaller than its size without repeating values\n";

					for (int i = 0; i < size - range; i++) {
						a[i] = NON_VALUE;
					}
					for (int i = size - range; i < size; i++) {
						a[i] = i - (size - range) + start;
					}
				}
				else {
					for (int i = 0; i < size; i++) {
						a[i] = i * (range / size) + start;
					}
				}
			}
			else if (!isOrdered && allowRepeats) {
				srand(time(NULL));
				for (int i = 0; i < size; i++) {
					a[i] = rand() % range + start;
				}
			}
			else {
				srand(time(NULL));
				int* possibleValues = new int[size];
				int possibleValuesSize = size;

				if (range < possibleValuesSize) {
					std::cout << "You cannot create an array with a range smaller than its size without repeating values\n";

					for (int i = 0; i < possibleValuesSize - range; i++) {
						possibleValues[i] = NON_VALUE;
					}
					for (int i = possibleValuesSize - range; i < possibleValuesSize; i++) {
						possibleValues[i] = i - (possibleValuesSize - range) + start;
					}
				}
				else {
					for (int i = 0; i < possibleValuesSize; i++) {
						possibleValues[i] = i * (range / possibleValuesSize) + start;
					}
				}

				int pickInd;
				for (int i = 0; i < size; i++) {
					pickInd = rand() % possibleValuesSize;
					a[i] = possibleValues[pickInd];

					for (int j = pickInd; j < possibleValuesSize - 1; j++) {
						possibleValues[j] = possibleValues[j + 1];
					}
					possibleValuesSize--;
				}
				delete[] possibleValues;
			}
			this->size = size;
			capacity = size;
		}

		//GETTERS

		int getSize() {
			return size;
		}
		int getCapacity() {
			return capacity;
		}
		int* getCopy() {
			int* copy = new int[size];
			for (int i = 0; i < size; i++) {
			       copy[i] = a[i];
			}
	 		return copy;
		}
		void printA() {
			for (int i = 0; i < size; i++) {
				std::cout << a[i] << ' ';
			}
			std::cout << '\n';
		}
		bool isEmpty() {
			return !size;
		}
		int getVal(int index) {
			if (index < 0 || index >= size) {
				std::cout << "Invalid Index\n";
				return NON_VALUE;
			}
			return a[index];
		}
		int search(int val) {
			switch(searchOption) {
				case 0:
					return linearSearch(val);
				case 1:
					return binarySearch(val);
				case 2:
					return interpolationSearch(val);
			}
			return -1;
		}
		bool isSorted() {
			for (int i = 0; i < size - 1; i++) {
				if (a[i] > a[i + 1]) {
					return false;
				}
			}
			return true;
		}
		//SETTERS

		void push(int val) {
			if (capacity == 0) {
				a = new int;
				capacity = 1;
			}
			if (size == capacity) {
				expand();
			}
			a[size] = val;
			size++;
		}
		void enqueue(int val) {
			push(val);
		}
		void insert(int index, int val) {
			if (capacity == 0 && index == 0) {
				a = new int;
				capacity = 1;
			}
			else if (index < 0 || index > size) {
				std::cout << "Invalid Index\n";
				return;
			}

			if (size == capacity) {
				expand();
			}
			for(int i = size; i > index; i--) {
				a[i] = a[i - 1];
			}
			a[index] = val;
			size++;

		}
		void replace(int index, int value) {
			if (index < 0 || index >= size) {
				std::cout << "Invalid Index\n";
				return;
			}
			a[index] = value;
		}

		void setSearch(SearchAlgo option) {
			searchOption = option;
		}
		void setSort(SortAlgo option) {
			sortOption = option;
		}

		void sort() {
			switch(sortOption) {
				case 0:
					bubbleSort();
				case 1:
					std::cout << "You have SelectionSort as your sorting option\n";
					break;
				case 2:
					std::cout << "You have InsertionSort as your sorting option\n";
					break;
				case 3:
					std::cout << "You have MergeSort as your sorting option\n";
					break;
				case 4:
					std::cout << "You have QuickSort as your sorting option\n";
					break;
			}
		}

		//DELETERS

		int pop() {
			if (isEmpty()) {
				std::cout << "A is empty\n";
				return NON_VALUE;
			}

			int returnVal = a[size - 1];
			size--;

			if (size == (capacity / 2)) {
				shrink();
			}
			return returnVal;
		}
		int dequeue() {
			if (isEmpty()) {
				std::cout << "A is empty\n";
				return NON_VALUE;
			}

			int returnVal = a[0];

			for (int i = 0; i < size - 1; i++) {
				a[i] = a[i + 1];
			}
			size--;

			if(size == (capacity / 2)) {
				shrink();
			}
			return returnVal;
		}
		void remove(int index) {
			if (isEmpty()) {
				std::cout << "A is empty\n";
				return;
			}
			else if (index < 0 || index >= size) {
				std::cout << "Index Out Of Range\n";
				return;
			}

			for (int i = index; i < size - 1; i++) {
				a[i] = a[i + 1];
			}
			size--;

			if(size == (capacity / 2)) {
				shrink();
			}
		}

		//DESTRUCTOR

		~ASys() {
			delete[] a;
		}
};

/*Search Algos*/
int ASys::linearSearch(int val) {
	int ind = -1;
	for (int i = 0; i < size; i++) {
		if (a[i] == val) {
			ind = i;
		}
	}
	return ind;
}
int ASys::binarySearch(int val) {
	int index = -1;
	int lo = 0;
	int hi = size - 1;

	int mid;
	while (lo <= hi) {
		mid = ((hi - lo) / 2) + lo;

		if (a[mid] == val) {
			return mid;
		}
		else if (a[mid] < val) {
			lo = mid + 1;
		}
		else {
			hi = mid - 1;
		}
	}
	return -1;
}
int ASys::interpolationSearch(int val) {
	int index = -1;
	int lo = 0;
	int hi = size - 1;

	int mid;
	while (lo <= hi && a[lo] <= val && a[hi] >= val) {
		mid = ((hi - lo)/(a[hi] - a[lo])) * (val - a[lo]) + lo;

		if (a[mid] == val) {
			return mid;
		}
		else if (a[mid] < val) {
			lo = mid + 1;
		}
		else {
			hi = mid - 1;
		}
	}
	return -1;
}
/*Sorting Algos*/
void ASys::bubbleSort() {
	int temp;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i; j++) {
			if (a[i] < a[i + 1]) {
				temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
			}
		}
	}
}

/*Search Testing Function*/

bool searchTestingFunction(SearchAlgo testOption) {
	ASys testA(5, 5, 1, ORDERED, NO_REPEAT_VALUES);	
	testA.setSearch(testOption);

	testA.printA();

	if (testA.search(3) != 2) {
		std::cout << "Failed at non-boundary value search\n";
		return false;
	}
	if (testA.search(1) != 0) {
		std::cout << "Failed at beginning-boundary value search\n";
		return false;
	}
	if (testA.search(5) != 4) {
		std::cout << "Failed at ending-boundary value search\n";
		return false;
	}
	if (testA.search(0) != -1) {
		std::cout << "Failed at beginning out-boudary value search\n";
		return false;
	}
	if (testA.search(6) != -1) {
		std::cout << "Failed at ending out-boundary value search\n";
		return false;
	}

	for (int i = 2; i <= 4; i++) {
		testA.replace(i, i + 2);
	}
	testA.printA();

	if (testA.search(3) != -1) {
		std::cout << "Failed at non-existent value search\n";
		return false;
	}
	std::cout << "Passed all tests\n";
	return true;
}

/*Sort Testing Function*/

/*bool sortTestingFunction(SortAlgo testOption) {
	for (int i = 0; i < 100; i++) {

	}
}*/

int main() {
	/*
	searchTestingFunction(LINEAR);
	searchTestingFunction(BINARY);
	searchTestingFunction(INTERPOLATION);
	*/

	ASys test0(5, 5, 1, ORDERED, ALLOW_REPEAT_VALUES);
	test0.printA();
	std::cout << test0.isSorted() << '\n';
	std::cout << '\n';
	ASys test1(5, 5, 1, UNORDERED, ALLOW_REPEAT_VALUES);
	test1.printA();
	std::cout << test1.isSorted() << '\n';
	return 0;
}
