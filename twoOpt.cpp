/*********************************************************************
** Program name: TSP
** Author: Group 14
** Date: 29 November 2017
** Description: two-opt algorithm functions
*********************************************************************/

#include "twoOpt.hpp"

/*
//performs two-opt optimization 
int two_opt(std::vector<int> &currentRoute, std::map<int, Node*> & cityMap,int total, Node* &startNode) {
	bool improve = true;
    int bestDistance = total;
    int newDistance;
    std::vector<int> newRoute;
    do
    {
        improve = false;
        bestDistance = calculateTotalDistance(currentRoute, cityMap);
        std::cout << bestDistance << std::endl;
        for (int i = 1; i < currentRoute.size() - 1; i++)
        {
            for (int k = i + 1; k < currentRoute.size(); k++)
            {
                newRoute = twoOptSwap(startNode, cityMap[currentRoute[i]], cityMap[currentRoute[k]]);
                newDistance = calculateTotalDistance(newRoute, cityMap);
                if (newDistance < bestDistance)
                {
                    currentRoute = newRoute;
                    reconnectNodes(currentRoute, cityMap);
                    improve = true;
                }
            }
        }
    } while (improve);
    return bestDistance;
}
*/

// performs a swap so that routes of the two nodes do not cross over each other
std::vector<int> twoOptSwap(struct Node* startNode, struct Node* i, struct Node* k) {
    std::vector<int> newRoute;
    Node* current = startNode;
    while (current != i)
    {
        newRoute.push_back(current->cityID);
        current = current->next;
    }
    current = k;
    while (current->next != i)
    {
        newRoute.push_back(current->cityID);
        current = current->prev;
    }
    current = k->next;
    while (current != startNode)
    {
        newRoute.push_back(current->cityID);
        current = current->next;
    }
    return newRoute;
}
