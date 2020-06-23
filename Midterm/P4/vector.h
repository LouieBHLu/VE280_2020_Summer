#include <sstream>
#include <iostream>
using namespace std;

class Vector{
   double w;
   double q;
public:
   Vector(double w, double q);
   Vector(Vector &v);

   double getX();
   double getY();

   Vector add(Vector &v);
   Vector scale(double s);
   double dot(Vector &v);
   string toString();   
};
