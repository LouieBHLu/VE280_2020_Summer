//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include "factoredForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in){
    a = a_in;
    float det = pow(b_in,2)-4*a*c_in;
    if(det == 0){
        r1.real = (-b_in)/(2*a);
        r1.imaginary = 0;
        r2.real = (-b_in)/(2*a);
        r2.imaginary = 0;
    }
    else if(det > 0){
        r1.real = (-b_in-pow(det,0.5))/(2*a);
        r1.imaginary = 0;
        r2.real = (-b_in+pow(det,0.5))/(2*a);
        r2.imaginary = 0;
    }
    else{
        r1.real = (-b_in)/(2*a);
        r2.real = (-b_in)/(2*a);
        if(a > 0){
            r1.imaginary = -(pow(-det,0.5)/(2*a));
            r2.imaginary = pow(-det,0.5)/(2*a);    
        }
        else{
            r1.imaginary = pow(-det,0.5)/(2*a);
            r2.imaginary = -(pow(-det,0.5)/(2*a));     
        }
    }
}


float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    return -a*(r1.real+r2.real);
}

float quadraticFunction::getC() const {
    if(r1.imaginary == 0){
        return a*r1.real*r2.real;
    }
    else{
        return a*(pow(r1.real,2) + pow(r1.imaginary,2));
    }
}

float quadraticFunction::evaluate(float x) {
    float ans = 0;
    ans += pow(x,2)*getA() + x*getB() + getC();
    return ans;
}

root quadraticFunction::getRoot() {
    root_t root;
    float det = pow(getB(),2)-4*getA()*getC();
    root.roots[0].real = r1.real;
    root.roots[1].real = r2.real;
    root.roots[0].imaginary = r1.imaginary;
    root.roots[1].imaginary = r2.imaginary;
    if(det == 0) root.realRootNum = 1;
    else if(det > 0) root.realRootNum = 2;
    else root.realRootNum = 0;
    return root;
}

int quadraticFunction::intersect(quadraticFunction g) {
    float d = g.a; float e = g.getB(); float f = g.getC();
    float a = getA(); float b = getB(); float c = getC(); 
    float det = pow(b-e,2)-4*(a-d)*(c-f);
    if(det >= 0) return 1;
    else return 0;
}