#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
using namespace std;

class Shape{
    string s_name;
    public:
    Shape(string name): s_name(name){}
    virtual void get_info(){ cout<<s_name<<endl; 
    }
};

class Square : public Shape{
    int side;

    public:
    Square(string S_name, int value) : Shape(S_name), side(value){}

    void get_info(){ cout<<"Area of the square is: "<<side * side<<endl; }
    };
class Rectangle : public Shape{
    int length;
    int width;
    public:
    Rectangle(string S_name, int len, int wid) : Shape(S_name), length(len), width(wid) {}

    void get_info() override { 
        cout<<"Area of the rectangle is: "<<length *
        width<<endl; 
    }
    };

    Shape* create_square(string S_name, int value){
        return new Square(S_name, value);
    }

    Rectangle* create_rectangle(string S_name, int len, int wid){
        return new Rectangle(S_name, len, wid);
    }

int main() {
    // quad is the pointer to the parent class,
    // it needs to be casted to be used to
    // access the method of the child class.
    Shape *quad = create_square("Quadliteral", 4);
    // Trying to downcast the parent class pointer to
    // the child class pointer.
    Square* sq = dynamic_cast<Square*>(quad);
    // dynamic_cast returns returns null if the type
    // to be casted into is a pointer and the cast
    // is unsuccessful.
    if(sq){
        sq -> get_info();
    }

    Rectangle *rect = create_rectangle("Quadliteral", 4, 5);
    // An example of a valid upcasting
    Shape* quad1 = dynamic_cast<Shape*>(rect);
    // An example of invalid downcasting
    Square* sq1 = dynamic_cast<Square*>(quad1);
    if(!sq1){
        cout<<"Invalid casting."<<endl;
    }
}
