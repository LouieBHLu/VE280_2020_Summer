#include "binaryTree.h"
#include "huffmanTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

//helper function to copy a node
Node *copy_node_depress(const Node *root){
    if(!root) return nullptr;
    Node *node_copy = new Node(root->getstr(),root->getnum());
    Node *left = nullptr;
    Node *right = nullptr;
    if(root->leftSubtree()) left = copy_node_depress(root->leftSubtree());
    if(root->rightSubtree()) right = copy_node_depress(root->rightSubtree());
    node_copy->setleft(left);
    node_copy->setright(right);
    return node_copy;
}

//decode function
string decode(string &code, const Node *root, Node *parent_node){
    if(root == nullptr) return "";
    if(root->getnum() == 0){
        Node *node_copy = copy_node_depress(parent_node);
        BinaryTree parent_tree_copy(node_copy);
        string ans = parent_tree_copy.findPath(root->getstr());
        if(ans == code) return root->getstr();
    }

    string left_result = decode(code,root->leftSubtree(),parent_node);
    if(left_result != "") return left_result;
    string right_result = decode(code,root->rightSubtree(),parent_node);
    if(right_result != "") return right_result;
    return "";

}

int main(int argc, char *argv[]) {
    string treefilename = argv[1];
    string binaryfile = argv[2];
    //build a HuffmanTree using treefilename
    ifstream ifile;
    HuffmanTree tree(treefilename);
    string line;
    //read the file and decode
    ifile.open(binaryfile);
    while(getline(ifile,line)){
        string code;
        for(int i = 0; i < line.size(); i++){
            if(line[i] != ' ') code += line[i];
            else{
                BinaryTree copy_tree = tree.copy();
                //output each char
                cout << decode(code,copy_tree.root,copy_tree.root);
                code = "";
            }
        }
    }
    ifile.close();
    return 0;
}