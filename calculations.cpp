/*********************************************************************
** Program name: TSP
** Author: Group 14
** Date: 29 November 2017
** Description: calculation functions
*********************************************************************/

#include "calculations.hpp"

//calculates the Euclidean distance between two cities
int calculateDistance(int x1, int x2, int y1, int y2) {

	int xCoordCalc = x1 - x2;
	int yCoordCalc = y1 - y2;

	double distance = std::sqrt(std::pow(xCoordCalc, 2) + std::pow(yCoordCalc, 2));
    // cout << "(" << x1 << ", " << y1 << ") -> (" << x2 << ", " << y2 <<"): " << distance << endl;

	return (int) round(distance);
}

//goes through the route to calculate the total distance of the tour
int calculateTotalDistance(std::vector<int> route, std::map<int, Node*>& cityMap) {
    int totalDistance = 0;
    int distance;
    int nextCity;

    for (int i = 0; i < route.size(); i++)
    {
        if (i == route.size() - 1)
            distance = cityMap[route[i]]->adjacencyList.find(route[0])->second;
        else
            distance = cityMap[route[i]]->adjacencyList.find(route[i + 1])->second;
        totalDistance += distance;
    }
    return totalDistance;
}
