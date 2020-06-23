#include <iostream>

#include "vector.h"
#include "linearMap.h"
#include "linearEquation.h"

using namespace std;

int main(){
      Vector v1(1, 1);
      Vector v2(2, 0);
      Vector v3(0.5, -4);

      LinearEquation le(v1, v2);
      LinearMap lm(v3);

      cout << v1.toString() << endl;
      cout << v2.toString() << endl;
      cout << v3.toString() << endl;

      cout << le.str() << endl;
      cout << lm.str() << endl;

      cout << le.solve(v3).toString() << endl;
      cout << lm.evaluate(v1).toString() << endl;

      return 0;
}
