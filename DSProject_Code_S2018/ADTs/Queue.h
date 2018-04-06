#pragma once
#include "Node.h"
#include "PrecondViolatedExcep.h"

template <typename T>
class Queue {
	int count;
	Node<T>* head;
	Node<T>* tail;
public:
	Queue();
	bool enqueue(const T&);							//inserts an item at the end
	bool isEmpty() const;								//checks whether the queue is empty
	T peek() throw (PrecondViolatedExcep);			//returns the first item without removing it, throws an exception if queue is empty
 	T dequeue() throw (PrecondViolatedExcep);		//returns and removes the first item, throws an exception if queue is empty
	int getCount() const;							//returns the number of items 
	void clear();									//deletes all the nodes
	~Queue();
};


template <typename T>
Queue<T>::Queue() {
	count = 0;
}

template <typename T>
bool Queue<T>::enqueue(const T& item) {
	Node<T>* newNode = new Node<T>(item);
	if (newNode == nullptr) return false;
	if (head == nullptr) { //empty queue
		head = newNode;
		tail = newNode;
		count++;
	}
	else {
		tail->setNext(newNode);
		tail = tail->getNext();
		count++;
	}
}

template<typename T>
bool Queue<T>::isEmpty() const{
	if (head == nullptr)
		return true;
	return false;
}

template<typename T>
T Queue<T>::peek() {
	if (head == nullptr) {
		string message = "peek() called with empty queue";
		throw (new PrecondViolatedExcep(message));
	}
	else
		return head->getData();
}

template <typename T>
T Queue<T>::dequeue() {
	if (head == nullptr) {
		string message = "dequeue() called with empty queue";
		throw (new PrecondViolatedExcep(message));
	}
	Node* ptr = head;
	head = head->getNext();
	count--;
	return ptr;
}

template <typename T>
int Queue<T>::getCount() const {
	return count;
}

template <typename T>
void Queue<T>::clear() {
	Node<T>* temp;
	while (head != nullptr) {
		temp = head;
		head = head->getNext();
		delete temp;
	}
}

template <typename T>
Queue<T>::~Queue() {
	clear();
}