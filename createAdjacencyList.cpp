/*********************************************************************
** Program name: TSP
** Author: Katherine Isabella - Group 14
** Date: 28 November 2017
** Description: **FILL IN**
*********************************************************************/

#include "createAdjacencyList.hpp"
#include <iostream>
#include <sstream> 
#include <fstream>


/*********************************************************************
** Function: createAdjacencyList
** Description: **FILL IN**
** Parameters:  **FILL IN**
** Pre-Conditions: cityList is not null or empty
** Post-Conditions: **FILL IN**
*********************************************************************/

std::unordered_map<int, std::vector<std::pair<int, int>>> createAdjacencyList(std::vector<std::pair<int, std::pair<int, int>>> & cityList){

	std::unordered_map<int, std::vector<std::pair<int, int>>> adjacencyListandWeights;



	//goes through each of the cities and calculates all of the edge weights for that city
	for (int i = 0; i < cityList.size(); i++) {

		//gests the current city's x and y coordinates
		int xCoordOne = cityList[i].second.first;
		int yCoordOne = cityList[i].second.second;

		std::vector<std::pair<int, int>> adjacencyList;

		for (int j = 0; j < cityList.size(); j++) {

			if (j != i) {
				//gets the next city's x and y coordinates
				int xCoordTwo = cityList[j].second.first;
				int yCoordTwo = cityList[j].second.second;


				//calculates the Euclidean distance between the cities
				int xCoordCalc = xCoordOne - xCoordTwo;
				int yCoordCalc = yCoordOne - yCoordTwo;
				int distance = std::sqrt(std::pow(xCoordCalc, 2.0) + std::pow(yCoordCalc, 2.0));


				//creates a pair of the combined city names and the calculated distance between them and adds it to the edgeList
				std::pair<int, int> cityDistancePair(cityList[j].first, distance);
				adjacencyList.push_back(cityDistancePair);
			}
		}

		std::pair<int, std::vector<std::pair<int, int>>> currentPair(cityList[i].first, adjacencyList);
		adjacencyListandWeights.insert(currentPair);
	}


	std::ofstream outputFile("adjacencyLists.txt");
	for (int i = 0; i < cityList.size(); i++) {

		outputFile << "\n" <<  cityList[i].first << "\n";

		for (int j = 0; j < adjacencyListandWeights[cityList[i].first].size(); j++) {
			outputFile << adjacencyListandWeights[cityList[i].first][j].first << " " << adjacencyListandWeights[cityList[i].first][j].second << std::endl;
		}

		outputFile << "\n";
	}

	outputFile.close();

	return adjacencyListandWeights;
}