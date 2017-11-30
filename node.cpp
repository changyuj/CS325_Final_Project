/*********************************************************************
** Program name: TSP
** Author: Group 14
** Date: 29 November 2017
** Description: node functions
*********************************************************************/

#include "node.hpp"


Node* createNode(int id, int x, int y, std::map<int, int>* adjList)
{
    Node* newNode = new Node;

	newNode->cityID = id;
	newNode->xCoordinate = x;
	newNode->yCoordinate = y;
	newNode->next = NULL;
    newNode->prev = NULL;
    newNode->adjacencyList = *adjList;

    return newNode;
}

void reconnectNodes(std::vector<int> route, std::map<int, Node*>& cityMap)
{
    Node* startNode = cityMap[route[0]];
    Node* current = startNode;
    for (int i = 0; i < route.size(); i++)
    {
        if (i == route.size() - 1)
            connectCity(cityMap[route[i]], cityMap[route[0]]);
        else
            connectCity(cityMap[route[i]], cityMap[route[i + 1]]);
    }
}
