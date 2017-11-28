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

	int xCoordCalc = x1 - x2;
	int yCoordCalc = y1 - y2;

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

int getNearestNeighbor(struct Node* current, set<int>& tour)
{
    int minDistance = numeric_limits<int>::max();
    int minId = -1;
    set<int>::iterator it;

    while (minId == -1)
    {
        for (map<int, int>::iterator itr = current->adjacencyList.begin(); itr != current->adjacencyList.end(); itr++)
        {
            it = tour.find(itr->first);
            if (itr->second < minDistance && it == tour.end())
            {
                minDistance = itr->second;
                minId = itr->first;
                // cout << "Min city " << itr->first << ", Distance " << itr->second << endl;
            }
        }
    }
    return minId;
}

void createCityMap(map<int, Node*>& cityMap, map< int, pair<int, int> >& cities)
{
    map< int, map<int, int> > adjMatrix;  // adjacency matrix
    map<int, int> adjList;  // adjacency list for a single city

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
}

int main(int argc, char *argv[])
{
    clock_t start = clock();

	//read in file from argument
    string infile = "";
    infile = argv[1];
    ifstream readFile;
    readFile.open(infile);

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
    readFile.close();

    // Create city nodes
    map<int, Node*> cityMap;  // map of cities
    createCityMap(cityMap, cities);
    int total = 0;

    // // connect all the nodes in the order they were read in
    // map<int, Node*>::iterator next = cityMap.begin();
    // for (map<int, Node*>::iterator itr = cityMap.begin(); itr != cityMap.end(); itr++)
    // {
    //     next++;
    //     if (next == cityMap.end())  // connect last city to first city for cycle
    //         next = cityMap.begin();
    //         // total += connectCity(itr->second, itr->second + 1);
    //     total += connectCity(itr->second, next->second);
    //     cout << "Add city " << itr->first << " -> " << next->first << ": "<< total << endl;
    // }

    Node* startNode = cityMap[0];
    Node* current = startNode;
    set<int> tour;
    tour.insert(startNode->cityID);
    // loop until all cities are visited
    do
    {
        int minId = getNearestNeighbor(current, tour);
        tour.insert(minId);
        total += connectCity(current, cityMap[minId]);
        // current->connectingCity = cityMap[minId];
        // total += current->adjacencyList.find(minId)->second;
        current = current->connectingCity;
    } while (tour.size() < numCities);
    // connect the last city to the first one to complete the tour
    total += connectCity(current, startNode);
    // current->connectingCity = startNode;
    // total += current->adjacencyList.find(startNode->cityID)->second;

    string outfile = infile + ".tour";
    ofstream writeFile;
    writeFile.open(outfile);
    writeFile << total << endl;

    // output tour to screen
    Node* traverse = startNode;
    do
    {
        writeFile << traverse->cityID << endl;
        traverse = traverse->connectingCity;
    } while(traverse != startNode);

    writeFile.close();

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time elapsed: " << elapsed << endl;

    return 0;
}
