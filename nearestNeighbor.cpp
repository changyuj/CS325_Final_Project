/*********************************************************************
** Program name: TSP
** Author: Katherine Isabella - Group 14
** Date: 28 November 2017
** Description: **FILL IN**
*********************************************************************/

#include "nearestNeighbor.hpp"


/*********************************************************************
** Function: nearestNeighbor
** Description: **FILL IN**
** Parameters:  **FILL IN**
** Pre-Conditions: cityList and adjacencyListWithWeights is not null 
**					or empty 
** Post-Conditions: **FILL IN**
*********************************************************************/

std::vector<std::pair<int, int>> nearestNeighbor(std::vector<std::pair<int, std::pair<int, int>>>& cityList, std::unordered_map<int, 
	std::vector<std::pair<int, int>>>& adjacencyListWithWeights){
	
	std::vector<std::pair<int, int>> nearestNeighborList;

	std::unordered_map<int, bool> availableVertices;

	
	for (int i = 0; i < cityList.size(); i++) {
		std::pair<int, bool> currentPair(cityList[i].first, true);
		availableVertices.insert(currentPair);

		//sorts the lists from least to greatest
		std::vector<std::pair<int, int>> currentAdjacencyList = adjacencyListWithWeights[cityList[i].first];
		mergeSort(currentAdjacencyList);
		adjacencyListWithWeights[cityList[i].first] = currentAdjacencyList;
	}
	
	int currentVertex = cityList[0].first;
	std::pair<int, int> firstPair(currentVertex, 0);
	nearestNeighborList.push_back(firstPair);

	for (int i = 1; i < cityList.size(); i++) {

		std::vector<std::pair<int, int>> currentAdjacencyList = adjacencyListWithWeights[cityList[i].first];
		bool foundNext = false;

		for (int j = 0; j < currentAdjacencyList.size() && !foundNext; j++) {
			if (availableVertices[currentAdjacencyList[j].first]) {

				foundNext = true;

				currentVertex = currentAdjacencyList[j].first;
				availableVertices[currentAdjacencyList[j].first] = false;
				std::pair<int, int> neighborPair(currentAdjacencyList[j].first, currentAdjacencyList[j].second);
				nearestNeighborList.push_back(neighborPair);
			}
		}

	}

	//loop back to the start of the cycle
	for (int i = 1; i < adjacencyListWithWeights[currentVertex].size(); i++) {

		if (adjacencyListWithWeights[currentVertex][i].first == cityList[0].first) {
			std::pair<int, int> neighborPair(adjacencyListWithWeights[currentVertex][i].first, adjacencyListWithWeights[currentVertex][i].second);
			nearestNeighborList.push_back(neighborPair);
		}
	}

	return nearestNeighborList;
}