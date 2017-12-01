Project Name: CS325 - TSP Project
Author: Group 14
Date: November 30, 2017

Description: This folder contains one program: tspProject. This program reads in from a file specified in the command line at run time. Each line of the file should include a city id, then an x-coordinate, and then a y-coordinate, each separated with a space. All the cities and their coordinates in the file are read, and then the program will call then create a tour of the cities using the chosen TSP algorithms. After, the program will create a file (named by taking the input file name and adding .tour to the end) and output on the first line the total distance of the tour and each following line will contain the next city in the tour. 

An example of how the file should be formatted is below:

0 6 8
1 12 21
5 11 20
3 6 7

Using the above file information, the output will be:

<calculated total distance>
0
3
5
1

How to Run: To run the program there is a makefile included with the project. To use the makefile on flip, use the "make" command in the same folder containing the file with the cities and coordinates (your input file), Makefile, main.cpp, calculations.cpp, calculations.hpp, node.cpp, node.hpp, cities.cpp, cities.hpp, twoOpt.cpp, and twoOpt.hpp. This will compile the program. To run the program, you must then type in "tspProject" followed by the name of your input file (for example: "tspProject tsp_example_1.txt") and press enter. Once tspProject completes running, you will see the output .tour file in the same folder.

Once you are done with the programs you can use the "make clean" command to remove the tspProject program.

Other: Please note, there are two sets of .tour files included - competition_time and unlimited_time. Due to the fact our algorithms take > 3 minutes for large datasets, we have modified the code for the competition to force a stop before the 3 minute mark. These competition tours are in the competition_time folder. The .tours for the 7 competition files were also run in unlimited time without the forced stop. These .tours are located in the unlimited_time folder.
