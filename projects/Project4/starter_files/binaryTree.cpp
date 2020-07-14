#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right) {
    this->str = str;
    this->num = num;
    this->left = left;
    this->right = right;
}

Node* Node::leftSubtree() const{
    return this->left;  
}

void Node::setleft(Node *n){
    this->left = n;
}

Node* Node::rightSubtree() const{
    return this->right;
}

void Node::setright(Node *n){
    this->right = n;
}

string Node::getstr() const {
    if(this == nullptr) return "";
    return str;
}

int Node::getnum() const {
    if(this == nullptr) return 0;
    return num;
}

void Node::incnum(){
    this->num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    string merge_str = leftNode->str + rightNode->str;
    int merge_num = leftNode->num + rightNode->num;
    Node *merge_node = new Node(merge_str,merge_num,leftNode,rightNode);
    return merge_node;
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode){
    this->root = rootNode;
}

BinaryTree::~BinaryTree() {
    delete[] root;//not sure
}
//helper function for findPath
string findPath_helper(const BinaryTree *tree, const string &s){
    if(tree->root == nullptr) return "-1";
    if(tree->root->getstr() == s) return "";
    BinaryTree *left = new BinaryTree(tree->root->leftSubtree());
    string left_result = findPath_helper(left,s);
    if(left_result != "-1") return left_result + '0';
    BinaryTree *right = new BinaryTree(tree->root->rightSubtree());
    string right_result = findPath_helper(right,s);
    //add destroyer 

    if(right_result != "-1") return right_result + '1';
    return "-1";
}

string BinaryTree::findPath(const string &s) const{
    string path = findPath_helper(this,s);
    if(path == "-1") return path;
    for(int i = 0; i < path.size()/2; i++){//reverse the path
        char temp = path[i];
        path[i] = path[path.size()-i-1];
        path[path.size()-i-1] = temp;
    }
    return path;
}

int BinaryTree::sum() const {
    if(this->root == nullptr) return 0;
    BinaryTree *left = new BinaryTree(this->root->leftSubtree());
    BinaryTree *right = new BinaryTree(this->root->rightSubtree());
    //add destroyer
    
    return this->root->getnum() + left->sum() + right->sum();
}

int BinaryTree::depth() const {
    //Returns zero if the tree is empty.
    if(this->root == nullptr) return 0;
    //Get the depth of the left and right subtree
    BinaryTree *left = new BinaryTree(this->root->leftSubtree());
    BinaryTree *right = new BinaryTree(this->root->rightSubtree());
    int leftDepth = left->depth();
    int rightDepth = right->depth();
    //add destroyer

    //Choose the larger one and add the root to it.
    if (leftDepth > rightDepth) return leftDepth + 1;
    else return rightDepth + 1;
}

void BinaryTree::preorder_num() const {
    if(this->root == nullptr) return;
    //first print data of node
    cout << this->root->getnum() << " ";
    //then recur on left subtree
    BinaryTree *left = new BinaryTree(this->root->leftSubtree());
    left->preorder_num();
    //then recur on right subtree
    BinaryTree *right = new BinaryTree(this->root->rightSubtree());
    right->preorder_num();
    //add destroyer

}

void BinaryTree::inorder_str() const {//not sure
    if(this->root == nullptr) return;
    //first recur on left subtree
    BinaryTree *left = new BinaryTree(this->root->leftSubtree());
    left->inorder_str();
    //then print data of node
    cout << this->root->getstr() << " ";
    //then recur on right subtree
    BinaryTree *right = new BinaryTree(this->root->rightSubtree());
    right->inorder_str();
    //add destroyer
}

void BinaryTree::postorder_num() const {
    if(this->root == nullptr) return;
    //first recur on left subtree
    BinaryTree *left = new BinaryTree(this->root->leftSubtree());
    left->postorder_num();
    //then recur on right subtree
    BinaryTree *right = new BinaryTree(this->root->rightSubtree());
    right->postorder_num();
    //then print data of node
    cout << this->root->getnum() << " ";
    //add destroyer

}
//helper function to find max value of sum
int minPathSum(const BinaryTree *tree){
    if(tree->root == nullptr) return 0;
    BinaryTree *left = new BinaryTree(tree->root->leftSubtree());
    BinaryTree *right = new BinaryTree(tree->root->rightSubtree());
    if(left->root == nullptr && right->root == nullptr) return tree->root->getnum();
    int left_sum = minPathSum(left);
    int right_sum = minPathSum(right);  
    return tree->root->getnum() + min(left_sum,right_sum);
}

bool BinaryTree::allPathSumGreater(int sum) const {
    int min = minPathSum(this);
    if(min > sum) return true;
    else return false;
}

bool Identical(const BinaryTree *tree1, const BinaryTree *tree2){
    if(tree1->root == nullptr && tree2->root == nullptr) return true;
    if(tree1->root == nullptr || tree2->root == nullptr) return false;
    //check if the num of both root is same and num of left and right subtrees are also the same
    BinaryTree *left_1 = new BinaryTree(tree1->root->leftSubtree());
    BinaryTree *right_1 = new BinaryTree(tree1->root->rightSubtree());
    BinaryTree *left_2 = new BinaryTree(tree2->root->leftSubtree());
    BinaryTree *right_2 = new BinaryTree(tree2->root->rightSubtree());
    return (tree1->root->getnum() == tree2->root->getnum() &&
    Identical(left_1,left_2) && Identical(right_1,right_2));
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    // "tree" is the subtree of this
    const BinaryTree *tree_pointer = &tree;
    const BinaryTree *this_tree = this;
    //"this" is the subtree of "tree"
    if(this_tree->root == nullptr) return true;
    if(tree_pointer->root == nullptr) return false;
    //check if current "this" is the subtree of "tree"
    if(Identical(this_tree,tree_pointer)) return true;
    //if current "this" is not, try left and right subtrees
    BinaryTree *left = new BinaryTree(this_tree->root->leftSubtree());
    BinaryTree *right = new BinaryTree(this_tree->root->rightSubtree());
    return contained_by(*left) || contained_by(*right);
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    const BinaryTree *tree_pointer = &tree;
    const BinaryTree *this_tree = this;
    //"this" is the subtree of "tree"
    if(tree_pointer->root == nullptr) return true;
    if(this_tree->root == nullptr) return false;
    //check if current "this" is the subtree of "tree"
    if(Identical(this_tree,tree_pointer)) return true;
    //if current "this" is not, try left and right subtrees
    BinaryTree *left = new BinaryTree(tree_pointer->root->leftSubtree());
    BinaryTree *right = new BinaryTree(tree_pointer->root->rightSubtree());
    return contained_by(*left) || contained_by(*right);
}

void copy_node(Node *old_node, Node *new_node){
    if(old_node->leftSubtree() != nullptr){
        Node *set_left = new Node(old_node->getstr(),old_node->getnum(),old_node->leftSubtree());
        new_node->setleft(set_left);
        copy_node(old_node->leftSubtree(),new_node->leftSubtree());
    }
    if(old_node->rightSubtree() != nullptr){
        new_node->setright(new Node(old_node->getstr(),old_node->getnum(),old_node->rightSubtree()));
        copy_node(old_node->rightSubtree(),new_node->rightSubtree());
    }
    return;
}

BinaryTree BinaryTree::copy() const {
    Node *root = new Node(this->root->getstr(),this->root->getnum());
    BinaryTree copy_tree(root);
    copy_node(this->root,copy_tree.root);
    return copy_tree;
}

/* =============================== Driver =============================== */
// int main(int argc, char const *argv[]){
//     string s = "a";
//     Node *root = new Node(s,0);
//     Node *one = new Node("b",1);
//     Node *two = new Node("c",2);
//     Node *three = new Node("d",3);
//     Node *four = new Node("e",4);
//     Node *five = new Node("f",5);
//     Node *six = new Node("g",6);
//     //basic tree
//     BinaryTree test(root);
//     test.root->setright(two);
//     test.root->setleft(one);
//     one->setright(three);
//     three->setright(six);
//     three->setleft(five);
//     two->setright(four);
//     //subtree
//     BinaryTree sub(one);
//     sub.root->setright(three);
//     three->setleft(five);
//     three->setright(six);
//     cout << root->mergeNodes(one,two)->getstr() << endl;

//     //cout << sub.contained_by(test) << endl;
//     //cout << test.contained_by(sub) << endl;
//     //cout << one->leftSubtree()->getstr() << endl;
//     //cout << test.findPath("g") << endl;
//     //cout << test.sum() << endl;
//     //cout << test.depth() << endl;
//     //test.preorder_num();
//     //test.postorder_num();
//     // cout << test.allPathSumGreater(6) << endl;
//     // cout << test.allPathSumGreater(5) << endl;
//     //BinaryTree test_copy = test.copy();
//     //cout << test_copy.root->getnum() << endl;
//     //cout << test_copy.root->getstr() << endl;

//     //test.inorder_str();
//     return 0;
// }
