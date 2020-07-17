//
// Created by cyx on 20-5-29.
//

#ifndef INTLIST_IMPL_H
#define INTLIST_IMPL_H

#include <iostream>
#include "mylist.h"
using namespace std;
template <class T>
List<T>::List(): first(0),last(0){}

template <class T>
T List<T>::removeFront(){
    if(isEmpty()){
        emptyList e;
        throw e;
    }
    node_t<T> *victim = first;
    //if there is only one element
    if(victim->next == NULL){
        last = victim->next;
    }
    first = victim->next;
    T result = victim->val;
    delete victim;
    return result;
}

template <class T>
void List<T>::removeAll(){
    while(!isEmpty()){
        removeFront();
    }
}

template <class T>
List<T>::~List(){
    removeAll();
}

template <class T>
void List<T>::copyFrom(const List<T> &l){
    if(first != nullptr){
        removeAll();
    }
    const node_t<T> *head = l.returnHead();
    while(head != nullptr){
        insertBack(head->val);
        head = head->next;
    }
}

// copy constructor
template <class T>
List<T>::List(const List &l): first(0),last(0){
    copyFrom(l);
}
// assignment operator
template <class T>
List<T> &List<T>::operator=(const List<T> &l){
    if(this != &l){
        removeAll();
        copyFrom(l);
    }
    return *this;
}

template <class T>
void List<T>::print()
{
    node_t<T>* itr = first;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
bool List<T>::isEmpty() const{
    return (first == NULL);
}

template <class T>
void  List<T>::insertBack(T val){
    node_t<T> *np = new node_t<T>;
    np->next = NULL;
    np->val = val;
    if(isEmpty()) first = last = np;
    else{
        last->next = np;
        last = np;
    }
}

template <class T>
const node_t<T>* List<T>::returnHead() const{
    return first;
}

bool isLarger(const List<int> &a, const List<int> &b){
    if(a.isEmpty() && b.isEmpty()) return false;
    int count_a = 0;
    const node_t<int>* itr_a = a.returnHead();
    while(itr_a){
        count_a++;
        itr_a = itr_a->next;
    }
    int count_b = 0;
    const node_t<int>* itr_b = b.returnHead();
    while(itr_b){
        count_b++;
        itr_b = itr_b->next;
    }

    int greater = 0;
    if(count_a > count_b) return true;
    else if(count_a < count_b) return false;
    else{
        for(int j = 0; j < count_a; j++){
            itr_a = a.returnHead();
            itr_b = b.returnHead();
            for(int i = count_a-1-j; i > 0; i--){
                itr_a = itr_a->next;
                itr_b = itr_b->next;
            }
            if(itr_a->val > itr_b->val){
                greater = 1;
                break;
            }
            else if(itr_a->val < itr_b->val) break;
            else continue;
        } 
    }
    if(greater) return true;
    else return false;
}

int digit(const node_t<int> *itr_a,const node_t<int> *itr_b, bool &over, int digit_a, int digit_b){
    if(digit_a == 1 && digit_b == 1){
    if(over){
        return itr_b->val + itr_a->val + 1;
    }
    else{
        return itr_b->val + itr_a->val;
    }
    }
    else if(digit_a == 1){
        if(over) return itr_a->val + 1;
        else return itr_a->val;
    }
    else if(digit_b == 1){
        if(over) return itr_b->val + 1;
        else return itr_b->val;
    }
    else{
        if(over) return 1;
        else return -1;
        
    } 

}

List<int> Add(const List<int> &a, const List<int> &b){
    List<int> sum;
    bool over = 0;
    const node_t<int>* itr_a = a.returnHead();
    const node_t<int>* itr_b = b.returnHead();
    int digit_a = 1;
    int digit_b = 1;
    while(digit(itr_a,itr_b,over,digit_a,digit_b) != -1){
        int result = digit(itr_a,itr_b,over,digit_a,digit_b);
        digit_a = 0;
        digit_b = 0;
        if(result > 9){
            result -=10;
            over = 1;
        }
        else over = 0;
        sum.insertBack(result);
        if(itr_a->next != NULL){
            digit_a++;
            itr_a = itr_a->next;
        } 
        if(itr_b->next != NULL){
            digit_b++;
            itr_b = itr_b->next;
        } 
    }
    return sum;
}

#endif //INTLIST_IMPL_H
