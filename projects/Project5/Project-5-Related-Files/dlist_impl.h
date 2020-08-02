#include "dlist.h"
#include <cstdlib>

template<class T>
bool Dlist<T>::isEmpty() const{
    return this->first == NULL;
}

template<class T>
void Dlist<T>::insertFront(T *op){
    node *itr = new node;
    //T* newop = new T(*op);
    itr->op = op;
    if (isEmpty()){
        itr->prev= itr; 
        itr->next = itr;
        last = itr;
    } 
    else{
        itr->prev = last;
        itr->next = first;
        last->next = itr;
        first->prev = itr;
    }
    first = itr;
}

template<class T>
void Dlist<T>::insertBack(T *op){
    node *itr = new node;
    itr->op = op;
    if (isEmpty()){
        itr->prev= itr; 
        itr->next = itr;
        first = itr;
    } 
    else{
        itr->prev = last;
        itr->next = first;
        last->next = itr;
        first->prev = itr;
    }
    last = itr;
}

template<class T>
T* Dlist<T>::removeFront(){
    if (isEmpty()){
        emptyList error;
        throw error;
    }
    node *itr = first;
    T *val = itr->op;
    if (itr == itr->next){
        first = NULL;
        last = NULL;
    } 
    else{
        //first = itr->prev->next = itr->next;
        first = itr->next;
        itr->prev->next = itr->next;
        itr->next->prev = itr->prev;
    }
    delete itr;
    return val;
}

template<class T>
T *Dlist<T>::removeBack(){
    if (isEmpty()){
        throw emptyList();
    }
    node* itr = last;
    T* op = itr->op;
    if (itr == itr->next){
        first = NULL;
        last = NULL;
    } 
    else{
        itr->prev->next = itr->next;
        //last = itr->next->prev = itr->prev;
        last = itr->prev;
        itr->next->prev = itr->prev;
    }
    delete itr;
    return op;
}

template<class T>
T *Dlist<T>::remove(bool (*cmp)(const T*, const T*), T* ref){
    //if(isEmpty()) return nullptr;
    node* itr = first;
    T* val = NULL;
    while(itr != last){
        if(cmp(itr->op,ref)){
            val = itr->op;
            if(itr == first){
                first = itr->next;
            } 
            if(itr->next != NULL) itr->next->prev = itr->prev;
            if(itr->prev != NULL) itr->prev->next = itr->next;
            delete itr;
            break;
        }
        itr = itr->next;
    }
    if(last){
        if(itr == last){
            if(cmp(itr->op,ref)){
                val = itr->op;
                last = itr->prev;
                delete itr;
            }
        }
    }

    return val;
}

template<class T>
Dlist<T>::Dlist(){
    first = NULL;
    last = NULL;
}

template<class T>
void Dlist<T>::removeAll(){
    while(!isEmpty()){
        T* op = removeFront();
        delete op;
    }
}

template<class T>
Dlist<T>::~Dlist(){
    removeAll();
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l){
    if (l.last != NULL){
        node* itr = l.last;
        while (itr != l.first){
            T* copy_val = new T(*itr->op);
            insertFront(copy_val);
            itr = itr->prev;
        }
        T* copy_first = new T(*itr->op);
        insertFront(copy_first);
    }
}

template<class T>
Dlist<T>::Dlist(const Dlist &l): first(0),last(0){
    copyAll(l);
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l){
    if (this != &l){
        removeAll();
        copyAll(l);
    }
    return *this;
}



