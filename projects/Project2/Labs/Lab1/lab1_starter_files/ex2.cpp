/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[]){
    int length = 0;
    // for(int i = 0; i < 50; i++){
    //     if(password[i] == NULL) break;
    //     length++;
    // }
    while(password[length]) length++;

    for(int i = 0; i < length; i++){
        if(((password[i]>='a')&&(password[i]<='z'))||((password[i]>='A')&&(password[i]<='Z'))) break;
        if(i == length - 1) return 0;
    }
    for(int i = 0; i < length; i++){
        if((password[i]>='0')&&(password[i]<='9')) break;
        if(i == length - 1) return 0;
        }
    for(int i = 0; i < length; i++){
        if(!(((password[i]>='a')&&(password[i]<='z'))||((password[i]>='A')&&(password[i]<='Z')) || ((password[i]>='0')&&(password[i]<='9')))) break;
        if(i == length - 1) return 0;
    }
    return 1;
}


int main(){
    char password[50] = {};
    cin >> password;
    cout << isValidPassword(password) << endl;
    
}
