#include <vector>
#include <deque>
#include <list>
#include <map>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int add(int a, int b = 0, int c = 0, int d){
    return a+b+c+d;
}
int foo(int a, int d){
    return add(a+d);
}

int main(int argc, char const *argv[]){
    vector<int> ivec(5, 0); // holes ints
    vector<int>::const_iterator cit = ivec.cbegin();
    vector<int>::iterator it = ivec.begin();
    *it = 1;
    cit++;

    deque<int> d(5,1);
    deque<int>::iterator dite = d.end();
    deque<int>::iterator ditb = d.begin();
    deque<int> d_copy(ditb,dite);


    std::map<char,int> mymap;
    // first insert function version (single parameter):
    mymap.insert ( std::pair<char,int>('a',100) );
    // can also use mymap.insert(std::make_pair('a', 100))
    // remember to #include <utility> if you use make_pair
    mymap.insert ( std::pair<char,int>('z',200) );
    std::pair<std::map<char,int>::iterator,bool> ret;
    ret = mymap.insert ( std::pair<char,int>('z',500) );
    if (ret.second==false) {
        cout << "element 'z' already existed";
        cout << " with a value of " << ret.first->second << '\n';
    }
    
    foo(1,2);
    // map<string, vector<int>> mp;
    // mymap.erase('a');
    // stack<int, vector<int> > stk(ivec); 
    return 0;
}

