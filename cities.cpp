/*********************************************************************
** Program name: TSP
** Author: Group 14
** Date: 29 November 2017
** Description: cities functions
*********************************************************************/

#include <limits>
#include <map>
#include "node.hpp"
#include "calculations.hpp"
#include "cities.hpp"

// establishes route between two city nodes
// returns the distance between them
int connectCity(struct Node* fromNode, struct Node* toNode) {

    fromNode->next = toNode;
    toNode->prev = fromNode;
    int distance = fromNode->adjacencyList.find(toNode->cityID)->second;

    return distance;
}

int getNearestNeighbor(struct Node* current, std::set<int>& visited) {

    int minDistance = std::numeric_limits<int>::max();
    int minId = -1;
    std::set<int>::iterator it;

    while (minId == -1)
    {
        for (std::map<int, int>::iterator itr = current->adjacencyList.begin(); itr != current->adjacencyList.end(); itr++)
        {
            it = visited.find(itr->first);
            if (itr->second < minDistance && it == visited.end())
            {
                minDistance = itr->second;
                minId = itr->first;
                // cout << "Min city " << itr->first << ", Distance " << itr->second << endl;
            }
        }
    }
    return minId;
}

void createCityMap(std::map<int, Node*>& cityMap, std::map<int, std::pair<int, int>>& cities)
{
    std::map<int, std::map<int, int>> adjMatrix;  // adjacency matrix
    std::map<int, int> adjList;  // adjacency list for a single city

    // each city
    for (std::map<int, std::pair<int, int>>::iterator itr_thisCity = cities.begin(); itr_thisCity != cities.end(); itr_thisCity++)
    {
        adjList.clear();
        // calulate distances to all other cities for adjacency list
        for (std::map<int, std::pair<int, int>>::iterator itr_otherCity = cities.begin(); itr_otherCity != cities.end(); itr_otherCity++)
        {
            if (itr_otherCity->first != itr_thisCity->first) {
                adjList[itr_otherCity->first] = calculateDistance(itr_thisCity->second.first, itr_otherCity->second.first, itr_thisCity->second.second, itr_otherCity->second.second);
            }
        }
        // add city adjaceny list to adjacency matrix
        adjMatrix[itr_thisCity->first] = adjList;

        // create city node
        cityMap[itr_thisCity->first] = createNode(itr_thisCity->first, itr_thisCity->second.first, itr_thisCity->second.second, &adjMatrix[itr_thisCity->first]);
    }
}
