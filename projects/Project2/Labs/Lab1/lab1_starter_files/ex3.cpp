/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return the trace of the Laplacian of the weight matrix.
int traceLaplacian(int weight[][50], int size){
    int degree[50][50] = {};
    int laplace[50][50] = {};
    int ans = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == j){
                for(int k = 0; k < size; k++){
                    degree[i][j] += weight[i][k];
                }
            }
            else degree[i][j] = 0;
        }
    }
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            laplace[i][j] = degree[i][j] - weight[i][j];
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == j){
                    ans += laplace[i][j];
                }
            }
        }
    
    return ans;
}


int main(){
    int size, trace;
    int weight[50][50] = {};
    cin >> size;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            cin >> weight[i][j];
    trace = traceLaplacian(weight, size);
    cout << trace << endl;
}
