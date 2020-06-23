#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(int argc, char const *argv[])
{
    int integer[argc-1] = {0};
    for(int i = 0; i < argc-1; i++){
        integer[i] = atoi(argv[i+1]);
    }

    int max = -INT_MAX;
    int min = INT_MAX;
    for(int i = 0; i < argc-1; i++){
        //EEFECT: find the max number 
        if(integer[i] >= max) max = integer[i];
    }
    for(int i = 0; i < argc-1; i++){
        //EEFECT: find the min number
        if(integer[i] < max) min = integer[i];
    }

    for(int i = 0; i < argc-1; i++){
        if(atoi(argv[i+1]) == max || atoi(argv[i+1]) == min) continue;
        else{
            cout << argv[i+1] << " ";
        }
    }
    return 0;
}
