/*
 * This is an exercise of VE280 Lab 10, SU2020.
 * Written by Martin Ma.
 * Latest Update: 7/17/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#ifndef MY_STACK_H
#define MY_STACK_H


class stackEmpty
// Overview: An exception class.
{};


template <class T>
struct Node
// Overview: Node.
{
    Node* next;
    T val;
};


template <class T>
class Stack
// Overview: A list based stack.
{

private:
    /* Attributes */
    Node<T>* head;

    /* Utilities */
    void removeAll();
    // EFFECTS: called by destructor/operator=
    //          to remove and destroy all list elements.

    void copy_helper(Node<T>* node);
    //helper function for copyFrom

    void copyFrom(const Stack &s);
    // MODIFIES: this
    // EFFECTS: called by copy constructor/operator=
    //          to copy elements from a source list l to this list;
    //          if this list is not empty originally,
    //          removes all elements from it before copying.

public:

    Stack();
    // constructor
    Stack(const Stack &s);
    // copy constructor
    Stack &operator = (const Stack &s);
    // assignment operator
    ~Stack();
    // destructor


    /* Methods */
    void print();
    // EFFECTS: print the elements in the stack

    bool isEmpty() const;
    // EFFECTS: returns true if list is empty, false otherwise.

    size_t size() const;
    // EFFECTS: returns the size of the stack.

    void push(T val);
    // MODIFIES: this
    // EFFECTS: inserts val at the top of the stack.

    void pop();
    // MODIFIES: this
    // EFFECTS: removes the top element from a non-empty stack and returns its val;
    //          in case of empty stack, throws an instance of emptyList if empty.

    T top() const;
    // EFFECTS: returns the top element from a stack.

};

template <class T>
void reverse(Stack<T> &s);
// MODIFIES: s
// EFFECTS: reverse stack s.
//           * for example:
//             [12345] => [54321]

/* Operators */
template <class T>
Stack<T> operator +(Stack<T> &s, T val);
// EFFECTS: append stack s by val.
//          for example:
//             [123] + 4 => [1234]

template <class T>
Stack<T> operator +(Stack<T> &first, Stack<T> &second);
// MODIFIES: first
// EFFECTS: append stack first by another stack second.
//          for example:
//             [123] + [45] => [12345]


#include "my_stack_impl.h"

#endif //MY_STACK_H