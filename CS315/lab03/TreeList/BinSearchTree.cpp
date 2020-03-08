//Christopher Murray
// Created by ASUS on 3/4/2020.
//

#include <iostream>
#include <queue>
#include "BinSearchTree.h"
#include "TreeNode.h"

using namespace std;

TreeNode *BinSearchTree::local_insert(TreeNode *root, int v) {
    if (root == nullptr)
        return new TreeNode(v);
    if (root->value() < v)
        root->rightSubTree(local_insert(root->rightSubTree(), v));
    else {
        root->leftSubTree(local_insert(root->leftSubTree(), v));
    }
    return root;
}

void BinSearchTree::insert(int v) {
    if (!find(v))
        root = local_insert(root, v);
}

bool BinSearchTree::find(int v){

    if (root == nullptr)
        return false;
    if (root->value() == v)
        return true;
    if (root->value() > v) {
        return this->left().find(v);
    }else {
        return this->right().find(v);
    }

//    return this->left().find(v)  || this->right().find(v);
}

bool BinSearchTree::iterFind(int v) {

    TreeNode *currNode = root;
    while (currNode != nullptr) {
        if (currNode->value() > v) {
            currNode = currNode->leftSubTree();
        }else if (currNode->value() < v) {
            currNode = currNode->rightSubTree();
        }else if (currNode->value() == v) {
            return true;
        }
    }
    return false;
}

int BinSearchTree::size() {

    if(root == nullptr)
        return 0;

    return 1 + left().size() + right().size();
}

void BinSearchTree::inorderDump() {

    if(root == nullptr)
        return;
    if (this->left().root == nullptr) {
        cout<<root->value()<<endl;
        return this->right().inorderDump();
    }else {this->left().inorderDump();}

    cout<<root->value()<<endl;
    this->right().inorderDump();

}

int BinSearchTree::maxDepth() {

    if (root == nullptr)
        return 0;
    if (left().maxDepth() >= right().maxDepth()){
        return 1 + left().maxDepth();
    }
    return 1 + right().maxDepth();
}

int BinSearchTree::iterMaxDepth() {

    queue<TreeNode *> q;
    TreeNode *node = root;
    q.push(node);
    q.push(nullptr);
    int depth = 0;

    while (!q.empty()) {
        if(q.front() == nullptr) {
            depth++;
            if(q.size() != 1)
                q.push(nullptr);
        }else {
            if (q.front()->leftSubTree() != nullptr) {
                q.push(q.front()->leftSubTree());
            }
            if (q.front()->rightSubTree() != nullptr) {
                q.push(q.front()->rightSubTree());
            }
        }
        q.pop();
    }
    return depth;
}

bool BinSearchTree::remove(int v) {
    if (root == nullptr)
        return false;
    if (root->leftSubTree()->value() == v) {

        return true;
    }
}
void BinSearchTree::levelOrderDump() {

    queue<TreeNode*> q;
    TreeNode *myNode = root;
    q.push(myNode);

    while (!q.empty()) {

        cout<<q.front()->value()<<endl;

        if(q.front()->leftSubTree() != nullptr) {
            q.push(q.front()->leftSubTree());
        }
        if(q.front()->rightSubTree() != nullptr) {
            q.push(q.front()->rightSubTree());
        }
        q.pop();
    }

}

void BinSearchTree::valuesAtLevel(int k) {

    if (root == nullptr) return;

    if (k == 1) {
        cout<<root->value()<<endl;
        return;
    }

    left().valuesAtLevel(k-1);
    right().valuesAtLevel(k-1);
}

void BinSearchTree::iterValuesAtLevel(int k) {

    queue<TreeNode*> q;
    TreeNode *myNode = root;
    q.push(myNode);
    q.push(nullptr);
    int levelCount = 1;

    while(!q.empty()) {

        if(q.front() == nullptr) {
            levelCount++;
            q.push(nullptr);
        }else {
            if (levelCount == k) {
                while(q.front() != nullptr) {
                    cout << q.front()->value() << endl;
                    q.pop();
                }
                return;
            }
            if (q.front()->leftSubTree() != nullptr) {
                q.push(q.front()->leftSubTree());
            }
            if (q.front()->rightSubTree() != nullptr) {
                q.push(q.front()->rightSubTree());
            }
        }
        q.pop();

    }
}

int BinSearchTree::kthSmallest(int k) {

    if(!(this->size() >= k)) return 0;
    if(root->leftSubTree() == nullptr)
        return k-1;

    if(left().kthSmallest(k) == 1) {
        return root->value();
    }
    return left().kthSmallest(k);
}

bool BinSearchTree::hasRootToLeafSum(int sum) {

    if (root == nullptr) return false;

    if(root->leftSubTree() == nullptr
        &&
        root->rightSubTree() == nullptr
        &&
        (sum-(root->value())) == 0)
        return true;

    return left().hasRootToLeafSum(sum-(root->value())) || right().hasRootToLeafSum(sum-(root->value()));
}

bool BinSearchTree::areIdentical(BinSearchTree *bst) {

    if (root == nullptr && bst->root == nullptr)
        return true;
    else if (root == nullptr || bst->root == nullptr)
        return false;

    if( root->value() != bst->root->value())
        return false;

    BinSearchTree otherLeft = bst->left();
    BinSearchTree otherRight = bst->right();

    return left().areIdentical(&otherLeft) && right().areIdentical(&otherRight);
}

BinSearchTree *BinSearchTree::intersectWith(BinSearchTree *bst) {

    BinSearchTree *newTree = new BinSearchTree();

    if (root == nullptr)
        return newTree;

    if(bst->find(root->value())) {
            newTree->insert(root->value());
    }

    newTree->insert(  left().intersectWith(bst)->root->value()    );
    newTree->insert(  right().intersectWith(bst)->root->value()   );

    return newTree;
}

BinSearchTree BinSearchTree::*unionWith(BinSearchTree *bst) {


}

BinSearchTree BinSearchTree::*differenceOf(BinSearchTree *bst) {


}

//left() and right() returns a new BinSearchTree that it's root is changed to its left or right subtree
BinSearchTree BinSearchTree::left() {
    BinSearchTree left;
    left.root = root->leftSubTree();
    return left;
}
BinSearchTree BinSearchTree::right () {
    BinSearchTree right;
    right.root = this->root->rightSubTree();
    return right;
}
