/*
 * recursive.h
 * 
 * A simple interface to two recursively-defined, applicative
 * structures, lists and trees.
 */

#ifndef __RECURSIVE_H__
#define __RECURSIVE_H__

/*
 * lists
 *
 * A well-formed list is either:
 *      the empty list
 *   or an integer followed by a well-formed list.
 *
 * Lists are applicative (functional) data structures---in other
 * words, they are immutable.
 */
 

/*
 * We define lists using the following type declaration.  Don't worry
 * if you don't understand what this means---we haven't covered the
 * syntax for this sort of declaration yet.  For the purposes of this
 * project, just assume that "list_t" is the name of a type that you can
 * use just like "int" or "double".
 */

struct opaque_list;
typedef opaque_list *list_t;

list_t select(list_t lElements, list_t lIndices);
// REQUIRES: values in lIndices correspond to correct indices in lElements
//           indices in lIndices are in increasing order
// EFFECTS: returns all the elements of lElements (in the same order)
//          whose indices appear in lIndices

extern bool list_isEmpty(list_t list);
   // EFFECTS: returns true if list is empty, false otherwise

list_t list_make();
   // EFFECTS: returns an empty list.

list_t list_make(int elt, list_t list);
   // EFFECTS: given the list (list) make a new list consisting of
   //          the new element followed by the elements of the
   //          original list. 

extern int list_first(list_t list);
   // REQUIRES: list is not empty
   // EFFECTS: returns the first element of list

extern list_t list_rest(list_t list);
   // REQUIRES: list is not empty
   // EFFECTS: returns the list containing all but the first element of list

extern void list_print(list_t list);
    // MODIFIES: cout
    // EFFECTS: prints list to cout.

extern bool list_equal(list_t l1, list_t l2);
   // EFFECTS: returns true iff l1 == l2.

#endif /* __RECURSIVE_H__ */