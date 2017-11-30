/*********************************************************************
** Program name: TSP
** Author: Group 14
** Date: 29 November 2017
** Description: **FILL IN**
*********************************************************************/

#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP

#include <vector>
#include <string>
#include <map>
#include <cmath>
#include "node.hpp"

//function prototype for calculateDistance
int calculateDistance(int, int, int, int);

//function prototype for calculateTotalDistance
int calculateTotalDistance(std::vector<int>, std::map<int, Node*>&);
#endif
