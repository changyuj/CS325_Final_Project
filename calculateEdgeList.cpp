/*********************************************************************
** Program name: TSP
** Author: Katherine Isabella - Group 14
** Date: 28 November 2017
** Description: **FILL IN**
*********************************************************************/

#include "calculateEdgeList.hpp"

/*********************************************************************
** Function: calculateEdgeList
** Description: **FILL IN**
** Parameters:  **FILL IN**
** Pre-Conditions: cityList is not null or empty
** Post-Conditions: the function will return a list of all the 
**					calculated edges in the city map
*********************************************************************/

std::vector<std::pair<std::string, int>> calculateEdgeList(std::vector<std::pair<std::string, std::pair<int, int>>>& cityList){

	std::vector<std::pair<std::string, int>> edgeList;

	//goes through each of the cities and calculates all of the edge weights for that city
	for (int i = 0; i < cityList.size(); i++) {

		//gests the current city's x and y coordinates
		int xCoordOne = cityList[i].second.first;
		int yCoordOne = cityList[i].second.second;

		for (int j = i+1; j < cityList.size(); j++) {

			//gets the next city's x and y coordinates
			int xCoordTwo = cityList[j].second.first;
			int yCoordTwo = cityList[j].second.second;


			//calculates the Euclidean distance between the cities
			int xCoordCalc = xCoordOne - xCoordTwo;
			int yCoordCalc = yCoordOne - yCoordTwo;
			int distance = std::sqrt(std::pow(xCoordCalc, 2.0) + std::pow(yCoordCalc, 2.0));

			//gives the two cities a combined identifier
			std::string combinedCities = cityList[i].first +"," + cityList[j].first;

			//creates a pair of the combined city names and the calculated distance between them and adds it to the edgeList
			std::pair<std::string, int> cityDistancePair(combinedCities, distance);
			edgeList.push_back(cityDistancePair);
		}
	}

	return edgeList;
}