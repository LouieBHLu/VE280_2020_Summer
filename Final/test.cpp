#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
using namespace std;

class Base {
friend void friendBase(Base* b);
friend void friendDrived(Derived* d);
/* A */
private:
int priv;
void privMethod(){
priv = 0;
}
/* B */
protected:
int prot;
void protMethod(){
prot = 0;
}
/* C */
public:
int pub;
void pubMethod(){
pub = 0;
}
};

class Derived : public Base {
    int derived;
    friend void friendDrived(Derived* d);
/* D */
    void tryPrivDerived() {
    priv = 0;
    privMethod();
    }
/* E */
    void tryProtDerived() {
    prot = 0;
    protMethod();
    }
/* F */
    void tryPubDerived() {
    pub = 0;
    pubMethod();
    }
};

class PrivateDerived : Base {};

class Rederived : PrivateDerived {
/* G */
void tryPubRederived(){
    pub = 0;
    pubMethod();
}
};
/* H */
void tryPrivOutside() {
    Derived d;
    d.priv = 0;
    d.privMethod();
}
/* I */
void tryProtOutside() {
    Derived d;
    d.prot = 0;
    d.protMethod();
}
/* J */
void tryPubOutside() {
    Derived d;
    d.pub = 0;
    d.pubMethod();
}

void friendBase(Base* b){
    /* K */
    b->priv = 0;
    b->privMethod();
}
void friendDrived(Derived* d){
    /* L */
    d->derived = 0;
    d->tryPubDerived();
    /* M */
    d->priv = 0;    
    d->privMethod();
}

int main(){
    return 0;
}