#include <iostream>
#include <string>
using namespace std;


struct Student{
// represents a JI student.
string name;
string major;
long long stud_id;
bool graduated;
};

void example(const Student &s){
}
int main(){
auto x = new int[10];
x[3] = 1;
delete[] x;
cout << x[3]; // UB
}
