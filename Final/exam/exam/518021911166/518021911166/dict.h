#ifndef DICT_H
#define DICT_H

#include <list>
using namespace std;

// DON'T MODIFY THIS HEADER FILE

template <class K, class V> 
// K is the type of the keys and 
// V is the type of the values in the dictionary
class Dict{
   list<K> keys;
   list<V> values;
public:
   Dict();
   V *find(K k); // TODO
   // EFFECTS: returns a pointer to the value associated 
   //          to key k if it is in the dictionary, and 
   //          NULL otherwise
   void insert(K k, V v); // TODO
   // MODIFIES: this
   // EFFECTS: add the pair (k, v) in the dictionary if
   //          k was not in it before, otherwise updates 
   //          the value associated to k with value v
   void remove(K k); // TODO
   // MODIFIES: this
   // EFFECTS: remove the pair (k, v) from the dictionary
   //          if k was in it, otherwise does nothing
   unsigned int size(); // TODO
   // EFFECTS: return the number of pairs (k, v) in the
   //          dictionary
};

#include "dict.hpp"

#endif
