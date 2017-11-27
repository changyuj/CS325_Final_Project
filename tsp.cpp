#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>

using namespace std;

struct Node
{
	int cityID;
	int xCoordinate;
	int yCoordinate;
	Node* connectingCity;
};
/****************
initial node
*****************/
void initNode(struct Node *head, int id, int x, int y)
{
	head->cityID = id;
	head->xCoordinate = x;
	head->yCoordinate = y;
	head->connectingCity  = NULL;
}
/****************
apending node
*****************/
void addNode(struct Node *head, int id, int x, int y) {
	Node *newNode = new Node;
	newNode->cityID = id;
	newNode->xCoordinate = x;
	newNode->yCoordinate = y;
	newNode->connectingCity = NULL;

	Node *cur = head;
	while(cur) {
		if(cur->connectingCity == NULL) {
			cur->connectingCity = newNode;
			return;
		}
		cur = cur->connectingCity;
	}
}
/****************
display node
*****************/
void display(struct Node *head) {
	Node *tempList = head;
	while(tempList) {
		cout << tempList->cityID << " " <<  tempList->xCoordinate << " " << tempList-> yCoordinate << endl;;
		tempList = tempList->connectingCity;
	}
	cout << endl;
}


/****************
  main function
*****************/
int main(int argc, char *argv[])
{
	struct Node *head = new Node;

	//read in file from argument
    ifstream readFile(argv[1]);

	int id, xCoor, yCoor;
	//initial city
	cin >> id >> xCoor >> yCoor;

	initNode(head, id, xCoor, yCoor);
//	cout << "read in first city info: " << "city-" << id <<" x: " <<xCoor<<" y: "<<yCoor<<endl;
	display(head);     //checking if read in correctly

	int counter=0;
    while(cin >> id >> xCoor >> yCoor)
    {
        addNode(head, id, xCoor, yCoor);
        counter++;
    }
    display(head);    //checking if read in correctly
	cout << counter<<endl;

    readFile.close();

    return 0;
}
