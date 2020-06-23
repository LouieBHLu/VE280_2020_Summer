#include "vector.h"

class LinearEquation
{
   Vector a1;
   Vector a2;

public:

   LinearEquation(Vector &x, Vector &y);

   Vector solve(Vector &v);
   std::string str();
};
