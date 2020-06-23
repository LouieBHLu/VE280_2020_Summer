#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "recursive.h"
using namespace std;

int countDifference(list_t list1, list_t list2);
// REQUIRES: values inside each list are in increasing order.
//           None of the two lists contain duplicates.
// EFFECTS: returns the number of elements that appear only in one list
//          If the requires clause is not satisfied, an exception
//          of type string is raised.

int main(int argc, char const *argv[])
{
    //first simple testcase
    int list1_num[5] = {0,1,2,3,4};
    int list2_num[4] = {0,1,2,4};
    list_t list1 = list_make();
    list_t list2 = list_make();
    for(int i = 4; i >= 0; i--){
        list1 = list_make(list1_num[i],list1);
    }
    for(int i = 3; i >= 0; i--){
        list2 = list_make(list2_num[i],list2);
    }
    assert(countDifference(list1, list2) == 3);

    //second simple testcase
    int list3_num[6] = {0,1,2,3,4,5};
    int list4_num[5] = {0,1,2,3,4};
    list_t list3 = list_make();
    list_t list4 = list_make();
    for(int i = 5; i >= 0; i--){
        list3 = list_make(list3_num[i],list3);
    }
    for(int i = 4; i >= 0; i--){
        list4 = list_make(list4_num[i],list4);
    }
    assert(countDifference(list3, list4) == 5);

    //third simple testcase
    int list5_num[3] = {0,1,2};
    int list6_num[2] = {0,1};
    list_t list5 = list_make();
    list_t list6 = list_make();
    for(int i = 2; i >= 0; i--){
        list5 = list_make(list5_num[i],list5);
    }
    for(int i = 1; i >= 0; i--){
        list6 = list_make(list6_num[i],list6);
    }
    assert(countDifference(list5, list6) == 2);

    //first boundary testcase
    int list7_num[1] = {0};
    list_t list7 = list_make();
    list_t list8 = list_make();
    list7 = list_make(list7_num[0],list7);
    assert(countDifference(list7, list8) == 0);

    //second boundary testcase
    list_t list9 = list_make();
    list_t list10 = list_make();
    assert(countDifference(list9, list10) == NULL);

    //third boundary testcase
    int list11_num[3] = {0,1,2};
    int list12_num[3] = {0,1,2};
    list_t list11 = list_make();
    list_t list12 = list_make();
    for(int i = 2; i >= 0; i--){
        list11 = list_make(list11_num[i],list11);
    }
    for(int i = 2; i >= 0; i--){
        list12 = list_make(list12_num[i],list12);
    }
    assert(countDifference(list11, list12) == NULL);

    //first non-sense case
    int list13_num[3] = {2,1,0};
    int list14_num[3] = {0,1,2};
    list_t list13 = list_make();
    list_t list14 = list_make();
    for(int i = 2; i >= 0; i--){
        list13 = list_make(list13_num[i],list13);
    }
    for(int i = 2; i >= 0; i--){
        list14 = list_make(list14_num[i],list14);
    }
    try{
        countDifference(list13, list14);
    }
    catch(string wrong){
        cout << "List1 is not in an increasing order!" << endl;
    }

    //second non-sense case
    int list15_num[3] = {0,1,1};
    int list16_num[3] = {0,1,2};
    list_t list15 = list_make();
    list_t list16 = list_make();
    for(int i = 2; i >= 0; i--){
        list15 = list_make(list15_num[i],list15);
    }
    for(int i = 2; i >= 0; i--){
        list16 = list_make(list16_num[i],list16);
    }
    try{
        countDifference(list15, list16);
    }
    catch(string wrong){
        cout << "List1 has duplicates!" << endl;
    }

    //third non-sense case
    int list17_num[4] = {0,1,3,4};
    int list18_num[4] = {0,1,2,3};
    list_t list17 = list_make();
    list_t list18 = list_make();
    for(int i = 3; i >= 0; i--){
        list17 = list_make(list17_num[i],list17);
    }
    for(int i = 3; i >= 0; i--){
        list18 = list_make(list18_num[i],list18);
    }
    try{
        countDifference(list17, list18);
    }
    catch(string wrong){
        cout << "More than one number appearing only in one list!" << endl;
    }

    //fourth non-sense case
    int list19_num[4] = {0,1,4,3};
    int list20_num[4] = {0,1,3,2};
    list_t list19 = list_make();
    list_t list20 = list_make();
    for(int i = 3; i >= 0; i--){
        list19 = list_make(list19_num[i],list19);
    }
    for(int i = 3; i >= 0; i--){
        list20 = list_make(list20_num[i],list20);
    }
    try{
        countDifference(list19, list20);
    }
    catch(string wrong){
        cout << "More than one number appearing only in one list!" << endl;
        cout << "List1 has duplicates!" << endl;
        cout << "List2 has duplicates!" << endl;
    }

    return 0;
}
