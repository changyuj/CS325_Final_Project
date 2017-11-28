/*********************************************************************
** Program name: mergesort
** Author: Katherine Isabella
** Date: 21 October 2017
** Description: This  file contains the implemented functions for
**				mergeSort function and the merge function. The
**				mergeSort function recursively cuts the array in half
**				and then calls the merge function which merges two
**				sorted lists together. Modified to
**				accept a vector holding a pair. Sorts the second value
**				of the pair in increasing order
**
** CITATION: Created for CS325 Homework 4 and modified for the TSP Project
*********************************************************************/
#include "mergeSort.hpp"

/*********************************************************************
** Function: mergeSort
** Description: Sorts an array of integers by recursively splitting
**				an array in half until it cannot anymore, and
**				then merging the sorted halves together using the
**				merge function.
** Parameters: std::vector<int>& arrayOfInts, the array of integers
**				to be sorted
** Pre-Conditions: none
** Post-Conditions: arrayOfInts holds a sorted list of integers
*********************************************************************/
void mergeSort(std::vector<std::pair<std::string, int>>& arrayOfInts) {

	//if the size of the array is 1 or less, then the array is already sorted and nothing needs to be done
	if (arrayOfInts.size() > 1) {

		//use info from the following link to split the vector into two arrays
		//http://www.cplusplus.com/reference/vector/vector/vector/
		std::vector<std::pair<std::string, int>> rightArray((arrayOfInts.begin() + (arrayOfInts.size() / 2)), arrayOfInts.end());
		std::vector<std::pair<std::string, int>> leftArray(arrayOfInts.begin(), (arrayOfInts.begin() + (arrayOfInts.size() / 2)));

		//calls mergeSort recursively on each half of the array
		mergeSort(rightArray);
		mergeSort(leftArray);

		//merges the two arrays
		merge(arrayOfInts, rightArray, leftArray);
	}
}


/*********************************************************************
** Function: merge
** Description: Merges two sorted arrays into a combined sorted array.
**				Used for the mergeSort algorithm
** Parameters: std::vector<int>& mergedList, the array which will
**			hold the sorted combination of rightArray and leftArray;
**			std::vector<int>& rightArray, the sorted array which holds
**			the right-half of the total mergedList array;
**			std::vector<int>& leftArray, the sorted array which holds
**			the left-half of the total mergedList array;
** Pre-Conditions: rightArray and leftArray are sorted
** Post-Conditions: mergedList holds the sorted combination of
**					leftArray and rightArray
*********************************************************************/
void merge(std::vector<std::pair<std::string, int>>& mergedList, std::vector<std::pair<std::string, int>>& rightArray,
	std::vector<std::pair<std::string, int>>& leftArray) {

	//variables for keeping track which element is next to be accessed in each array
	int mergedListLocation = 0;
	int rightArrayLocation = 0;
	int leftArrayLocation = 0;

	/*
	**while there are still elements to be accessed in both the left and right arrays,
	**goes through the arrays and merges them into the mergedList
	*/
	while (rightArrayLocation < rightArray.size() && leftArrayLocation < leftArray.size()) {

		/*
		**if the next element in the right array is larger than the
		**element in the left array, puts it into the mergedList
		**otherwise, places the next element from the left array in the
		**mergedList
		*/

		if (rightArray[rightArrayLocation].second < leftArray[leftArrayLocation].second) {

			mergedList[mergedListLocation] = rightArray[rightArrayLocation];

			//increments the rightArrayLocation to get the next element in the rightArray
			rightArrayLocation++;
		}
		else {

			mergedList[mergedListLocation] = leftArray[leftArrayLocation];

			//increments theleftArrayLocation to get the next element in the leftArray
			leftArrayLocation++;
		}

		mergedListLocation++;
	}

	//goes through and adds any leftover integers from the left array into the merged array
	while (leftArrayLocation < leftArray.size()) {
		mergedList[mergedListLocation] = leftArray[leftArrayLocation];
		leftArrayLocation++;
		mergedListLocation++;
	}

	//goes through and adds any leftover integers from the right array into the merged array
	while (rightArrayLocation < rightArray.size()) {
		mergedList[mergedListLocation] = rightArray[rightArrayLocation];
		rightArrayLocation++;
		mergedListLocation++;
	}
}