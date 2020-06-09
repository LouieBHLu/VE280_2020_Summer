#include <string>
#include <limits.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
using namespace std;

int small(int i, int arr[], int length){
    int first = arr[i];
    i++;
    if(i == length) return first;
    int cand = small(i, arr, length);
    if(first <= cand) return first;
    return cand;
    // int first = list_first(list);
    // list_t rest = list_rest(list);
    // if(list_isEmpty(rest)) return first;
    // int cand = smallest(rest);
    // if(first <= cand) return first;
    // return cand;
}

// int main(int argc, char *argv[]){
//     int arr[1000] = {0};

//     return 0;
// }
int main(int argc, char *argv[])
{
    int arr[1000] = {0};
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    if(argc == 1){
        cout << "No work to do!" << endl;
        return 0;
    }

    int po_help, po_add, po_small, po_ver = -1;
    int num;
    for(int i = 0; i < argc; i++){
        if(argv[i] == "--help") po_help = i;
        else if(argv[i] == "--add") po_add = i;
        else if(argv[i] == "--small"){
            po_small = i;
            num = atoi(argv[i+1]);
        } 
        else po_ver = i;
    }
    // if(po_help > 0){
    //     cout << "Hey, I love Integers." << endl;
    //     return 0;
    // }

    // if(po_ver > 0){
    //     if(po_add > 0){
    //         int sum = 0;
    //         for(int i = 0; i < n; i++){
    //             sum += arr[i];
    //         }
    //         cout << "This is add operation." << endl;
    //         cout << sum << endl;
    //     }
    //     if(po_small > 0){
    //         int ans;
    //         cout << "This is small operation." << endl;
    //         ans = small(0, arr, n) + num;
    //         cout << ans<< endl;
    //     }
    // }
    // else{
    //     if(po_add > 0){
    //         int sum = 0;
    //         for(int i = 0; i < n; i++){
    //             sum += arr[i];
    //         }
    //         cout << sum << endl;
    //     }
    //     if(po_small > 0){
    //         int ans;
    //         ans = small(0, arr, n) + num;
    //         cout << ans<< endl;
    //     }
    // }
    return 0;
}
