#include "binaryTree.h"
#include <queue>
#include <iostream>
using namespace std;
// Implement the following methods listed below.
// You don't need to implement the other methods.
// If you decide to implement the other methods,
// DON'T INCLUDE THEM IN YOUR SUBMISSION.
//
// In your implementations, you can call any other
// methods, even those you don't need to implement.

Node::Node(const Node &n){
   // TODO
   // You can use the initialization syntax if you want
}

Node::~Node(){
   // TODO
   if(this != nullptr){
        this->lNode->~Node();
        this->rNode->~Node();
        delete this;
   }
}

int Node::depth(){
   if(this == nullptr) return 0;
   //Get the depth of the left and right subtree
   int leftDepth = this->lNode->depth();
   int rightDepth = this->rNode->depth();
   //Choose the larger one and add the root to it.
   if (leftDepth > rightDepth) return leftDepth + 1;
   else return rightDepth + 1;
}

bool Node::isSorted(){
       // to store maximum value of previous 
    // level. 
    int prevMax = INT_MIN; 
  
    // to store minimum value of current 
    // level. 
    int minval; 
  
    // to store maximum value of current 
    // level. 
    int maxval; 
  
    // to store number of nodes in current 
    // level. 
    int levelSize; 
  
    // queue to perform level order traversal. 
    queue<Node*> q; 
    q.push(this); 
  
    while (!q.empty()) { 
        // find number of nodes in current 
        // level. 
        levelSize = q.size(); 
  
        minval = INT_MAX; 
        maxval = INT_MIN; 
  
        // traverse current level and find 
        // minimum and maximum value of 
        // this level. 
        Node *root;
        while (levelSize > 0) { 
            root = q.front(); 
            q.pop(); 
  
            levelSize--; 
  
            minval = min(minval, root->v); 
            maxval = max(maxval, root->v); 
  
            if (root->lNode) 
                q.push(root->lNode); 
  
            if (root->rNode) 
                q.push(root->rNode); 
        } 
  
        // if minimum value of this level 
        // is not greater than maximum 
        // value of previous level then 
        // given tree is not level sorted. 
        if (minval <= prevMax) 
            return 0; 
  
        // maximum value of this level is 
        // previous maximum value for 
        // next level. 
        prevMax = maxval; 
    } 
    return 1;
}

BinaryTree::~BinaryTree(){
   removeAll();
}

void BinaryTree::removeAll(){
   root->~Node();
}

int BinaryTree::depth(){
   if(root == nullptr) return -1;
   return root->depth();
}

bool BinaryTree::isSorted(){
   // TODO
}
