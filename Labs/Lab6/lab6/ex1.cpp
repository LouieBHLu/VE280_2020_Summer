//     Subclass            Children                                        Description
//     --------            --------                                        -----------
//   ASTNode:                                                              the base class
//     ProgramNode         DeclListNode                                    the whole program
//     DeclListNode        a list of DeclNode                              a list of declarations, e.g. int a; void f(){}
//
//     DeclNode:                                                           a declaration
//       VarDeclNode       TypeNode, IdNode                                a variable declaration, e.g. int a;
//       FnDeclNode        TypeNode, IdNode, FormalsListNode, FnBodyNode   a function definition, e.g. void f(...){...}
//       FormalDeclNode    TypeNode, IdNode                                a funtion parameter declaration, e.g. int a
//
//     FormalsListNode     a list of FormalDeclNode                        a list of function parameters, e.g. (int a, bool b)
//     FnBodyNode          DeclListNode, StmtListNode                      the function body
//     StmtListNode        a list of StmtNode                              a list of statements
//
//     TypeNode:                                                           a type keyword
//       IntNode           -- none --                                      the keyword int
//       BoolNode          -- none --                                      the keyword bool
//       VoidNode          -- none --                                      the keyword void
//
//     StmtNode:                                                           a statement end with semicolon ;
//       AssignStmtNode      AssignNode                                    an assign statement, e.g. a=1;
//       PostIncStmtNode     ExpNode                                       a post increase statement, e.g. a++;
//       PostDecStmtNode     ExpNode                                       a pose decrease statement, e.g. a--;
//
//     ExpNode:                                                            an expression
//       IntLitNode          -- none --                                    an int literal, e.g. 1
//       TrueNode            -- none --                                    the keyword true
//       FalseNode           -- none --                                    the keyword false
//       IdNode              -- none --                                    an identifier, e.g. a, f, main
//       AssignNode          ExpNode, ExpNode                              an assignemnt expression, e.g. a=1 (notice no ";")

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// constants used
#define MAX_NUM_NODE 100
#define MAX_NUM_CHILD 10
#define SIZE_TAB 4

// forward declaration of classes
class ASTNode;
class ProgramNode;
class DeclListNode;
class DeclNode;
class VarDeclNode;
class FnDeclNode;
class FormalDeclNode;
class FormalsListNode;
class FnBodyNode;
class StmtListNode;
class TypeNode;
class IntNode;
class BoolNode;
class VoidNode;
class StmtNode;
class AssignStmtNode;
class PostIncStmtNode;
class PostDecStmtNode;
class ExpNode;
class IntLitNode;
class TrueNode;
class FalseNode;
class IdNode;
class AssignNode;

// **********************************************************************
// ASTNode class (base class for all other kinds of nodes)
// **********************************************************************

class ASTNode {
   public:
    ASTNode(int n = 0) : num_child(n) {}
    virtual ~ASTNode(){};

    int numChild() {
        return num_child;
    }

    void setChild(int index, ASTNode* ptr) {
        children[index] = ptr;
    }

    void addIndent(int indent) {
        for (int i = 0; i < indent; ++i) {
            cout << " ";
        }
    }

    virtual void unparse(int indent) = 0;

   protected:
    int num_child;
    ASTNode* children[MAX_NUM_CHILD];
};

// **********************************************************************
// ProgramNode,  DeclListNode, FormalsListNode, FnBodyNode, StmtListNode
// **********************************************************************

class ProgramNode : public ASTNode {
   public:
    ProgramNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        children[0]->unparse(indent);  // unparse DeclListNode
    }
};

class DeclListNode : public ASTNode {
   public:
    DeclListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        for (int i = 0; i < num_child; ++i) {
            children[i]->unparse(indent);  // unparse DeclNode
        }
    }
};

class FormalsListNode : public ASTNode {//different
   public:
    FormalsListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        if(num_child > 0){
            for (int i = 0; i < num_child - 1; ++i){
                children[i]->unparse(indent);
                cout << ", ";
            }
            children[num_child - 1]->unparse(indent);
        }
    }
};

class FnBodyNode : public ASTNode {
   public:
    FnBodyNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        // TODO, think about what indent value to pass to its children!
        children[0]->unparse(indent+SIZE_TAB);
        children[1]->unparse(indent+SIZE_TAB);
    }
};

class StmtListNode : public ASTNode {
   public:
    StmtListNode(int n = 0) : ASTNode(n) {}

    void unparse(int indent) {
        // TODO
        for (int i = 0; i < num_child; ++i){
            children[i]->unparse(indent);
            cout << endl;
        }
    }
};

// **********************************************************************
// DeclNode and its subclasses
// **********************************************************************

class DeclNode : public ASTNode {
   public:
    DeclNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class VarDeclNode : public DeclNode {
   public:
    VarDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent) {
        // TODO
        addIndent(indent);
        children[0]->unparse(indent);
        cout << " ";
        children[1]->unparse(indent);
        cout << ';' << endl;
    }
};

class FnDeclNode : public DeclNode {
   public:
    FnDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent) {
        addIndent(indent);
        children[0]->unparse(indent);  // unparse TypeNode
        cout << " ";
        children[1]->unparse(indent);  // unparse IdNode
        cout << "(";
        children[2]->unparse(indent);  // unparse FormalsListNode
        cout << ") {" << endl;
        children[3]->unparse(indent);  // unparse FnBodyNode
        addIndent(indent);
        cout << "}" << endl;
    }
};

class FormalDeclNode : public DeclNode {
   public:
    FormalDeclNode(int n = 0) : DeclNode(n) {}

    void unparse(int indent) {
        // TODO
        children[0]->unparse(indent);
        cout << " ";
        children[1]->unparse(indent);
        //cout << ',';
    }
};

// **********************************************************************
// TypeNode and its Subclasses
// **********************************************************************

class TypeNode : public ASTNode {
   public:
    TypeNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class IntNode : public TypeNode {
   public:
    IntNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent) {
        // TODO
        cout << "int";
    }
};

class BoolNode : public TypeNode {
   public:
    BoolNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent) {
        // TODO
        cout << "bool";
    }
};

class VoidNode : public TypeNode {
   public:
    VoidNode(int n = 0) : TypeNode(n) {}

    void unparse(int indent) {
        // TODO
        cout << "void";
    }
};

// **********************************************************************
// StmtNode and its subclasses
// **********************************************************************

class StmtNode : public ASTNode {
   public:
    StmtNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class AssignStmtNode : public StmtNode {
   public:
    AssignStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent) {
        // TODO
        addIndent(indent);
        children[0]->unparse(indent);
        cout << ";";
    }
};

class PostIncStmtNode : public StmtNode {
   public:
    PostIncStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent) {
        // TODO
        addIndent(indent);
        children[0]->unparse(indent);
        cout << "++;";
//?
    }
};

class PostDecStmtNode : public StmtNode {
   public:
    PostDecStmtNode(int n = 0) : StmtNode(n) {}

    void unparse(int indent) {
        // TODO
        addIndent(indent);
        children[0]->unparse(indent);
        cout << "--;";//?
    }
};

// **********************************************************************
// ExpNode and its subclasses
// **********************************************************************

class ExpNode : public ASTNode {
   public:
    ExpNode(int n = 0) : ASTNode(n) {}

    virtual void unparse(int indent) = 0;
};

class IntLitNode : public ExpNode {
   public:
    IntLitNode(int n = 0, int val = 0) {
        num_child = n;
        myVal = val;
    }

    void unparse(int indent) {
        // TODO
        cout << myVal;
    }

   private:
    int myVal;
};

class TrueNode : public ExpNode {
   public:
    TrueNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent) {
        // TODO
        cout << "true";
    }
};

class FalseNode : public ExpNode {
   public:
    FalseNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent) {
        // TODO
        cout << "false";
    }
};

class IdNode : public ExpNode {
   public:
    IdNode(int n = 0, string str = "") {
        num_child = n;
        myName = str;
    }

    virtual void unparse(int indent) {
        // TODO
        cout << myName;
    }

   private:
    string myName;
};

class AssignNode : public ExpNode {
   public:
    AssignNode(int n = 0) : ExpNode(n) {}

    void unparse(int indent) {
        // TODO
        children[0]->unparse(indent);
        cout << " = ";
        children[1]->unparse(indent);
    }
};

int main() {
    // TODO: read input line by line, allocate new node, store into array
    ASTNode* nodes[MAX_NUM_NODE];
    string line;
    string num_node;
    getline(cin,num_node);
    int NodeNum = atoi(num_node.c_str());
    int curnum = 0;
    while(curnum < NodeNum){
        getline(cin,line);
        string name;
        string node_type;
        string children_num;
        int i = 0;
        while(line[i] != ' '){
            node_type = node_type + line[i];
            i++;
        }
        i++;
        while(line[i] && line[i] != ' '){
            children_num = children_num + line[i];
            i++;
        }
        int ChildrenNum = atoi(children_num.c_str());
        if(line[i] == ' '){
            i++;
            while(line[i]){
                name = name + line[i];
                i++;
            }
        }
        int val = atoi(name.c_str());

        if(!node_type.compare("ProgramNode")){
            nodes[curnum] = new ProgramNode(ChildrenNum);
            curnum++;
        }
        else if(!node_type.compare("DeclListNode")){
            nodes[curnum] = new DeclListNode(ChildrenNum);
            curnum++;
        }
        else if(!node_type.compare("FnDeclNode")){
            nodes[curnum] = new FnDeclNode(ChildrenNum);
            curnum++;
        }
        else if(!node_type.compare("VoidNode")){
            nodes[curnum] = new VoidNode(ChildrenNum);
            curnum++;
        }
        else if(!node_type.compare("IdNode")){
            nodes[curnum] = new IdNode(ChildrenNum, name);
            curnum++;
        }
        else if(!node_type.compare("FormalsListNode")){
            nodes[curnum] = new FormalsListNode(ChildrenNum);
            curnum++;
        }
        else if(!node_type.compare("FnBodyNode")){
            nodes[curnum] = new FnBodyNode(ChildrenNum);
            curnum++;
        }
        else if(!node_type.compare("DeclListNode")){
            nodes[curnum] = new DeclListNode(ChildrenNum);
            curnum++;
        }
        else if(!node_type.compare("StmtListNode")){
            nodes[curnum] = new StmtListNode(ChildrenNum);
            curnum++;   
        }
        else if(!node_type.compare("VarDeclNode")){
            nodes[curnum] = new VarDeclNode(ChildrenNum);
            curnum++;   
        }
        else if(!node_type.compare("AssignStmtNode")){
            nodes[curnum] = new AssignStmtNode(ChildrenNum);
            curnum++;   
        }
        else if(!node_type.compare("IntNode")){
            nodes[curnum] = new IntNode(ChildrenNum);
            curnum++;   
        }
        else if(!node_type.compare("AssignNode")){
            nodes[curnum] = new AssignNode(ChildrenNum);
            curnum++;     
        }
        else if(!node_type.compare("IntLitNode")){
            nodes[curnum] = new IntLitNode(ChildrenNum, val);
            curnum++;  
        }
        else if(!node_type.compare("FormalDeclNode")){
            nodes[curnum] = new FormalDeclNode(ChildrenNum);
            curnum++;  
        }
        else if(!node_type.compare("BoolNode")){
            nodes[curnum] = new BoolNode(ChildrenNum);
            curnum++;  
        }
        else if(!node_type.compare("PostIncStmtNode")){
            nodes[curnum] = new PostIncStmtNode(ChildrenNum);
            curnum++;   
        }
        else if(!node_type.compare("PostDecStmtNode")){
            nodes[curnum] = new PostDecStmtNode(ChildrenNum);
            curnum++;   
        }
        else if(!node_type.compare("TrueNode")){
            nodes[curnum] = new TrueNode(ChildrenNum);
            curnum++;   
        }
        else{
            nodes[curnum] = new FalseNode(ChildrenNum);
            curnum++;   
        }
    }
    
    // TODO: traverse array to construct the tree
    int alone[NodeNum]; //if one node is not connected to any parent then it's alone.
    alone[0] = 0;
    for(int i = 1; i < NodeNum; i++) alone[i] = 1;
    for(int i = 0; i < NodeNum; i++){
        int position; // the position has been connected to a parent
        for(position = i; position < NodeNum; position++){
            if(alone[position] == 1) break;
        }
        for(int j = 0; j < nodes[i]->numChild(); j++){
            nodes[i]->setChild(j,nodes[j+position]);
            alone[j+position] = 0;
        }
    }
    // call unparse() of root to print whole program
    ASTNode* root = nodes[0];
    root->unparse(0);

    // TODO: delete the allocated nodes
    for(int i = 0; i < NodeNum; i++) delete nodes[i];
}
