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
    vector<tuple<char, int, int>> myCell;           //a vector of the whole maze starting at top left to bottom right
    vector<tuple<char, int, int>> myDeadEnds;       //vector of dead ends to stay away from
    tuple<char, int, int> mazeTarget;               //when maze ends
    tuple<char, int, int> mazeEntry;                //where maze starts
    stack<tuple<char, int, int>> mazeLadder;        //stack of cells/nodes that are solutions
    void findMazePath();                            //find solutions to add into stack
    int myRow, myCol;
    bool isDeadEnd(tuple<char, int, int> test);     //determines of current cell/node is a dead end or not
    bool used(tuple<char,int,int> used);            //determines if the next cell/node is used in myDeadEnds

public:
    //makeCells create tuples of each cell row/col and vectors of each node
    void makeCells(string fileName);

    //openFile open file and print current maze
    void openFile(string fileName);

    //printSolution finds the path of the solution and prints the end result
    void printSolution();


    //printMaze prints the original maze
    void printMaze();

    //findEntry finds the row and col where the maze starts and ends
    void findEntry();
};


#endif //MAZE_PROJECT_MAZE_H
