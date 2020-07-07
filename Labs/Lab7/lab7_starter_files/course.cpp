//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-22.
//


#include "course.h"

typedef struct task{
    std::string type;
    int index; // Task index of type
    int due_month;
    int due_day;
} Task;
/*
 * Task is used to represent tasks in a course.
 * type could be "Lab", "Project" and etc., which specifies the type of the task,
 * index is the number of task of this type,
 * due_month and due_day specifies its due date
 */

const int MAXTASKS = 4; // default maximum number of tasks in a course at a time
class TechnicalCourse : public Course {
protected:
    Task *tasks;
    int numTasks;
    int sizeTasks;
    std::string course_code;
public:
    TechnicalCourse(const std::string &course_code, int size){
        this->course_code = course_code;
        this->tasks = new Task[size];
        this->numTasks = 0;
        this->sizeTasks = size;
    }

    TechnicalCourse(const std::string &course_code){
        this->course_code = course_code;
        this->tasks = new Task[MAXTASKS];
        this->numTasks = 0;
        this->sizeTasks = MAXTASKS;
    }

    ~TechnicalCourse();
    
    virtual void updateTask(const std::string &type, int index, int due_month, int due_day);
    void finishTask(const std::string &type, int index, int finish_month, int finish_day);
    void print();
};

void TechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: if Task index of type already exists in tasks, updates its due_month & due_day ;
//          otherwise, adds Task i of type at the end of tasks if tasks is not full,
//          throw an exception if tasks is full
{
    int flag = 0;
    int order = 0;
    for(int i = 0; i <= this->numTasks-1; i++){
        if(type == this->tasks[i].type){
            if(index == this->tasks[i].index){
                flag++;
                order = i;
                break;
            }
        }
    }

    if(flag){
        this->tasks[order].due_month = due_month;
        this->tasks[order].due_day = due_day;
    }
    else{
        if(this->numTasks == this->sizeTasks){
            tooManyTasks full;
            throw full;
        } 
        else{
            this->tasks[numTasks].type = type;
            this->tasks[numTasks].index = index;
            this->tasks[numTasks].due_month = due_month;
            this->tasks[numTasks].due_day = due_day;
            if(type == "Lab" || type == "Project"){
                cout << this->course_code << " " << this->tasks[numTasks].type
                << " " << this->tasks[numTasks].index << " is released! Submit it via oj!" << endl;  
            }
            else{
                cout << this->course_code << " " << this->tasks[numTasks].type
                << " " << this->tasks[numTasks].index << " is released! Submit it via canvas!" << endl;  
            }
            this->numTasks++;
        }
    }
}

void TechnicalCourse::finishTask(const std::string &type, int index, int finish_month, int finish_day)
// REQUIRES: Task index of type is in tasks. finish_month and finish_day are in normal range.
// MODIFIES: this
// EFFECTS: removes Task index of type
{
    int flag = 0;
    int order = 0;
    for(int i = 0; i <= this->numTasks-1; i++){
        if(type == this->tasks[i].type){
            if(index == this->tasks[i].index){
                order = i;
                if(this->tasks[i].due_month < finish_month) flag = 1;
                else if(this->tasks[i].due_month > finish_month) flag = 0;
                else{
                    if(this->tasks[i].due_day < finish_day) flag = 1;
                    else flag = 0;
                }
                break;
            }
        }
    }

    if(flag){
        cout <<this->course_code << " " << this->tasks[order].type
        << " " << this->tasks[order].index << " is overdue!" << endl;  
    }
    else{
        cout <<this->course_code << " " << this->tasks[order].type
        << " " << this->tasks[order].index << " is finished!" << endl;  
    }
    
    //delete the task
    for(int i = order; i <= this->numTasks-2; i++){
        this->tasks[i].type = this->tasks[i+1].type;
        this->tasks[i].index = this->tasks[i+1].index;
        this->tasks[i].due_day = this->tasks[i+1].due_day;
        this->tasks[i].due_month = this->tasks[i+1].due_month;
    }
    this->tasks[numTasks-1].type ="";
    this->tasks[numTasks-1].index = 0;
    this->tasks[numTasks-1].due_day = 0;
    this->tasks[numTasks-1].due_month = 0;
    numTasks--;
}

void TechnicalCourse::print()
{
    std::cout << course_code << std::endl;
    for(int i = 0; i < numTasks; ++i){
        std::cout << tasks[i].type << " " << tasks[i].index << ": "
                  << tasks[i].due_month << "/" << tasks[i].due_day << std::endl;
    }
}

TechnicalCourse::~TechnicalCourse(){
    delete[] tasks;
}

class UpperlevelTechnicalCourse : public TechnicalCourse {
public:
    UpperlevelTechnicalCourse(const std::string &course_code, int size):TechnicalCourse(course_code,size){};

    UpperlevelTechnicalCourse(const std::string &course_code):TechnicalCourse(course_code){};
    
    void updateTask(const std::string &type, int index, int due_month, int due_day);
};

void UpperlevelTechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: If Task index of type does not exist in tasks,
//          adds Task i of type according to its due date if tasks is not full, throw an exception if tasks is full.
//          If Task index of type already exists in tasks,
//          updates its position in tasks & due_month & due_day if its due_month/due_day is changed,
//          do nothing if its due_month/due_day is unchanged.
{
    int flag = 0;
    int order = 0;
    int position = 0;
    for(int i = 0; i <= this->numTasks-1; i++){
        if(type == this->tasks[i].type){
            if(index == this->tasks[i].index){
                flag++;
                order = i;
                break;
            }
        }
    }

    if(flag){
        this->tasks[order].due_month = due_month;
        this->tasks[order].due_day = due_day;
        for(int i = 0; i < this->numTasks-1; i++){
            for (int j = 0; j < this->numTasks-1-i; j++){
                if(this->tasks[j].due_month > this->tasks[j+1].due_month){
                    //swap
                    int temp_index = this->tasks[j].index;
                    this->tasks[j].index = this->tasks[j+1].index;
                    this->tasks[j+1].index = temp_index;
                    string temp_type = this->tasks[j].type;
                    this->tasks[j].type = this->tasks[j+1].type;
                    this->tasks[j+1].type = temp_type;
                    int temp_month = this->tasks[j].due_month;
                    this->tasks[j].due_month = this->tasks[j+1].due_month;
                    this->tasks[j+1].due_month = temp_month;
                    int temp_day = this->tasks[j].due_day;
                    this->tasks[j].due_day = this->tasks[j+1].due_day;
                    this->tasks[j+1].due_day = temp_day;

                }
                else if(this->tasks[j].due_month == this->tasks[j+1].due_month){
                    if(this->tasks[j].due_day > this->tasks[j+1].due_day){
                        //swap
                        int temp_index = this->tasks[j].index;
                        this->tasks[j].index = this->tasks[j+1].index;
                        this->tasks[j+1].index = temp_index;
                        string temp_type = this->tasks[j].type;
                        this->tasks[j].type = this->tasks[j+1].type;
                        this->tasks[j+1].type = temp_type;
                        int temp_month = this->tasks[j].due_month;
                        this->tasks[j].due_month = this->tasks[j+1].due_month;
                        this->tasks[j+1].due_month = temp_month;
                        int temp_day = this->tasks[j].due_day;
                        this->tasks[j].due_day = this->tasks[j+1].due_day;
                        this->tasks[j+1].due_day = temp_day;
                    }
                }
            }
        }
    }
    else{
        if(this->numTasks == this->sizeTasks){
            tooManyTasks full;
            throw full;
        } 
        else{
            //check the position to insert
            if(this->numTasks == 0){
                this->tasks[0].type = type;
                this->tasks[0].index = index;
                this->tasks[0].due_month = due_month;
                this->tasks[0].due_day = due_day;
                position = 0;
            }
            else{
                int i = 0;
                for(i = 0; i <= this->numTasks-1; i++){
                    if(this->tasks[i].due_month < due_month) continue;
                    else if(this->tasks[i].due_month == due_month){
                        if(this->tasks[i].due_day < due_day) continue;
                        else if(this->tasks[i].due_day == due_day){
                            for(int j = this->numTasks-1; j >= i+1; j--){
                                this->tasks[j+1].type = this->tasks[j].type;
                                this->tasks[j+1].index = this->tasks[j].index;
                                this->tasks[j+1].due_day = this->tasks[j].due_day;
                                this->tasks[j+1].due_month = this->tasks[j].due_month;
                            }
                            this->tasks[i+1].type = type;
                            this->tasks[i+1].index = index;
                            this->tasks[i+1].due_month = due_month;
                            this->tasks[i+1].due_day = due_day;
                            position = i+1;
                            break;
                        }
                        else{
                        for(int j = i+1; j <= this->numTasks; j++){
                            this->tasks[j].type = this->tasks[j-1].type;
                            this->tasks[j].index = this->tasks[j-1].index;
                            this->tasks[j].due_day = this->tasks[j-1].due_day;
                            this->tasks[j].due_month = this->tasks[j-1].due_month;
                        }
                        position = i;
                        this->tasks[i].type = type;
                        this->tasks[i].index = index;
                        this->tasks[i].due_month = due_month;
                        this->tasks[i].due_day = due_day;
                        break;
                        }
                    }
                    else{
                        for(int j = i+1; j <= this->numTasks; j++){
                            this->tasks[j].type = this->tasks[j-1].type;
                            this->tasks[j].index = this->tasks[j-1].index;
                            this->tasks[j].due_day = this->tasks[j-1].due_day;
                            this->tasks[j].due_month = this->tasks[j-1].due_month;
                        }
                        this->tasks[i].type = type;
                        this->tasks[i].index = index;
                        this->tasks[i].due_month = due_month;
                        this->tasks[i].due_day = due_day;
                        position = i;
                        break;
                    }
                }
                if(i == this->numTasks){
                    position = this->numTasks;
                    this->tasks[position].type = type;
                    this->tasks[position].index = index;
                    this->tasks[position].due_month = due_month;
                    this->tasks[position].due_day = due_day;
                }
            }

            if(type == "Lab" || type == "Project"){
                cout << this->course_code << " " << this->tasks[position].type
                << " " << this->tasks[position].index << " is released! Submit it via oj!" << endl;  
            }
            else if(type == "Team Project"){
                cout << this->course_code << " " << this->tasks[position].type
                << " " << this->tasks[position].index << " is released! Submit it via github!" << endl;  
            }
            else{
                cout << this->course_code << " " << this->tasks[position].type
                << " " << this->tasks[position].index << " is released! Submit it via canvas!" << endl;  
            }
            this->numTasks++;
        }
    }
}

Course *create(const std::string &class_type, const std::string &course_code, bool assign_size, int tasks_size)
{
    if(class_type == "Technical"){
        if(assign_size){
            return new TechnicalCourse(course_code, tasks_size);
        }
        else{
            return new TechnicalCourse(course_code);
        }
    }
    else if(class_type == "Upper Level Technical"){
        if(assign_size){
            return new UpperlevelTechnicalCourse(course_code, tasks_size);
        }
        else{
            return new UpperlevelTechnicalCourse(course_code);
        }
    }
    else{
        return nullptr;
    }
}
