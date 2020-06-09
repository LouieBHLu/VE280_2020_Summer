#include <cmath>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void Triangle_number(int integer);
void Palindrome(int integer);
void Power_number(int integer);
void Abundant_number(int integer);

int main() {
    int exnum = 0; int intnum = 0;
    while(1){
        cout<<"Please enter the integer and the test number: ";
        cin >> intnum;
        cin >> exnum;
        if(intnum >= 1 && intnum <= 10000000 && exnum >= 1 && exnum <= 4 ) break;
    }
	
    switch (exnum)
        {
        case 1:
            Triangle_number(intnum);
            break;
        case 2:
            Palindrome(intnum);
            break;
        case 3:
            Power_number(intnum);
            break;
        default:
            Abundant_number(intnum);
            break;
        }

        return 0;
}

void Triangle_number(int integer){
    int flag = 0;//test true or false: 0 for false, 1 for true
    /*run every possible value of n. when correct value of n is found, change the flag and
    break the loop*/
    for(double n = 1; n <= integer; n++){
        if(2*integer/n == n + 1){
            flag = 1;
            break;
        }
    }
    cout << flag;
}

void Palindrome(int integer){
    int flag = 1;//test true or false: 0 for false, 1 for true
    string num  = to_string(integer);
    int length = num.size();//the length of the integer
    if(length % 2){//if the length is odd
        for(int i = 0; i < length/2; i++){
            int j = length-1-i;
                if(num[i] != num[j]){
                    flag = 0;
                }
        }
    }
    else{// if the legnth is even
        for(int i = 0; i < length/2; i++){
            int j = length-1-i;
                if(num[i] != num[j]){
                    flag = 0;
                }
        }
    }
    cout << flag;
}

void Power_number(int integer){
    int flag = 0;//test true or false: 0 for false, 1 for true
    double n = 2;
    if(integer == 1) flag = 1;
    else{
        while(pow(integer, 1/n) >= 2){
            int m = pow(integer, 1/n);//whether m^n = integer
            if(m == pow(integer, 1/n)){
                flag = 1;
                break;
            }
            n++;
        }
    }
    cout << flag;
}

void Abundant_number(int integer){
    int flag = 0;//test true or false: 0 for false, 1 for true
    int sum = 0;//the sum of its proper divisors
    for(int i = 1; i <= integer/2; i++){
        if(integer%i == 0) sum += i;//add up every proper divisors
    }
    if(sum > integer) flag = 1;
    cout << flag;
}

