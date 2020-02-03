//
// Created by Christopher Murray on 1/28/2020.
//

#include "Maze.h"

void Maze::openFile(string fileName) {
    string row;
    char cell;
    ifstream newFile;
    newFile.open(fileName);

    if (!newFile.is_open()) {
        cout<<"Unable to open the file: "<<fileName<<endl;
    }
    else {
        while (newFile>>row) {
            for (int i = 0; i < row.size(); i++){
                cout<<row.at(i)<<" ";
            }
            cout<<endl;
        }
    }
    newFile.close();
}

void Maze::makeCells(string fileName) {
    char cells;
    string line;
    ifstream mazeFile;
    mazeFile.open(fileName);

    if (!mazeFile.is_open()) {
        cout<<"Unable to open the file: "<<fileName<<endl;
    }
    else {
        unsigned int j = 0;
        while(getline(mazeFile,line)) {                    //i = number of col, j = number of rows
            for (int i = 0 ; i < line.size(); i++) {
                auto newCell = make_tuple(line.at(i), j, i);
                myCell.push_back(newCell);                 //each element of myCell contains a tuple of (zeros/ones, row, col)
               // myNode.push_back(line.at(i));
            }
            j++;
        }
        myRow = j-1;
        myCol = line.size();
    }
}
void Maze::printMaze() {
        unsigned int i = 0;

        while (i < myCell.size()) {
            for (int j = 0; j < myCol; j++) {
                cout<<get<0>(myCell.at(i));
                i++;
            }
            cout << endl;
        }
        cout<<endl;
}

void Maze::findEntry() {

    for (int i = 0; i < myCell.size(); i++) {
        auto valueTest = get<0>(myCell.at(i));
        auto rowTest = get<1>(myCell.at(i));
        auto colTest = get<2>(myCell.at(i));

        if (valueTest == '0' && colTest == 0) {
            get<0>(mazeEntry) = '0';
            get<1>(mazeEntry) = rowTest;
            get<2>(mazeEntry) = colTest;
            cout<<"Entry at Row: "<<get<1>(myCell.at(i))<<", Col: "<<get<2>(myCell.at(i))<<endl;
        }
        if (valueTest == '0' && colTest == 14) {        //fixme: find end col
            get<0>(mazeTarget) = '0';
            get<1>(mazeTarget) = rowTest;
            get<2>(mazeTarget) = colTest;
            cout<<"Exit at Row: "<<get<1>(myCell.at(i))<<", Col: "<<get<2>(myCell.at(i))<<endl;
        }
    }
    cout<<endl;
}

void Maze::findMazePath() {
    mazeLadder.push(mazeEntry);                 //start at entry
    auto currentNode = mazeLadder.top();
    auto prevNode = currentNode;
    auto backTrackNode = currentNode;

    begin:

    while (mazeLadder.top() != mazeTarget) {    //when top of stack is = to exit end

        for (int i = 0; i < myCell.size(); i++) {

            auto nextNode = myCell.at(i);
            auto nextNodeValue = get<0>(myCell.at(i));
            auto nextNodeRow = get<1>(myCell.at(i));
            auto nextNodeCol = get<2>(myCell.at(i));

            auto currNodeValue = get<0>(currentNode);
            auto currNodeRow = get<1>(currentNode);
            auto currNodeCol = get<2>(currentNode);


            //comparing currNodeRow - 1 and node above    && that their columns are equal
            if ((currNodeRow - 1) == nextNodeRow && (currNodeCol == nextNodeCol)
            && nextNode != prevNode && nextNode != backTrackNode && currNodeValue == nextNodeValue && !this->used(nextNode)) {                     //compare top cell
                    prevNode = mazeLadder.top();
                    mazeLadder.push(nextNode);
                    currentNode = nextNode;
                    goto begin;
            }
            else if (((currNodeCol + 1) == nextNodeCol) && (currNodeRow == nextNodeRow)
            && nextNode != prevNode && nextNode != backTrackNode && currNodeValue == nextNodeValue && !this->used(nextNode)) {                //compare right cell
                             //fixme: auto backtrack doesnt look down
                    prevNode = mazeLadder.top();
                    mazeLadder.push(nextNode);
                    currentNode = nextNode;
                    goto begin;
            }
            else if ((currNodeRow + 1) == nextNodeRow  && (currNodeCol == nextNodeCol)
            && nextNode != prevNode && nextNode != backTrackNode && currNodeValue == nextNodeValue && !this->used(nextNode)) {                   //compare bottom cell

                    prevNode = mazeLadder.top();
                    mazeLadder.push(nextNode);
                    currentNode = nextNode;
                    goto begin;

            }
            else if (currNodeRow == nextNodeRow  && (currNodeCol - 1) == nextNodeCol
            && nextNode != prevNode && nextNode != backTrackNode && currNodeValue == nextNodeValue && !this->used(nextNode)) {                   //compare left cell
                    prevNode = mazeLadder.top();
                    mazeLadder.push(nextNode);
                    currentNode = nextNode;
                    goto begin;

            }
                else if (this->isDeadEnd(currentNode)) {            //fixme: backtracking occurs before nextNode can reach bottom of currentNode
                //mazeLadder.pop()???, currNode = prev, prev = mazeLadder.top()             //fixme: find a way to make this true only after looking at all sides

                backtrack:
                    if (mazeLadder.size() == 2) {cout<<"There is no solution."<<endl; return;}
                myDeadEnds.push_back(currentNode);
                    backTrackNode = currentNode;
                currentNode = prevNode;
                mazeLadder.pop();
                mazeLadder.pop();
                prevNode = mazeLadder.top();
                mazeLadder.push(currentNode);

                goto begin;
                }
                else if (i == 194) {goto backtrack;}
        }
    }
}


void Maze::printSolution() {
    this->findMazePath();
    cout<<"SOLUTION:"<<endl;
    while (mazeLadder.size() > 0) {
        start:
        for (int i = 0; i < myCell.size(); i++) {                   //delete the path from entry to target
            if (myCell.at(i) == mazeLadder.top()) {
                get<0>(myCell.at(i)) = ' ';
                mazeLadder.pop();
                if (mazeLadder.empty()) {this->printMaze();return;}
                goto start;
            }
        }
    }
    this->printMaze();
}

bool Maze::isDeadEnd(tuple<char, int, int> test) {      //fixme: left wall - 1
    int count = 0;

    auto currNodeValue = get<0>(test);
    auto currNodeRow = get<1>(test);
    auto currNodeCol = get<2>(test);

    if (currNodeCol == 0 || currNodeCol == myCol -1) {return false;}

    for (int i = 0; i < myCell.size(); i++) {
        auto nextNodeValue = get<0>(myCell.at(i));
        auto nextNodeRow = get<1>(myCell.at(i));
        auto nextNodeCol = get<2>(myCell.at(i));

        if ((currNodeRow - 1) == nextNodeRow && (currNodeCol == nextNodeCol)) {                    //top cell
            if (nextNodeValue == '1') {count++;}
        } else if ((currNodeRow + 1) == nextNodeRow && (currNodeCol == nextNodeCol)) {               //bottom cell
            if (nextNodeValue == '1') {count++;}
        } else if ((currNodeRow == nextNodeRow && (currNodeCol - 1 == nextNodeCol))) {               //left cell
            if (nextNodeValue == '1') {count++;}
        }else if (currNodeRow == nextNodeRow && (currNodeCol + 1 == nextNodeCol)) {                 //right cell
            if (nextNodeValue == '1') {count++;}
        }

    }
    if (count == 3) {return true;}
    return false;
}

bool Maze::used(tuple<char,int,int> used) {
    for (int i = 0; i < myDeadEnds.size(); i++) {if (used == myDeadEnds.at(i)) return true;}
    return false;
}

