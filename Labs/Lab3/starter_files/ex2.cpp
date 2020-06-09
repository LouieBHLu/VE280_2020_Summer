#include <iostream>
#include <limits.h>
#include "ex2.h"

using namespace std;

// int fold_help(int count, int arr[], int (*fn) (int, int), int initial, int length){
//     if(count == 0) return initial;
//     else{
//         int temp = fn(arr[length - count], initial);
//         return fold_help(count-1, arr, fn, temp, length);
//     }
// }

int fold (int count, int arr[], int (*fn) (int, int), int initial) {
    // EFFECTS: returns the result of the fold function
    //int length = count;
    if(count == 0) return initial;
    return fn(arr[count - 1], fold(count - 1, arr, fn, initial));
    //return fold_help(count, arr, fn, initial, length);
    // TODO: implement this function recursively
}


int fn_add (int a, int b) {
    // TODO: implement this function such that fold(count, arr, fn_add, 0)
    // returns the sum of all the elements in arr
    return a+b;
}


int fn_count_odd (int a, int n) {
    // TODO: implement this function such that fold(n,arr,fn_count_odd, 0)
    // returns the numebr of odd numbers in the array
    if(a%2 != 0) return n+1;
    else return n;
}

