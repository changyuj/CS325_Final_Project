/*********************************************************************
** Program name: TSP
** Author: Katherine Isabella - Group 14
** Date: 26 November 2017
** Description: This  file contains the implemented function for
**				the calculateDistance function. The calculateDistance
**				function works by taking in two city nodes each
**				containing x and y coordinates. Using these coordinates.
**				Using these coordinates, the program calculates and
**				returns the Euclidean distance between the nodes.
*********************************************************************/

#include "calculateDistance.hpp"

/*********************************************************************
** Function: calculateDistance
** Description: This function takes in two nodes each containing
**				x and y coordinates. It then calculates and returns
**				the Euclidean distance between the nodes using the 
**				formula: squareRoot((x1-x2)^2 + (y1-y2)^2)
** Parameters:  Node* cityOne, a node containing info (coordinates, id)
**				on the first city; 
**				Node* cityTwo, a node containing info
**				on the second city
** Pre-Conditions: cityOne is not null and cityTwo is not null
** Post-Conditions: the function will return the distance between the
**					Euclidean distance between the nodes.
*********************************************************************/
int calculateDistance(Node* cityOne, Node* cityTwo) {

	int xCoordCalc = cityOne->xCoordinate - cityTwo->xCoordinate;
	int yCoordCalc = cityOne->yCoordinate - cityTwo->yCoordinate;

	int distance = std::sqrt(std::pow(xCoordCalc, 2) + std::pow(yCoordCalc, 2));

	return distance;
}