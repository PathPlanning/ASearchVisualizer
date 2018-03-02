# ASearchVisualizer
Program for visualization of detailed logs of pathplanning algorithms

## Description

This software was created to visualize the extended log files provided by pathplanning algorithms. It shows how the algorithm expand states on each iteration step by step, i.e. the states which were generated (and added to the OPEN list) at the current step, the expanded state (which was replaced to the CLOSED list) and the state which is going to be expanded next. It also shows parents' pointers, f-, g- and h- values of visited states. It can visualize any single-agent pathplanning algorithm, that can output the information about OPEN and CLOSED lists after each iteration.

## Building

User interface is written with using of Qt libraries. So, it is possible to build it only by QtCreator. It also uses external library TinyXML for reading XML-log files (it is already included in the source files of the project).

## Input files

As an input file the program needs an XML file with extended log of a pathplanning algorithm. The log-file contains the information about the states which presenting in the OPEN and CLOSED lists at each iteration of the algorithm. You can find more information about the log-format in README files of other repos (LIAN, AStar-JPS-Theta) or look for examples in the corresponding folder.

## Notes

The program does not create images representing the inforamtion in log-files. It creates interactive GUI objects per each grid cell, that require system resources of your PC. That is why it can consume a lot of resources and slow down if you try to visualize huge grids that contain tens of thousands of cells. 

It also worth to note, that extended log-file is not optimized in terms of memory usage. It contains the whole OPEN and CLOSED lists for each iteration of the algorithm. So, if you try to get the extended log-file for an instance that requires to spend several thousands iterations to find a solution, the resulting log-file can be very huge (hundreds MB) and if your PC doesn't have enough RAM, the program can get crash.
