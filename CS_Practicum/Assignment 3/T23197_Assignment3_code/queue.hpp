/*
 * queue.hpp
 *
 * define your methods in coherence with the following
 * function signatures
 * 
 * use the abstraction of linked lists
 * to implement the functionality of queues
 * 
 */

#ifndef QUEUE_HPP_
#define QUEUE_HPP_
#include"list.hpp"
using namespace std;
namespace queue_namespace
{
  template <class T>
    class queue
    {
      public:
        /*
         * Constructs a new queue.
         */
	list_namespace::list<T> ls;
        queue() {}
        /*
         * Pushes t to at the back of the queue.
         */
        void push(const T& t){
		ls.append(t);
	}
        /*
         * Returns the element at the front of the queue.
         * Also removes the front element from the queue.
         */
        T pop(){
		if(ls.empty()){
			cout<<"Queue Underflow"<<endl;
			exit(1);
		}
		T front = ls.head->value;
		ls.remove(front);
		return front;
	
	}
        /*
         * Returns the element at the front of the queue.
         * Does not remove the front element.
         */
        T front(){
		if(ls.empty()){
			cout<<"Queue Underflow"<<endl;
		}
		return ls.head->value;
	}
        /*
         * Returns the number of elements currently in the queue.
         */
        inline int size(){
		return ls.size;
	}
        /*
         * Returns a boolean indicating whether the queue is empty or not.
         */
        inline bool empty() {
		return ls.empty();
	}
        /*
         * Destructor
         * Fress the memory occupied by the queue elements.
         */
        ~queue() {}
    };
}
#endif
