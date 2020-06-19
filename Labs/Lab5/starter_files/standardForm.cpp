//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include <cmath>
#include "standardForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in){
    a = a_in;
    b = b_in;
    c = c_in;
}


float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    return b;
}

float quadraticFunction::getC() const {
    return c;
}

float quadraticFunction::evaluate(float x) {
    
    float ans = 0;
    ans += pow(x,2)*getA() + x*getB() + getC();
    return ans;
}

root quadraticFunction::getRoot() {
    root_t root;
    float a = getA(); float b = getB(); float c = getC();
    float det = pow(b,2)-4*a*c;
    if(det == 0){
        root.realRootNum = 1;
        root.roots[0].real = (-b)/(2*a);
        root.roots[0].imaginary = 0;
        root.roots[1].real = (-b)/(2*a);
        root.roots[1].imaginary = 0;
    }
    else if(det > 0){
        root.realRootNum = 2;
        root.roots[0].real = (-b-pow(det,0.5))/(2*a);
        root.roots[0].imaginary = 0;
        root.roots[1].real = (-b+pow(det,0.5))/(2*a);
        root.roots[1].imaginary = 0;
    }
    else{
        root.realRootNum = 0;
        root.roots[0].real = (-b)/(2*a);
        root.roots[1].real = (-b)/(2*a);
        if(a > 0){
            root.roots[0].imaginary = -(pow(-det,0.5)/(2*a));
            root.roots[1].imaginary = pow(-det,0.5)/(2*a);    
        }
        else{
            root.roots[0].imaginary = pow(-det,0.5)/(2*a);
            root.roots[1].imaginary = -(pow(-det,0.5)/(2*a));     
        }
    }
    return root;
}

int quadraticFunction::intersect(quadraticFunction g){
    float d = g.a; float e = g.b; float f = g.c;
    float a = getA(); float b = getB(); float c = getC(); 
    float det = pow(b-e,2)-4*(a-d)*(c-f);
    if(det >= 0) return 1;
    else return 0;
}