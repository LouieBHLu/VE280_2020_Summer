#include <iostream>
#include <sstream>
#include "linearMap.h"

LinearMap::LinearMap(Vector &a):a(a){
}

double LinearMap::evaluate(Vector &v)
{

   return a.dot(v);
}

std::string LinearMap::str(){
   ostringstream os;
   os << a.toString() << " . x";
   return os.str();
}
