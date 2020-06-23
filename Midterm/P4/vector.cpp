
#include "vector.h"
using namespace std;

Vector::Vector(double w, double q){
   this->w = w;
   this->q = q;
}

Vector::Vector(Vector &v){
   this->w = v.w;
   this->q = v.q;
}

double Vector::getX()
{
   return this->w;
}

double Vector::getY()
{
   return this->q;
}

Vector Vector::add(Vector &v){
   double w1 = getX() + v.w;
   double q1 = getY() + v.q;
   Vector v1 = Vector(w1,q1);
   return v1;
}

Vector Vector::scale(double s){
   return Vector(s*w, s*q);
}

double Vector::dot(Vector &v){
   return w*v.w + q*v.q;
}

string toString(){
   ostringstream is;
   double w1 = getX();
   double q1 = getY();
   is << "(" << getX() << ", " << getY() << ")";
   return is.str();
}
