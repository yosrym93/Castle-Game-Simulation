#pragma once
#include "Node.h"

template <typename T>
class Queue {
protected:
	int count;
	Node<T>* head;
	Node<T>* tail;
public:
	Queue();
	bool enqueue(const T&);		//inserts an item at the end
	void enqueue(Node<T>*);		//inserts a node at the end
	T peek();					//returns the first item without removing it
 	T dequeue();				//returns and removes the first item
	int getCount() const;		//returns the number of items 
	void clear();				//deletes all the nodes
	~Queue();
};
