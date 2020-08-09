#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
using namespace std;

// class Bird {
//     public:
//     virtual void talk() const {
//     cout << "tweet" << endl;
//     }
// };

// class Chicken : public Bird {
//     virtual void talk() {
//         cout << "bawwk" << endl;
//     }
// }

class A{
    public:
    void f(){cout << "A::f" << endl;}
    virtual void g() = 0;
    virtual void h() {cout << "A::h" << endl;}
};

class B: public A{
    public:
    virtual void f(){cout << "B::f" << endl;}
    void g(){cout << "B::g" << endl;}
    void h(){cout << "B::h" << endl;}
};

class C: public B{
    public:
    void f(){cout << "C::f" << endl;}
    void h(){A::h();}
};

class D: public C{
    public:
    void h(){cout << "D::h" << endl;}
};

struct Foo {
    void f() { cout << "a"; };
    virtual void g() = 0;
    virtual void c() const = 0;
};

struct Bar : public Foo {
    void f() { cout << "b"; };
    void g() { cout << "c"; };
    void c() const { cout << "d"; };
    void h() { cout << "e"; };
};

struct Baz : public Bar {
    void f() { cout << "f"; };
    void g() { cout << "g"; };
    void c() { cout << "h"; };
    virtual void h() { cout << "i"; };
};

struct Qux : public Baz {
    void f() { cout << "j"; };
    void h() { cout << "k"; };
};

int main() {
    // Chicken chicken("Myrtle");
    // Bird *b_ptr = &chicken;
    // b_ptr->talk();
    // Bar bar; bar.g();
    // Qux qux; qux.g();
    // Baz baz; baz.h();
    // Foo& f1 = qux; f1.f(); f1.g();
    // Bar& b1 = qux; b1.h();
    // Baz& b2 = qux; b2.h();
    // Bar* b3 = &qux; b3->h();
    // Baz* b4 = &qux; b4->h();
    // const Foo& f2 = *b3; f2.c();
    // Baz& b5 = *b4; b5.c();

    A *pa;
    B b;
    C c;
    D d;

    c.f();
    c.h();

    pa = &b;
    pa->f();
    pa->g();
    pa->h();

    pa = &c;
    pa->f();
    pa->g();
    pa->h();
    
    A &ra = d;
    ra.g();
    ra.h();

    d.f();
    d.g();
    return 0;
}