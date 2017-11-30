/*********************************************************************
** Program name: TSP
** Author: Group 14
** Date: 29 November 2017
** Description: header file for twoOpt.cpp. Defines function prototype
*********************************************************************/

#ifndef TWOOPT_HPP
#define TWOOPT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "calculations.hpp"
#include "node.hpp"

//function prototype for two_opt
int two_opt(std::vector<int> &, std::map<int, Node*> &, int, Node* &);

//function prototype for twoOptSwap
std::vector<int> twoOptSwap(struct Node*, struct Node*, struct Node*);

#endif
