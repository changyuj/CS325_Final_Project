#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <limits>
#include <set>

using namespace std;

struct Node
{
	int cityID;
	int xCoordinate;
	int yCoordinate;
	Node* connectingCity;
    map<int, int> adjacencyList;
};

int calculateDistance(int x1, int x2, int y1, int y2) {

	double xCoordCalc = x1 - x2;
	double yCoordCalc = y1 - y2;

	double distance = std::sqrt(std::pow(xCoordCalc, 2) + std::pow(yCoordCalc, 2));
    // cout << "(" << x1 << ", " << y1 << ") -> (" << x2 << ", " << y2 <<"): " << distance << endl;

	return (int) round(distance);
}

Node* createNode(int id, int x, int y, map<int, int>* adjList)
{
    Node* newNode = new Node;

	newNode->cityID = id;
	newNode->xCoordinate = x;
	newNode->yCoordinate = y;
	newNode->connectingCity  = NULL;
    newNode->adjacencyList = *adjList;

    return newNode;
}

int connectCity(struct Node* fromNode, struct Node* toNode)
{
    fromNode->connectingCity = toNode;
    int distance = fromNode->adjacencyList.find(toNode->cityID)->second;

    return distance;
}

// int getNearestNeighbor(struct Node* current, set<int>& visited)
// {
//     int minDistance = numeric_limits<int>::max();
//     int minId = -1;
//
//     while (minId == -1)
//     {
//         for (map<int, int>::iterator itr = current->adjacencyList.begin(); itr != current->adjacencyList.end(); itr++)
//         {
//             set<int>::iterator it = visited.find(itr->first);
//             if (itr->second < minDistance)
//             {
//                 minDistance = itr->second;
//                 minId = itr->first;
//                 cout << "Min city " << itr->first << ", Distance " << itr->second << endl;
//             }
//         }
//     }
//     return minId;
// }

int main(int argc, char *argv[])
{

	//read in file from argument
    ifstream readFile;
    readFile.open(argv[1]);
    if (!readFile) {
        cout << "Cannot open file: " << argv[1] << endl;
        // exit(1);
    }

    string line;
	int id, xCoor, yCoor;
    int numCities = 0;
    map< int, pair<int, int> > cities;
    while(readFile >> id >> xCoor >> yCoor)
    {
        cities[id] = pair<int, int> (xCoor, yCoor);
        numCities++;
    }

    // Create city nodes
    map< int, map<int, int> > adjMatrix;  // adjacency matrix
    map<int, int> adjList;  // adjacency list for a single city
    map<int, Node*> cityMap;  // map of cities

    for (map< int, pair<int, int> >::iterator itr_thisCity = cities.begin(); itr_thisCity != cities.end(); itr_thisCity++)
    {
        adjList.clear();
        // calulate distances for adjacency list
        for (map< int, pair<int, int> >::iterator itr_otherCity = cities.begin(); itr_otherCity != cities.end(); itr_otherCity++)
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

    // connect all the nodes in the order they were read in
    int total = 0;
    map<int, Node*>::iterator next = cityMap.begin();
    for (map<int, Node*>::iterator itr = cityMap.begin(); itr != cityMap.end(); itr++)
    {
        next++;
        if (next == cityMap.end())  // connect last city to first city for cycle
            next = cityMap.begin();
            // total += connectCity(itr->second, itr->second + 1);
        total += connectCity(itr->second, next->second);
        cout << "Add city " << itr->first << " -> " << next->first << ": "<< total << endl;
    }
    // set<int> visited;
    // visited.insert(getNearestNeighbor(next->second, visited));
    // for (set<int>::iterator it = visited.begin(); it != visited.end(); it++)
    //     cout << it << endl;

    readFile.close();

    return 0;
}
