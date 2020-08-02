#include "dlist.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <class T>
class Stack {
    private:
    Dlist<T> list;
    public:
    bool empty(){
        if(list.isEmpty()) return true;
        else return false;
    }

    void pop(){
        if(list.isEmpty()) return;
        T *op = list.removeFront();
        delete op;
    } 

    void push(T* val){
        //T *op = new T(val);
        list.insertFront(val);
    }

    T* top(){
        if(list.isEmpty()) return nullptr;
        // Dlist<T> temp(list);
        // T *op = temp.removeFront();
        // return op;
        T *op = list.removeFront();
        T *itr = op;
        list.insertFront(op);
        return itr;
    }

    ~Stack(){
        list.~Dlist();
    }
};

bool isParenthesis(const string& token){        
    return token == "(" || token == ")";      
} 

int cmpPrecedence(const string &token1, const string &token2){
    if(token2 == "*" || token2 == "/"){
        if(token1 == "+" || token1 == "-") return 1;
        else return 0;
    }
    if(token2 == "+" || token2 == "-"){
        if(token1 == "*" || token1 == "/") return -1;
        else return 0;
    }
    return 0;
}

bool isOperater(string &token){
    return token == "+" || token == "-" ||      
           token == "*" || token == "/";
}

int main(int argc, char const *argv[]){
    string output = "";
    Stack<string> stack;
    string token;
    string line;
    bool error_parent = 0;
    // Convert infix expression format into RPN   
    getline(cin,line);     
    unsigned int i = 0;
    while(i < line.size()){
        //clear the token
        token = "";
        //read a token
        while(line[i] != ' ' && i < line.size()){
            token += line[i];
            i++;
        }
        i++;
        //if token is a operator
        if(isOperater(token)){
            // While there is an operator token, o2, at the top of the stack AND    
            // either o1 is left-associative AND its precedence is equal to that of o2,    
            // OR o1 has precedence less than that of o2,    
            string o1 = token;
            if (!stack.empty()){
                string* o2 = stack.top();
                //cout << *o2 << endl;
                while(isOperater(*o2) && cmpPrecedence(o1,*o2) >= 0){
                    // pop o2 off the stack, onto the output;
                    string o2_val = *o2;
                    output += o2_val;
                    output += ' ';
                    stack.pop();
                    if(!stack.empty()){
                        o2 = stack.top();
                        //cout << *o2 << endl;
                    } 
                    else break;
                }
            }        
            //push o1 onto the operator stack
            string* new_op = new string(o1);
            stack.push(new_op);
            //delete new_op;
        }
        else if(token == "("){
            string* new_token = new string(token);
            stack.push(new_token);
            //delete new_token;
        } 
        else if(token == ")"){
            // Until the token at the top of the stack is a left parenthesis,     
            // pop operators off the stack onto the output queue. 
            bool lack_pare = 0;   
            string* topToken  = stack.top();
            while(*topToken != "("){
                string top_val = *topToken;
                output += top_val;
                output += ' ';
                stack.pop();
                if(stack.empty()){
                    lack_pare = true;
                    break;
                } 
                topToken  = stack.top();
            }
            // If the stack runs out without finding a left parenthesis,     
            // then there are mismatched parentheses. 
            if(lack_pare){
                cout << "ERROR: Parenthesis mismatch" << endl;
                error_parent = 1;
                break;

            }
            if (*topToken != "("){                        
                   cout << "ERROR: Parenthesis mismatch" << endl;
                   error_parent = 1;
                   break;
            }                                          
            //Pop the left parenthesis from the stack, but not onto the output
            if(!stack.empty()) stack.pop(); 
        }
        else{
            output += token;
            output += ' ';
        }        
    }

    // While there are still operator tokens in the stack
    while(!stack.empty()){
        string *stackToken = stack.top();
        // If the operator token on the top of the stack is a parenthesis,     
        // then there are mismatched parentheses.   
        if(isParenthesis(*stackToken)){
                cout << "ERROR: Parenthesis mismatch" << endl;
                error_parent = 1;
                break;
        }
        // Pop the operator onto the output queue./    
        output += *stackToken;   
        output += ' ';                 
        stack.pop();      
    }
    //cout the output
    if(error_parent) return 0;
    else cout << output << endl;
    i = 0;

    //compute value
    bool error_compute = 0;
    while(i < output.size()){
        //clear the token
        token = "";
        //read a token
        while(output[i] != ' ' && i < output.size()){
            //cout << output[i] << endl;
            token += output[i];
            i++;
        }
        i++;
        //if it's a value, push it onto the stack
        if(!isOperater(token)){
            string* new_token = new string(token);
            stack.push(new_token);
            //delete new_token;
        }
        else{
            int result = 0;
            // Token is an operator: pop top two entries
            if(stack.empty()){
                cout << "ERROR: Not enough operands" << endl;
                error_compute = 1;
                break;
            }
            string *val2 = stack.top();
            double d2 = atof((*val2).c_str());
            stack.pop();
            if(!stack.empty()){
                string *val1 = stack.top();
                double d1 = atof((*val1).c_str());
                stack.pop();
                //Get the result
                if(token == "+") result = d1 + d2;
                else if(token == "-") result = d1 - d2;
                else if(token == "*") result = d1 * d2;
                else{
                    if(d2 == 0){
                        cout << "ERROR: Divide by zero" << endl;
                        error_compute = 1; 
                        break;
                    }
                    else result = d1 / d2; 
                }      
            }
            else{
                cout << "ERROR: Not enough operands" << endl;
                error_compute = 1;
                break;
            }
        // Push result onto stack       
        ostringstream s;      
        s << result;   
        string* new_result = new string(s.str());
        stack.push(new_result);
        //delete new_result;
    }
    }

    //check if there are still operands in the stack besides the final result
    string* result_s = stack.top();
    string result_com;
    if(result_s != nullptr) result_com = *result_s;
    stack.pop();
    if(!stack.empty()){
        cout << "ERROR: Too many operands" << endl;
        error_compute = 1;
        return 0;
    }
    if(!error_compute) cout << result_com << endl;
    return 0;
}



