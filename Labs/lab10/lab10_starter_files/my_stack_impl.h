/*
 * This is an exercise of VE280 Lab 10, SU2020.
 * Written by Martin Ma.
 * Latest Update: 7/17/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#ifndef MY_STACK_IMPL_H
#define MY_STACK_IMPL_H

#include <iostream>
#include "my_stack.h"


template <class T>
void Stack<T>::print()
{
    Node<T>* itr = head;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
Stack<T>::Stack(){
    head = nullptr;
}

template <class T>
void Stack<T>::copy_helper(Node<T>* node){
    if(!node) return;
    copy_helper(node->next);
    push(node->val);
}

template <class T>
void Stack<T>::copyFrom(const Stack &s){
    copy_helper(s.head);
}

template <class T>
Stack<T>::Stack(const Stack &s): head(0){
    copyFrom(s);
}

template <class T>
Stack<T>& Stack<T>::operator = (const Stack &s){
    if(this != &s){
        removeAll();
        copyFrom(s);
    }
    return *this;
}

template <class T>
bool Stack<T>::isEmpty() const{
    return (head == NULL);
}

template <class T>
size_t Stack<T>::size() const{
    size_t result = 0;
    Node<T>* itr = head;
    while(itr != NULL){
        itr = itr->next;
        result++;
    }
    return result;
}

template <class T>
T Stack<T>::top() const{
    if(!isEmpty()) return head->val;
    else{
        stackEmpty empty_stack;
        throw empty_stack;
    }
}

template <class T>
void Stack<T>::pop(){
    if(isEmpty()){
        stackEmpty empty_stack;
        throw empty_stack;
    }
    Node<T>* victom = head;
    head = victom->next;
    delete victom;
}

template <class T>
void Stack<T>::push(T val){
    Node<T>* np = new Node<T>;
    np->val = val;
    np->next = NULL;
    // If the head is NULL just assign it to np;
    if(head == NULL) head = np;
    else{
        np->next = head;
        head = np;
    } 
}

template <class T>
void Stack<T>::removeAll(){
    while(!isEmpty()){
        pop();
    }
}

template <class T>
Stack<T>::~Stack(){
    removeAll();
}

template <class T>
void reverse(Stack<T> &s){
    T vals[s.size()];
    int i = 0;
    while(!s.isEmpty()){
        vals[i] = s.top();
        s.pop();
        i++;
    }
    for(int j = 0; j < i; j++){
        s.push(vals[j]);
    }
}

template <class T>
Stack<T> operator +(Stack<T> &s, T val){
    Stack<T> append;
    if(s.isEmpty()) append.push(val);
    T vals1[s.size()];
    int i = 0;
    while(!s.isEmpty()){
        vals1[i] = s.top();
        s.pop();
        i++;
    }
    for(int j = i-1; j >= 0; j--){
        append.push(vals1[j]);
    }
    for(int j = i-1; j >= 0; j--){
        s.push(vals1[j]);
    }
    reverse(append);
    append.push(val);
    reverse(append);
    return append;
}

template <class T>
Stack<T> operator +(Stack<T> &first, Stack<T> &second){
    T vals1[first.size()];
    T vals2[second.size()];
    int size1 = first.size();
    int size2 = second.size();
    int i = 0;
    while(!first.isEmpty()){
        vals1[i] = first.top();
        first.pop();
        i++;
    }
    i = 0;
    while(!second.isEmpty()){
        vals2[i] = second.top();
        second.pop();
        i++;
    }
    Stack<T> append;
    for(int j = size2-1; j >= 0; j--){
        append.push(vals2[j]);
    }
    for(int j = size1-1; j >= 0; j--){
        append.push(vals1[j]);
    }
    for(int j = size2-1; j >= 0; j--){
        second.push(vals2[j]);
    }
    for(int j = size1-1; j >= 0; j--){
        first.push(vals1[j]);
    }
    return append;
}


#endif //MY_STACK_IMPL_H