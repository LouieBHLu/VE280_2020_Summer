/*
 * VE280 Lab 3, SU2020.
 * Written by Guoxin Yin
 */

#include <iostream>

using namespace std;

const int MAXSIZE = 10;

bool canWin(int count, int arr[], int position) {
    // EFFECTS: return whether the player can win given the start position
    // and the card sequence
    int i = 0;
    int j = 0;
    if(arr[position] == 280) return 1;
    else{
        int value = arr[position];
        arr[position] = -1;
        if(position + value <= count-1/*在边界内*/ && arr[position + value] > 0/*没被翻开*/){
            //arr[position + arr[position]] = -1;
            i = canWin(count, arr, position + value);
        }
        if(position - value >= 0 && arr[position - value] > 0){
            //arr[position - arr[position]] = -1;
            j = canWin(count, arr, position - value);
        }
        if(i || j) return 1;
        else return 0;
    // TODO: implement this function
    }
}

int main(){
    int count;
    cin >> count;
    int arr[MAXSIZE];
    for (int i = 0; i < count; ++i) {
        cin >> arr[i];
    }
    int position;
    cin >> position;
    cout << canWin(count, arr, position);
}