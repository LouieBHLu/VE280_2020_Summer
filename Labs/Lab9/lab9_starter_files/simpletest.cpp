//
// Created by cyx on 20-6-12.
//

#include <iostream>
#include "mylist.h"

int main() {

    try{
        List<int> la, lb;
        la.insertBack(3);
        la.insertBack(4);
        la.insertBack(2);
        la.insertBack(5);
        la.print();
         // a = 3145
        lb.insertBack(6);
        lb.insertBack(3);
        lb.insertBack(2);
        lb.insertBack(6);
        lb.print();
        //lb.removeFront(); // b = 314
        // lb.print();
        // lb.removeFront();
        // lb.print();
        // lb.removeFront();
        // lb.print();
        // lb.removeFront();
        // lb.print();
        //lb.removeFront();
        //lb.print();


        std::cout << isLarger(la, lb) << '\n';

        List<int> ab_sum(la);
        ab_sum.print();
        ab_sum = Add(la, lb);
        ab_sum.print();

        // List<bool> lc;
        // lc.insertBack(true);
        // lc.insertBack(false);
        // lc.insertBack(true);
        // lc.insertBack(true);
        // lc.insertBack(false);
        // lc.print();
        // List<bool> ld(lc);
        // ld.print();
        // ld.removeFront();
        // ld.print();
    }
    catch(emptyList){
        std::cout << "Remove from empty list!\n";
    }

    return 0;
}

