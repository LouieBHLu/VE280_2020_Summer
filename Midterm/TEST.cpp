#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void f(int x, int &y){
x++;
y=x;
}

void g(int *x, int y){
    f(*x,y);
    (*x)++;
    y++;
}

 
enum Error_t {
INVALID_ARGUMENT, // 0
FILE_MISSING, // 1
CAPACITY_OVERFLOW, // 2
INVALID_LOG, // 3
};

struct Student{
// represents a JI student.
string name;
string major;
long long stud_id;
bool graduated;
};

int max(int x, int y) { return x > y ? x : y;}

int main(int argc, char *argv[])
{
    int x = 1;
    int y = 1;
    g(&x,y);
    f(x,y);
    cout << x << ' ' << y <<endl;
}

