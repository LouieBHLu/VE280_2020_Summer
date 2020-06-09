/*
 * Lab2 Ex3 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <cmath>
#include <iostream>

using namespace std;

#define MAX_LEN 1024

int square[MAX_LEN][MAX_LEN];

void initSquare(int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            square[i][j] = 1;
        }
    }
}

// REQUIRES: the square with left-upper corner at (x,y)
//           and length len is within square[MAX_LEN][MAX_LEN]
// MODIFIES: square[][]
// EFFECTS: fully update the specified square
void updateSquare(int x, int y, int len) {
    // TODO: check boundary condition
    if(len == 1) return;
    // TODO: update left upper square
    for(int i = 0; i < len/2; i++){
        for(int j = 0; j < len/2; j++){
            square[x + i][y + j] = 0;
        }
    }
    // TODO: recursive call for remaining 3 squares
    updateSquare(x + len/2, y + len/2, len/2);
    updateSquare(x + len/2, y, len/2);
    updateSquare(x, y + len/2, len/2);
}

void printSquare(int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            cout << square[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // TODO: read input
    int length; cin >> length;
    // TODO: init, update, and print square
    initSquare(pow(2, length));
    updateSquare(0, 0, pow(2, length));
    printSquare(pow(2, length));
    return 0;
}
