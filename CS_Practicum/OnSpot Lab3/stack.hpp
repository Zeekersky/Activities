/* 
 * stack.hpp
 * 
 * define your methods in coherence with the following
 * function signatures
 * 
 * use the abstraction of linked lists
 * to implement the functionality of stacks
 * 
 */

#ifndef STACK_HPP_
#define STACK_HPP_
#include "list.hpp"
using namespace std;
namespace stack_namespace
{
  template<typename T>
    class stack
    {
      public:
        /*
         * Constructs a new stack.
         */
	list_namespace::list<T> ls;
        stack() {}
        /*
         * Pushes t to on the top of the stack.
         */
        void push(const T& t){
		ls.cons(t);
	}
        /*
         * Returns the element at the top of the stack.
         * Also removes the top element from the stack.
         */
        T pop(){
		if(ls.empty())
			cout<<"Stack Underflow"<<endl;
		T top = ls.head->value;
		ls.remove(top);
		return top;
	}
        /*
         * Returns the element at the top of the stack.
         * Does not remove the top element.
         */
        T top(){
		if(ls.empty())
			cout<<"Stack Underflow"<<endl;
		else return ls.head->value;
	}
        /*
         * Returns the number of elements currently in the stack.
         */
        int size(){
		return ls.length();
	}
        /*
         * Returns a boolean indicating whether the stack is empty or not.
         */
        inline bool empty(){
		return ls.empty();
	}
        /*
         * Destructor
         * Fress the memory occupied by the stack elements.
         */
        ~stack() {}

    };
}

#endif
