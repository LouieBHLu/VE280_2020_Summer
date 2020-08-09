#ifndef BST_H
#define BST_H

#include <cstddef> // for definition of NULL

// DON'T MODIFY THIS HEADER FILE

// Instances of Node are dynamically allocated
class Node{
   int v;
   Node *lNode; // left child
   Node *rNode; // right child
public:
   Node(int v, Node *lNode, Node *rNode);
   // EFFECTS: construct a new Node with deep copies of the
   //          left subtree lNode and the right subtree rNode

   // Big Three
   Node(const Node &n); // TODO
   Node &operator=(const Node &n);
   ~Node(); // TODO

   int depth(); // TODO
   // EFFECTS: returns the depth of the tree (see below)
   bool isSorted(); // TODO
   // EFFECTS: returns true if tree is sorted (see below)
};

class BinaryTree{
   Node *root; // All nodes are dynamically allocated
public:
   BinaryTree();
   // EFFECTS: builds an empty binary tree
   BinaryTree(int v, const BinaryTree &left, 
         const BinaryTree &right);
   // EFFECTS: builds a new tree whose root contains
   //          value v, its left subtree is a deep copy
   //          of left, its right subtree is a deep copy
   //          of right
   BinaryTree(const BinaryTree &bt);
   // EFFECTS: deep copy constructor from binary tree bt
   BinaryTree &operator=(const BinaryTree &bt); 
   // MODIFIES: this
   // EFFECTS: deep copies from binary tree bt
   ~BinaryTree(); // TODO

   void removeAll(); // TODO
   // MODIFIES: this
   // EFFECTS: deallocates all the nodes

   // Other methods skipped

   int depth(); // TODO
   // EFFECTS: returns the depth of the tree
   //          recall a tree with only a root has depth 0
   //          and an empty tree has depth -1

   bool isSorted(); // TODO
   // EFFECTS: returns true if the binary tree is such 
   //          that v in the root node is larger or equal
   //          to any values in the nodes of the left
   //          and right subtrees.
   //          This ordering property applies recursively
   //          to the left and right subtrees.
};

#endif
