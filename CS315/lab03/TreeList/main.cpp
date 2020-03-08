//Christopher Murray
#include <iostream>
#include <fstream>
#include "BinSearchTree.h"
#include "TreeNode.h"

using namespace std;

int main(int argc, char *argv[]) {
    //create a tree and then print the values of its nodes
    //from the smallest to the largest

    BinSearchTree *tree1 = new BinSearchTree();
    BinSearchTree *tree2 = new BinSearchTree();
    ifstream testFile;
    testFile.open(argv[1]);

    int v;
    while (!testFile.eof()) {
        testFile>>v;
        tree1->insert(v);
    }
    testFile.close();

    ifstream testFile2;
    testFile2.open(argv[2]);

    while (!testFile2.eof()) {
        testFile2>>v;
        tree2->insert(v);
    }
    testFile2.close();

//    cout<<"size is: "<<tree1->size()<<endl;
//    cout<<"iterFind 76: "<<tree1->iterFind(146432)<<endl;
    cout<<"maxDepth: "<<tree1->maxDepth()<<endl;
    cout<<"iterMaxDepth: "<<tree1->iterMaxDepth()<<endl;
//    tree->inorderDump();
//    tree->levelOrderDump();
//    tree1->valuesAtLevel(4);
//    cout<<"kthSmallest: "<<tree1->kthSmallest(2)<<endl;
//    cout<<"Root-Leaf_sum: "<<tree1->hasRootToLeafSum(207)<<endl;
//    tree1->iterValuesAtLevel(4);
//    cout<<"Are identical: "<<tree1->areIdentical(tree2)<<endl;
//    tree1->intersectWith(tree2)->inorderDump();
    return 0;
}