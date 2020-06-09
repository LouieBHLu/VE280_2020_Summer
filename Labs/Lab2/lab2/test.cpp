<<<<<<< HEAD
/* qsort example */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
typedef struct {
    int price;
    int id;
} order;
order list[6];
int i = 0;

int compare (const void * a, const void * b)
{

  order *orderA = (order *)a;
  order *orderB = (order *)b;

  return ( orderB->price - orderA->price );
}

int main (int argc, char *argv[])
{
int x = 6;
int y = 2;
int n = (x-y)%2;
int m = (y-x)%2;
cout << n << endl;
cout << m << endl;


}
=======
/* qsort example */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
typedef struct {
    int price;
    int id;
} order;
order list[6];
int i = 0;

int compare (const void * a, const void * b)
{

  order *orderA = (order *)a;
  order *orderB = (order *)b;

  return ( orderB->price - orderA->price );
}

int main (int argc, char *argv[])
{
int x;
string s1, s2;
cin >> s1 >> x >> s2;
cout << s1 << " " << x << " " << s2;
}
>>>>>>> e27ff802315dc6a81998cfb4af218a430c670ebd
