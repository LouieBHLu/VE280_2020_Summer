#include <cassert>

// Example file that tests a function add
int add(int, int);

int main(){
   // first test case
   int a=0;
   int b=0;
   assert(0 == add(a, b));

   // second test case
   int c=1; 
   int d=-1;
   assert(0 == add(c, d));

   return 0;
}
