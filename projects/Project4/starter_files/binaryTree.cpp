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
    return str;
}

int Node::getnum() const {
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

void Destroy_helper(Node *root){
    if(root != nullptr){
        Destroy_helper(root->leftSubtree());
        Destroy_helper(root->rightSubtree());
        delete root;
    }
}

BinaryTree::~BinaryTree() {
    Destroy_helper(this->root);
}

//helper function for findPath
string findPath_helper(const Node *root, const string &s){
    if(root == nullptr) return "-1";
    if(root->getstr() == s) return "";
    string left_result = findPath_helper(root->leftSubtree(),s);
    if(left_result != "-1") return left_result + '0';
    string right_result = findPath_helper(root->rightSubtree(),s);
    if(right_result != "-1") return right_result + '1';
    return "-1";
}

string BinaryTree::findPath(const string &s) const{
    string path = findPath_helper(this->root,s);
    if(path == "-1") return path;
    for(int i = 0; i < path.size()/2; i++){//reverse the path
        char temp = path[i];
        path[i] = path[path.size()-i-1];
        path[path.size()-i-1] = temp;
    }
    return path;
}

//helper function for sum
int sum_helper(const Node *root){
    if(root == nullptr) return 0;
    return root->getnum() + sum_helper(root->leftSubtree()) +sum_helper(root->rightSubtree());
}

int BinaryTree::sum() const {
    return sum_helper(this->root);
}

//helper function for depth
int depth_helper(const Node *root){
    //Returns zero if the tree is empty.
    if(root == nullptr) return 0;
    //Get the depth of the left and right subtree
    int leftDepth = depth_helper(root->leftSubtree());
    int rightDepth = depth_helper(root->rightSubtree());
    //Choose the larger one and add the root to it.
    if (leftDepth > rightDepth) return leftDepth + 1;
    else return rightDepth + 1;
}

int BinaryTree::depth() const {
    return depth_helper(this->root);
}

//helper function for preorder
void preorder_helper(const Node *root){
    if(root == nullptr) return;
    //first print data of node
    cout << root->getnum() << " ";
    //then recur on left subtree
    preorder_helper(root->leftSubtree());
    //then recur on right subtree
    preorder_helper(root->rightSubtree());
}

void BinaryTree::preorder_num() const {
    preorder_helper(this->root);
    cout << endl;
}

//helper function for inorder
void inorder_helper(const Node *root){
    if(root == nullptr) return;
    //first recur on left subtree
    inorder_helper(root->leftSubtree());
    //then print data of node
    cout << root->getstr() << " ";
    //then recur on right subtree
    inorder_helper(root->rightSubtree());
}


void BinaryTree::inorder_str() const {
    inorder_helper(this->root);
    cout << endl;
}

//helper function for postorder
void postorder_helper(const Node *root){
    if(root == nullptr) return;
    //first recur on left subtree
    postorder_helper(root->leftSubtree());
    //then recur on right subtree
    postorder_helper(root->rightSubtree());
    //then print data of node
    cout << root->getnum() << " ";
}

void BinaryTree::postorder_num() const {
    postorder_helper(this->root);
    cout << endl;
}

//helper function to find min value of sum
int minPathSum(const Node *root){
    if(root == nullptr) return 0;
    if(root->leftSubtree() == nullptr && root->rightSubtree() == nullptr) return root->getnum();
    int left_sum = minPathSum(root->leftSubtree());
    int right_sum = minPathSum(root->rightSubtree());
    return root->getnum() + min(left_sum,right_sum);
}

bool BinaryTree::allPathSumGreater(int sum) const {
    int min = minPathSum(this->root);
    if(min > sum) return true;
    else return false;
}

//helper function for cover
static bool covered_Helper(Node *const root, Node *const tree_root) {
    if (!root) 
        return true;
    if (!tree_root) 
        return false;
    return (root->getnum() == tree_root->getnum() && covered_Helper(root->leftSubtree(), tree_root->leftSubtree()) && 
    covered_Helper(root->rightSubtree(), tree_root->rightSubtree()));
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    return covered_Helper(root, tree.root);
}

//helper function for contained
static bool containedByHelper(Node *const root, Node *const tree_root) {
    if (covered_Helper(root, tree_root))
        return true;
    if (!tree_root)
        return false;
    return (containedByHelper(root, tree_root->leftSubtree()) || containedByHelper(root, tree_root->rightSubtree()));
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    return containedByHelper(root, tree.root);
}

Node *copy_node(const Node *root){
    if(!root) return nullptr;
    Node *node_copy = new Node(root->getstr(),root->getnum());
    Node *left = nullptr;
    Node *right = nullptr;
    if(root->leftSubtree()) left = copy_node(root->leftSubtree());
    if(root->rightSubtree()) right = copy_node(root->rightSubtree());
    node_copy->setleft(left);
    node_copy->setright(right);
    return node_copy;
}

BinaryTree BinaryTree::copy() const {
    Node *root = copy_node(this->root);
    BinaryTree copy_tree(root);
    return copy_tree;
}
