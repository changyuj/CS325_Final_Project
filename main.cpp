/*********************************************************************
** Program name: TSP Problem
** Author: Group 14
**         Katherine Isabella
**         Kenny Lew
**         Yu Ju Chang
** Date: 29 November 2017
** Description: This program creates a route for the TSP and finds
**              an approximate solution using Nearest Neighbor,
**              Simulated Annealing, and 2-Opt Swap.
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
    srand(10000);  // set the random generator seed

    // make sure program does not run for more than 3 minutes
    clock_t clock_start = clock();
    time_t start = time(NULL);
    time_t seconds = 175;
    time_t endwait = start + seconds;


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

		Node* startNode = cityMap[rand() % numCities];

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

        // int bestDistance = two_opt(currentRoute, cityMap, total, startNode);

        /*
        Optimization - Simulated Annealing
        */
        bool improve = true;
        int bestDistance = total;  // start with Nearest Neighbor solution
        int newDistance;
        std::vector<int> newRoute;

        // index of city in route list
        int i, k;

        // Simulated Annealing parameters
    	double temperature = 1;
    	double coolingRate = 0.99;
    	double minTemperature = 0.0001;
    	double acceptanceProbability, randomProbability;
    	int numIterations = 1000;

    	int j;  // loop counter
        if (numCities > 2000)
            minTemperature = 0.001;

        // std::cout << bestDistance << std::endl;
        while (temperature > minTemperature && improve)
        {
    		for (j = 0; j < numIterations; j++)
    			{
                // select two random cities
    	        do {
    	            i = rand() % numCities;
    	        } while (i == 0 || i == (numCities-1));
    	        do {
    	            k = rand() % numCities;
    	        } while (k <= i);

                // check if swapping the cities in the route makes a better solution
    	        newRoute = twoOptSwap(startNode, cityMap[currentRoute[i]], cityMap[currentRoute[k]]);
    	        newDistance = calculateTotalDistance(newRoute, cityMap);

                //do nothing if the solution is the same
    	        if (newDistance == bestDistance)
    			{
    				continue;
    			}
                // swap if the new solution is better
    			else if (newDistance < bestDistance)
    	        {
    	            currentRoute = newRoute;
    	            reconnectNodes(currentRoute, cityMap);
    				bestDistance = calculateTotalDistance(currentRoute, cityMap);
    				// std::cout << bestDistance << std::endl;
    	        }
                // possibly still wap if new solution is worse
    			else
    			{
    				acceptanceProbability = exp((bestDistance - newDistance) / temperature);
    				randomProbability = (double) (rand() / (RAND_MAX + 1.0));
    				if (acceptanceProbability > randomProbability)
    				{
    					// std::cout << bestDistance << std::endl;
    					currentRoute = newRoute;
    					reconnectNodes(currentRoute, cityMap);
    					bestDistance = calculateTotalDistance(currentRoute, cityMap);
    				}
    			}
                // COMMENT OUT IF RUNNING WITH UNLIMITED TIME
                // check if program has run for 3 minutes
    		    start = time(NULL);
    		    if (start >= endwait)
    		    {   // stop program if run for 3 minutes
    		        improve = false;
    		        break;
    		    }
    		}
            // cooling
    		temperature *= coolingRate;
        }
		std::cout << "Distance: " << bestDistance << std::endl;

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
		clock_t clock_end = clock();
		double elapsed = (double)(clock_end - clock_start) / CLOCKS_PER_SEC;
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
