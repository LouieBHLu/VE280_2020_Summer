#include <string>
#include <string.h>
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
}
int main(int argc, char *argv[])
{
    if(argc < 2){
        cout << "No work to do!" << endl;
        return 0;
    }
    
    int arr[100];
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    
    int po_help = -1;
    int po_add = -1;
    int po_small = -1;
    int po_verbose = -1;
    int num = -1;

    for(int i = 0; i < argc; i++){
        if(std::string(argv[i]) == "--help") po_help = i;
        else if(std::string(argv[i]) == "--add") po_add = i;
        else if(std::string(argv[i]) == "--small"){
            po_small = i;
            
        } 
        else if(std::string(argv[i]) == "--verbose"){
            po_verbose = i;
        }
        else num = atoi(argv[i]);
            
    }

    if(po_help > 0){
        cout << "Hey, I love Integers." << endl;
        return 0;
    }

    if(po_verbose > 0){
        if(po_add > 0){
            int sum = 0;
            for(int i = 0; i < n; i++){
                sum += arr[i];
            }
            cout << "This is add operation." << endl;
            cout << sum << endl;
        }
        if(po_small > 0){
            int ans;
            cout << "This is small operation." << endl;
            ans = small(0, arr, n) + num;
            cout << ans<< endl;
        }
    }
    else{
        if(po_add > 0){
            int sum = 0;
            for(int i = 0; i < n; i++){
                sum += arr[i];
            }
            cout << sum << endl;
        }
        if(po_small > 0){
            int ans;
            ans = small(0, arr, n) + num;
            cout << ans<< endl;
        }
    }
    return 0;
}
