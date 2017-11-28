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

#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <vector>
#include<utility>
#include<string>

//function prototype for mergeSort
void mergeSort(std::vector<std::pair<int, int>>&);

//helper function for mergeSort which merges two sorted lists
void merge(std::vector<std::pair<int, int>>&, std::vector<std::pair<int, int>>&, std::vector<std::pair<int, int>>&);


#endif
