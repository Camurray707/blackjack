//Christopher Murray

#include "Maze.h"

using namespace std;

int main(int argc, char **argv) {
      Maze myMaze1;
      myMaze1.makeCells(argv[1]);

      //myMaze1.printMaze();
      myMaze1.findEntry();
      myMaze1.findTarget();
      myMaze1.printSolution();

    return 0;
}
