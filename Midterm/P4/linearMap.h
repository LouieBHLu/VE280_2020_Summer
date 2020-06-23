#include "vector.h"

class LinearMap
{

   Vector a;

public:
   LinearMap(Vector &a);

   double evaluate(Vector &v);
   std::string str();
};
