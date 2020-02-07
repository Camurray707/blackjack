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

class Maze {

private:
    std::vector<std::tuple<char, int, int>> myCell;           //a vector of the whole maze starting at top left to bottom right
    std::vector<std::tuple<char, int, int>> myDeadEnds;       //vector of dead ends to stay away from
    std::tuple<char, int, int> mazeTarget;               //when maze ends
    std::tuple<char, int, int> mazeEntry;                //where maze starts
    std::stack<std::tuple<char, int, int>> mazeLadder;        //stack of cells/nodes that are solutions
    int myRow, myCol;
    void findMazePath();                            //find solutions to add into stack
    bool isDeadEnd(std::tuple<char, int, int> test);     //determines of current cell/node is a dead end or not
    bool used(std::tuple<char,int,int> used);            //determines if the next cell/node is used in myDeadEnds

public:
    Maze();
    ~Maze();
    //makeCells create tuples of each cell row/col and vectors of each node
    void makeCells(std::string fileName);

    //openFile open file and print current maze
    void openFile(std::string fileName);

    //printSolution finds the path of the solution and prints the end result
    void printSolution();


    //printMaze prints the original maze
    void printMaze();

    //findEntry and findTarget finds the walls where the maze starts and ends
    void findEntry();
    void findTarget();
};

#endif //MAZE_PROJECT_MAZE_H
