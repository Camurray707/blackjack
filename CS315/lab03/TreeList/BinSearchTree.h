//Christopher Murray
// Created by ASUS on 3/4/2020.
//

#ifndef TREENODE_HPP_BINSEARCHTREE_H
#define TREENODE_HPP_BINSEARCHTREE_H

class TreeNode;

class BinSearchTree {
public:
    //Part A
    void insert(int v);
    bool find(int v);
    bool iterFind(int v);
    int size();
    void inorderDump();
    int maxDepth();

    //Part B
    void levelOrderDump();
    bool remove(int v);
    int kthSmallest(int k);
    void valuesAtLevel(int k);
    void iterValuesAtLevel(int k);
    int iterMaxDepth();
    bool hasRootToLeafSum (int sum);
    bool areIdentical ( BinSearchTree *bst);
    BinSearchTree *intersectWith (BinSearchTree *bst);
    BinSearchTree *unionWith (BinSearchTree *bst);
    BinSearchTree *differenceOf (BinSearchTree *bst);



private:
    TreeNode *local_insert(TreeNode*, int);
    TreeNode *root;

    BinSearchTree left();
    BinSearchTree right();
};


#endif //TREENODE_HPP_BINSEARCHTREE_H
