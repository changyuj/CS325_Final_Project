/*********************************************************************
** Program name: TSP Problem
** Author: Katherine Isabella - Group 15
** Date: 28 November 2017
** Description: **FILL IN**
**
*********************************************************************/


#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>
#include <utility>  
#include <vector>

#include "calculateEdgeList.hpp"
int main(int argc, char** argv)
{

	//gets the name of the file from the command line
	std::string fileName = "";
	if (argc > 1)
	{
		fileName = argv[1];
	}
	std::string currentString;

	//opens the file to read
	std::ifstream inputFile(fileName);

	//checks if the file is open and working properly
	if (inputFile.is_open()) {

		std::string currentString; 

		std::vector<std::pair<std::string, std::pair<int, int>>> cities;
		int cityID;
		int xCoord;
		int yCoord;

		//gets the next inputted line 
		while (getline(inputFile, currentString)) {

			//adds the input into the proper variables
			std::istringstream currentLine(currentString);
			currentLine >> cityID;
			currentLine >> xCoord;
			currentLine >> yCoord;
			
			//changes the cityID to a string for ease of use later on
			std::string stringCity = std::to_string(cityID);

			//creates the pair of x and y coordinates and then creates the pair of city + coordinates
			std::pair<int, int> coordinatePair(xCoord, yCoord);
			std::pair<std::string, std::pair<int, int>> cityAndCoordPair(stringCity, coordinatePair);
			cities.push_back(cityAndCoordPair);
		}


		//creates a vector holding a calculated edge list
		std::vector<std::pair<std::string, int>>  cityDistances = calculateEdgeList(cities);

		//close the input file
		inputFile.close();
	}

	//if the file cannot be opened, displays a message alerting the user
	else {
		std::cout << "There was an error in reading " << fileName << std::endl;
	}

	return 0;
}