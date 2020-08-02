#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
using namespace std;

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
    Bar bar; bar.g();
    Qux qux; qux.g();
    Baz baz; baz.h();
    Foo& f1 = qux; f1.f(); f1.g();
    Bar& b1 = qux; b1.h();
    Baz& b2 = qux; b2.h();
    Bar* b3 = &qux; b3->h();
    Baz* b4 = &qux; b4->h();
    const Foo& f2 = *b3; f2.c();
    Baz& b5 = *b4; b5.c();
    return 0;
}