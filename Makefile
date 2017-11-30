###
## Project Name: CS325 TSP Project  Makefile
## Author: Katherine Isabella
## Date: 28 November 2017
## Description: A simple makefile creates an  executable file, and cleans extraneous files.
## Citations: Uses template from the Lecture Video: " ~rookert/cs162/03" and information from Harlan's makefile template
###

#target: dependencies
#	rule to build
#

tspProject: main.cpp calculations.cpp calculations.hpp cities.cpp cities.hpp node.cpp node.hpp twoOpt.cpp twoOpt.hpp
	g++ -std=c++0x main.cpp calculations.cpp cities.cpp node.cpp twoOpt.cpp -o tspProject

#cleans extraneous files
clean:
	rm -f *.o tspProject
