/*
 * list.hpp
 *
 * functionality of a singly linked-list
 *
 * define your methods in coherence with the following
 * function signatures
 * 
 * 
 */

#ifndef LIST_HPP
#define LIST_HPP 1

namespace /*your namespace here.*/
{
  template<class T>
    class list
    {
      public:
        /*
         * Primary contructor.
         * Should construct an empty list.
         * Size of the created list should be zero.
         */
        list();
        /*
         * Seondary constructor.
         * Creates a new list which is a copy of the provided list.
         */
        list(const list<T> & x);
        /*
         * Destructor.
         * Frees all the memory acquired by the list.
         */
        ~list();
        /*
         * adds value at the end of the list.
         */
        void append(const T& value);
        /*
         * Returns the length of the list.
         */
        inline int length();
        /*
         * Returns a boolean indicating whether the list is empty.
         */
        inline bool empty();
        /*
         * Adds a value to the front of the list.
         */
        void cons(const T& value);
        /*
         * Removes the first occurence of the value from list.
         */
        void remove(const T & x);
        /*
         * Appends the given list x at the end of the current list.
         */
        void append(list<T>& x);
    };
}

#endif