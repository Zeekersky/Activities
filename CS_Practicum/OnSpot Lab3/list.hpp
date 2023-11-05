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

namespace list_namespace
{
  template<class T>
    class list
    {
      public:
	struct node {
		T value;
		node* next;
		node(const T &data) {
			value = data;
			next = nullptr;
		}
	};
	node* head;
	int size;
	


	/*
         * Primary contructor.
         * Should construct an empty list.
         * Size of the created list should be zero.
         */
        list() {
		head = nullptr;
		size = 0;
	}

        /*
         * Seondary constructor.
         * Creates a new list which is a copy of the provided list.
         */
        list(const list<T> & x) {
		head = nullptr;
		node* curr = x.head;
		while(curr) {
			append(curr->value);
			curr = curr->next;
		}
	}
	
        /*
         * Destructor.
         * Frees all the memory acquired by the list.
         */
        ~list() {
		while(head){
			node* temp = head;
			head = head->next;
			delete temp;
		}
	}

        /*
         * adds value at the end of the list.
         */
        void append(const T& value){
		node* nd = new node(value);
		if(head == nullptr) 
			head = nd;
		else{
			node* curr = head;
			while(curr->next)
				curr = curr->next;
			curr->next = nd;
		}
		size += 1;
	}
        /*
         * Returns the length of the list.
         */
        inline int length(){
		return size;
	}
        /*
         * Returns a boolean indicating whether the list is empty.
         */
        inline bool empty(){
		return (head == nullptr);
	}
        /*
         * Adds a value to the front of the list.
         */
        void cons(const T& value) {
		node* nd = new node(value);
		nd->next = head;
		head = nd;
		size += 1;
	}
        /*
         * Removes the first occurence of the value from list.
         */
        void remove(const T & x){
		node* prev = nullptr;
		node* curr = head;
		while(curr != nullptr){
			if(curr->value == x){
				if(prev == nullptr)
					head = curr->next;
				else
					prev->next = curr->next;
				delete curr;
				size -= 1;
				break;
			}
			prev = curr;
			curr = curr->next;
		}
	}
        /*
         * Appends the given list x at the end of the current list.
         */
        void append(list<T>& x){
		node* curr = x.head;
		while(curr != nullptr){
			append(curr->data);
			curr = curr->next;
		}
	}
    };
}
#endif

