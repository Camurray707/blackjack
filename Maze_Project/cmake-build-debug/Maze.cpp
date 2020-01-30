//
// Created by ASUS on 1/28/2020.
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
        if (valueTest == '0' && colTest == 14) {
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
//    mazeLadder.push(myCell.at(46));             //move right one cell fixme:find the cell to the right of mazeEntry
    auto currentNode = mazeLadder.top();
    auto prevNode = currentNode;
    auto currNodeValue = get<0>(currentNode);
    auto currNodeRow = get<1>(currentNode);
    auto currNodeCol = get<2>(currentNode);

    while (mazeLadder.top() != mazeTarget) {    //when top of stack is = to exit end
        begin:
        for (int i = 0; i < myCell.size(); i++) {

            auto nextNode = myCell.at(i);
            auto nextNodeValue = get<0>(myCell.at(i));
            auto nextNodeRow = get<1>(myCell.at(i));
            auto nextNodeCol = get<2>(myCell.at(i));

            auto currNodeValue = get<0>(currentNode);
            auto currNodeRow = get<1>(currentNode);
            auto currNodeCol = get<2>(currentNode);

            //comparing currNodeRow - 1 and node above    && that their columns are equal
            if ((currNodeRow - 1) == nextNodeRow && (currNodeCol == nextNodeCol)) {                     //compare top cell
                if (nextNode == prevNode) {continue;}
                if (currNodeValue == nextNodeValue) {
                    mazeLadder.push(nextNode);
                    prevNode = currentNode;
                    currentNode = nextNode;
                    goto begin;
                }

            }
            else if (((currNodeCol + 1) == nextNodeCol) && (currNodeRow == nextNodeRow)) {                //compare right cell
                if (nextNode == prevNode) {continue;}
                if (currNodeValue == nextNodeValue) {
                    mazeLadder.push(nextNode);
                    prevNode = currentNode;
                    currentNode = nextNode;
                    goto begin;
                }

            }
            else if ((currNodeRow + 1) == nextNodeRow  && (currNodeCol == nextNodeCol)) {                   //compare bottom cell
                if (nextNode == prevNode) {continue;}
                if (currNodeValue == nextNodeValue) {
                    mazeLadder.push(nextNode);
                    prevNode = currentNode;
                    currentNode = nextNode;}
                    goto begin;
            }else {


            }

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