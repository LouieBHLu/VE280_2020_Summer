#include "dict.h"

template <class K, class V> 
V *Dict<K,V>::find(K k){
    if(this->size() == 0) return NULL;
    list<K>::iterator itk = keys.begin();
    list<K>::iterator itv = values.begin();
    V* ans;
    for(unsigned int i = 0; i < this->size(); i++){
        if(*itk == k){
            ans = itr;
            break;
        }
        else{
            itk++;
            itv++;
        }
    }
    return ans;
}

template <class K, class V> 
unsigned int Dict<K,V>::size(){
    list<K>::iterator itk = keys.begin();
    unsigned int count = 0;
    while(itk != keys.end()){
        count++;
        itk++;
    }
    return count;
}

template <class K, class V> 
void Dict<K,V>::insert(K k, V v){
    list<K>::iterator itk = keys.begin();
    list<K>::iterator itv = values.begin();
    bool exist = false;
    while(itk != keys.end()){
        if(*itk == k){
            *itv = v;
            exist = true;
            break;
        }
        else{
            itk++;
            itv++;
        }
    }
    if(!exist){
        this->keys->push_back(k);
        this->valus->pushs_back(v);
    }
}

template <class K, class V> 
void Dict<K,V>::remove(K k){
    list<K>::iterator itk = keys.begin();
    list<K>::iterator itv = values.begin();
    while(itk != keys.end()){
        if(*itk == k){
            this->values.erase(itv);
            this->keys.erase(itk);
            break;
        }
        else{
            itk++;
            itv++;
        }
    }
}