/*********************************************************************
** Program name: TSP Problem
** Author: Group 15
** Date: 29 November 2017
** Description: This program creates a route for the TSP and finds
**              the optimum solution.
**
*********************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <time.h>
#include "node.hpp"
#include "twoOpt.hpp"
#include "cities.hpp"

int main(int argc, char *argv[])
{
    clock_t start = clock();

	//gets the name of the file from the command line
    std::string fileName = "";
    if (argc > 1)
	{
		fileName = argv[1];
	}
	//opens the file to read
    std::ifstream inputFile(fileName);

	//checks if the file is open and working properly
    if(inputFile.is_open()) {

		std::string currentString;
		int id, xCoord, yCoord;

		std::map<int, std::pair<int, int> > cities;

		int numCities = 0;
		//gets the next inputted line
		while(getline(inputFile, currentString)) {

			//adds the input into the proper variables
			std::istringstream currentLine(currentString);
			currentLine >> id;
			currentLine >> xCoord;
			currentLine >> yCoord;

			cities[id] = std::pair<int, int> (xCoord, yCoord);
			numCities++;
		}

		// Create city nodes
		std::map<int, Node*> cityMap;  // map of cities
		createCityMap(cityMap, cities);
		int total = 0;
		std::vector<int> currentRoute;

		Node* startNode = cityMap[0];

		// Nearest neighbor algorithm
		Node* current = startNode;
		std::set<int> visited;
		visited.insert(startNode->cityID);
		currentRoute.push_back(current->cityID);

		// loop until all cities are visited
		do {
			int minId = getNearestNeighbor(current, visited);
			visited.insert(minId);
			total += connectCity(current, cityMap[minId]);
			current = current->next;
			currentRoute.push_back(current->cityID);
		} while (visited.size() < numCities);

		// connect the last city to the first one to complete the tour
		total += connectCity(current, startNode);

        int bestDistance = two_opt(currentRoute, cityMap, total, startNode);

		// output tour to file
		std::string outfile = fileName + ".tour";
		std::ofstream writeFile;
		writeFile.open(outfile);
		writeFile << bestDistance << std::endl;

		Node* traverse = startNode;

		do
		{
			writeFile << traverse->cityID << std::endl;
			traverse = traverse->next;
		} while(traverse != startNode);

		writeFile.close();

		// output time to run
		clock_t end = clock();
		double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
		std::cout << "Time elapsed: " << elapsed << std::endl;

		//close the input file
		inputFile.close();
	}

	//if the file cannot be opened, displays a message alerting the user
	else {
        std::cout << "There was an error in reading " << fileName << std::endl;
    }
    return 0;
}
