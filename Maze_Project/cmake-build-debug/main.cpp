//Christopher Murray

#include <iostream>
#include "Maze.h"

using namespace std;

int main(int argc, char **argv) {

    Maze myMaze1;
//    myMaze1.openFile(argv[1]);
    myMaze1.makeCells(argv[1]);

    myMaze1.printMaze();
    myMaze1.findEntry();

    myMaze1.printSolution();

    return 0;
}