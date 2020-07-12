#include "node.h"
#include <iostream>
using namespace std;

Node::Node(int _value, int _n){
    this->value = _value;
    this->n = _n;
    this->parent = nullptr;
    this->child_num = 0;
    this->height = 0;
    this->children = new Node *[n];
};

Node::~Node(){
    for(int i = 0; i < child_num; i++) delete children[i];
    delete[] children;
}

void Node::addChild(int _value){
    if(child_num == n){
        tooManyChildren error;
        throw error;
    }
    child_num++;
    children[child_num-1] = new Node(_value,n);
};

void Node::addChild(Node *child){
    if(this->child_num == n){
        tooManyChildren error;
        throw error;
    }
    this->children[child_num] = child;
    this->child_num++;
    child->parent = this;
};

void Node::traverse(){
    cout << this->value << " ";
    if(this->child_num == 0) return;
    else{
        for(int j = 0; j < this->child_num; j++){
            this->children[j]->traverse();
        }
    }
};

int Node::getHeight(){
    Node *this_tree = this;
    if(this_tree == nullptr) return 0;
    int height = -1;
    for(int i = 0; i < this_tree->child_num; i++){
        height = max(height,this_tree->children[i]->getHeight());
    }
    return height+1;
};

bool Node::dfs(Node *tree1, Node *tree2){
    if(tree1 == nullptr && tree2 == nullptr) return true;
    if(tree1 == nullptr || tree2 == nullptr) return false;
    if(tree1->value != tree2->value) return false;
    if(tree1->child_num != tree2->child_num) return false;
    //tree1 and tree2 have the same child_num
    bool identical = 1;
    for(int i = 0; i < tree1->child_num; i++){
        identical *= dfs(tree1->children[i], tree2->children[i]);
    }
    return identical;
}

bool Node::contain(Node *sub){
    Node *this_tree = this;
    if(this_tree == nullptr) return false;
    if(dfs(this_tree,sub)) return true;
    int i;
    for(i = 0; i < this_tree->child_num; i++){
        if(this_tree->children[i]->contain(sub)) break;
    }
    if(i == this_tree->child_num) return false;
    else return true;
};

Node &Node::operator[](int i){
    if(i > this->child_num-1 || i < 0){
        invalidIndex error;
        throw error;
    }
    Node *child_node = this->children[i];
    return *child_node;
};



