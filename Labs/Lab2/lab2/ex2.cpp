/*
 * Lab2 Ex2 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct {
    string Name;
    int ChineseScore;
    int MathScore;
    int EnglishScore;
    int flag;
    // TODO: complete struct
} Student;

int compare(const void* p1, const void* p2) {
    // TODO: complete compare function for qsort()
    return *(int *)p2 - *(int *)p1; 
}

int main() {
    // TODO: read input
    int n = 0;
    cin >> n;//number of Students
    Student students[n];
    int sum[n];    
    for(int i = 0; i < n; i++){
        cin >> students[i].Name;
        cin >> students[i].ChineseScore;
        cin >> students[i].MathScore;
        cin >> students[i].EnglishScore;
        students[i].flag = 0;// not found yet
    }
    for(int i = 0; i < n; i++){
        sum[i] = students[i].ChineseScore + students[i].MathScore + students[i].EnglishScore;
    }
    // TODO: sort array with qsort()
    qsort(sum, n, sizeof(int), compare);
    // TODO: print result
    for(int i = 0; i < n; i++){
        for(int j =0; j < n; j++){
            if(sum[i] == students[j].ChineseScore + students[j].MathScore + students[j].EnglishScore && students[j].flag == 0){
                cout << students[j].Name << " ";
                cout << students[j].ChineseScore << " ";
                cout << students[j].MathScore << " ";
                cout << students[j].EnglishScore << '\n';
                students[j].flag = 1;//found
                break;
            }    
        }
    }
    return 0;
}