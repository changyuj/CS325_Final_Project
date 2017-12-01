/*********************************************************************
** Program name: TSP
** Author: Group 14
** Date: 29 November 2017
** Description: **Node functions for creating and connecting nodes**
*********************************************************************/

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <string>
#include <map>
#include "cities.hpp"


struct Node
{
	int cityID;
	int xCoordinate;
	int yCoordinate;
	Node* next;
    Node* prev;
    std::map<int, int> adjacencyList;
};

//function prototype for createNode
Node* createNode(int, int, int, std::map<int, int>*);

//function prototype for reconnectNodes
void reconnectNodes(std::vector<int>, std::map<int, Node*>&);

#endif
