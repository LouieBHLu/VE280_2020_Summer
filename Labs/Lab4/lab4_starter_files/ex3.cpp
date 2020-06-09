#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    string strResult;
    getline(cin, strResult);
    int order = 0;
    int num = 0;
    string name[1000];

    while(strResult[order]){
        if(strResult[order] == ','){
            num++;
        }
        if(strResult[order] != ' ' && strResult[order] != ','){
            name[num] = name[num] + strResult[order];
        }
        order++;
    }
    num++;
    for(int i = 0; i < num; i++){
        cout << name[i] << endl;
    }
    cout << num;
    return 0;
}
