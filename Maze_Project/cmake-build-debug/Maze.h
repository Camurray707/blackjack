//
// Created by Christopher Murray on 1/28/2020.
//

#ifndef MAZE_PROJECT_MAZE_H
#define MAZE_PROJECT_MAZE_H

#include <iostream>
#include <fstream>
#include <tuple>
#include <stack>
#include <vector>

using namespace std;

class Maze {

private:
    vector<tuple<char, int, int>> myCell;
    vector<tuple<char, int, int>> myDeadEnds;       //vector of dead ends to stay away from
    tuple<char, int, int> mazeTarget;
    tuple<char, int, int> mazeEntry;
    vector<char> myNode;
    stack<tuple<char, int, int>> mazeLadder;
    void findMazePath();
    int myRow, myCol;
    bool isDeadEnd(tuple<char, int, int> test);
    bool used(tuple<char,int,int> used);

public:
    //makeCells create tuples of each cell row/col and vectors of each node
    void makeCells(string fileName);

    //openFile open file and print current maze
    void openFile(string fileName);

    //printSolution finds the path of the solution and prints the end result
    void printSolution();


    //printMaze prints the maze
    void printMaze();

    //findEntry finds the row and col where the maze starts
    void findEntry();
};


#endif //MAZE_PROJECT_MAZE_H
