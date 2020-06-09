/*
 * Lab2 Ex1 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <iostream>
using namespace std;

#define RANGE 100000

bool isPrime[RANGE + 1];

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], true for prime, false otherwise
void generateIsPrime() {
    // TODO: implement Eratosthenes Sieve Algorithm
    isPrime[0] = false;
    isPrime[1] = false;
    for(int i = 2; i <= RANGE; i++) isPrime[i] = true;
    for(int i = 2; i*i <= RANGE; i++){
        if(isPrime[i]){
            for(int j = i*i; j <= RANGE; j+=i){
                isPrime[j] = false;
            }        
        }
        }
}

int main() {
    // TODO: generate lookup table
    generateIsPrime();
    // TODO: read input and check if each num is prime
    int n = 0;//the length of the sequence
    cin >> n;
    int num[n];//the array to store the sequence
    for(int k = 0; k < n; k++){//input the sequence
        cin >> num[k];
    }  
    for(int k = 0; k < n; k++){//input all prime number in the original order
      if(isPrime[num[k]]){
        cout << num[k] << " ";   
      }
    }      
    return 0;
}