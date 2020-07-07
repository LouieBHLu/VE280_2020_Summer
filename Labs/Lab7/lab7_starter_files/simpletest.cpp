//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-25.
//

#include "course.h"

int main() {

    //Course *ve281 = create("Technical", "VE281", false, 0);
    //Course *ve370 = create("Technical", "VE370", false, 0);
    Course *ve482 = create("Upper Level Technical", "VE482", true, 5);

    try{
        //ve482->updateTask("Homework", 1, 9, 20);
        ve482->updateTask("Lab", 1, 9, 15);
        ve482->print();
        ve482->updateTask("Lab", 2, 9, 30);
        ve482->print();
        ve482->updateTask("Lab", 3, 10, 1);
        ve482->print();
        ve482->updateTask("Lab", 4, 10, 10);
        // ve482->finishTask("Homework", 1, 9, 19);
        // ve482->updateTask("Homework", 2, 9, 30);
        // ve482->finishTask("Lab", 2, 9, 22);
        // ve482->updateTask("Homework", 3, 10, 14);
        // ve482->updateTask("Team Project", 1, 10, 13);
        ve482->print();
        ve482->updateTask("Project", 1, 9, 30);
        ve482->print();
        ve482->updateTask("Project", 1, 9, 16);
        ve482->print();


        // ve281->updateTask("Lab", 1, 9, 23);
        // ve281->updateTask("Project", 1, 9, 30);
        // ve281->print();
        // ve281->finishTask("Lab", 1, 9, 23);
        // //ve281->print();
        // ve281->updateTask("Lab", 2, 10, 2);
        // ve281->updateTask("Project", 1, 10, 4);
        // ve281->print();

        // ve370->updateTask("Project", 1, 9, 27);
        // ve370->updateTask("Homework", 1, 9, 25);
        // ve370->updateTask("Homework", 1, 9, 25);
        // ve370->print();
        // ve370->finishTask("Project", 1, 9, 25);
        // ve370->finishTask("Homework", 1, 9, 30);
        // ve370->updateTask("Homework", 2, 10, 15);
        // ve370->print();
    }
    catch(tooManyTasks){
        std::cout << "Too many tasks\n";
    }

    //delete ve281;
    //delete ve370;
    delete ve482;

    return 0;
}

