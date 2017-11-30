/*********************************************************************
** Program name: TSP
** Author: Group 14
** Date: 29 November 2017
** Description: **FILL IN**
*********************************************************************/

#ifndef CITIES_HPP
#define CITIES_HPP

#include <vector>
#include <string>
#include <set>

//function prototype for connectCity
int connectCity(struct Node*, struct Node*);

//function prototype for getNearestNeighbor
int getNearestNeighbor(struct Node*, std::set<int>&);

//function prototype for createCityMap
void createCityMap(std::map<int, Node*>& , std::map<int, std::pair<int, int>>& );

#endif
