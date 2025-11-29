//searching functions will accept a value and an array/vector.
//Searching functions will return an index

#include <iostream>
#include <vector>

//###################### LINEAR SEARCH ##################################

//vector does not need to be sorted for this to work
//time_complexity of O(1) to O(n)
//kind of terrible, but necessary if you know virtually nothing about the vector
int linearSearch(int val, std::vector<int> nums) {
	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] == val) {
			return i;
		}
	}
	return -1;
}

//##################### BINARY SEARCH ####################################

//vector needs to be sorted for this to work
//time complexity of O(1) to O(log n)
//O(log n) at worst case makes this a great all-round algorithm
int binarySearch(int val, std::vector<int> nums) {
	int lo = 0;
	int hi = nums.size() - 1;
	int index;

	while(lo <= hi) {
		index = ((hi - lo) / 2) + lo;

		if (nums[index] == val) {
			return index;
		}
		else if (nums[index] < val) {
			lo = index + 1; //index takes the floor so we need to push lo up in case the value is at the final index
		}
		else {
			hi = index - 1; //index will infinitely retake the floor if hi isn't pushed below when the value does not exist
		}
	}
	return -1;
}

//######################## INTERPOLATION SEARCH ##################################

//vector needs to be sorted for this to work
//linear interpolation works best when differences between values are similar throughout the vector
//average case of O(log log n) but can decay to O(n) if values are unevenly distributed
//This one's a risky algorithm. You should know if a vector has uniform or near-uniform distribution before slapping it into this

//###### Explanation of Linear Interpolation #####

//Assume we have two points along a line P1(x1, y1) and P2(x2, y2)
//Let there be a point P(x, y) whose x-value is between x1 and x2
//We can find the y-value of P by calculating the slope of the line, multiplying the slope by the change in x, and adding the value to y1
//the formula goes as follows: y = y1 + (x - x1)((y2 - y1)/(x2 - x1)) 

//Let our indicies be the y-values, and our values in the vector be the x-values
//If the values in our vector are perfectly uniformly spaced, then the index at our target value goes as follows:
// Index = lowerIndex + (targetValue - valueAtLowerIndex)((higherIndex - lowerIndex)/(valueAtHigherIndex - valueAtLowerIndex))
// A straight "slope" in our vector would give us a best case of O(1), however,
// we can update the slope and initial values at each iteration when the index is not found


int interpolationSearch(int val, std::vector<int> nums) {
	int lo = 0;
	int hi = nums.size() - 1;
	int index;

	while(lo <= hi && val <= nums[hi] && val >= nums[lo]) { //take vector values into loop condition to avoid infinite loop when the value does not exist between indicies
		index = lo + (val - nums[lo]) * ((hi - lo)/(nums[hi] - nums[lo]));

		if (nums[index] == val) {
			return index;
		}
		else if (nums[index] < val) {
			lo = index + 1; //index takes the floor so we need to push lo up in case the value is at the final index
		}
		else {
			hi = index - 1; //index will infinitely retake the floor if hi isn't pushed below when the value does not exist
		}
	}
	return -1;
}
//Forward declare our recursive implementation
int binarySearch_r(int val, std::vector<int> nums);
int binarySearch_r(int val, std::vector<int> nums, int lo, int hi); //helper functions will be overloaded from initial function

int interpolationSearch_r(int val, std::vector<int> nums);
int interpolationSearch_r(int val, std::vector<int> nums, int lo, int hi);

//###################### MAIN FUNCTION ###########################
int main() {
	int length = 0;
	int val;
	int element;

	std::cout << "Please enter the vector length: ";
	std::cin >> length;

	std::vector<int> nums;
	for (int i = 0; i < length; i++) {
		std::cout << "Enter the value of element #" << i + 1 << ": ";
		std::cin >> element;
		nums.push_back(element);
	}

	std::cout << "Please enter a value: ";
	std::cin >> val;

	std::cout << "(linear search) Your value is at index #" << linearSearch(val, nums) << '\n';
	std::cout << "(binary search) Your value is at index #" << binarySearch(val, nums) << '\n';
	std::cout << "(interpolation search) Your value is at index #" << interpolationSearch(val, nums) << '\n';
	
	std::cout << "(recursive binary search) Your value is at index #" << binarySearch_r(val, nums) << '\n';
	std::cout << "(recursive interpolation search) Your value is at index #" << interpolationSearch_r(val, nums) << '\n';

	return 0;
}

int binarySearch_r(int val, std::vector<int> nums, int lo, int hi) {
	if (lo > hi) {
		return -1;
	}

	int index = ((hi - lo) / 2) + lo;
	
	if (nums[index] == val) {
		return index;
	}
	else if (nums[index] < val) {
		return binarySearch_r(val, nums, index + 1, hi);
	}
	else {
		return binarySearch_r(val, nums, lo, hi - 1);
	}
}
int binarySearch_r(int val, std::vector<int> nums) {
	return binarySearch_r(val, nums, 0, nums.size() - 1);
}
		
int interpolationSearch_r(int val, std::vector<int> nums, int lo, int hi) {
	if (lo > hi || val > nums[hi] || val < nums[lo]) {
		return -1;
	}

	int index = lo + (val - nums[lo]) * ((hi - lo)/(nums[hi] - nums[lo]));
	
	if (nums[index] == val) {
		return index;
	}
	else if (nums[index] < val) {
		return binarySearch_r(val, nums, index + 1, hi);
	}
	else {
		return binarySearch_r(val, nums, lo, hi - 1);
	}
}
int interpolationSearch_r(int val, std::vector<int> nums) {
	return binarySearch_r(val, nums, 0, nums.size() - 1);
}
