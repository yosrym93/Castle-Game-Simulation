#pragma once
#include "Node.h"
#include "PrecondViolatedExcep.h"

template <typename T>
class List {
	Node<T>* head;
	Node<T>* tail;
	int count;
public:
	List(); 
	void push(const T&);							//pushes an item to the end of the list
	bool remove(const T&);							//removes an item by its value, returns false if value not in the list
	bool remove(int pos);							//removes an item by its position, returns false if position is out of range
	T get(int pos) throw (PrecondViolatedExcep);	//returns an item at a certain position,  
													//throws an exceptions if pos is out of range
	template<typename S>
	void traverse(void (S::*func)());

	template<typename S>
	void traverse(void (S::*func)(T), S &fnCaller);	//traverses through the list and calls a function from object fnCaller
													//that takes an elemnt in the list as its parameter
	void update();									//update the list (removing killed enemies)
	void clear();									//deletes all items in the list
	bool isEmpty() const;
	int getCount() const;

	void pickRand();								//picks a random element and kill it(by setting the health = 0), for phase 1
	
	~List();
};

template <typename T>
List<T>::List() {
	head = nullptr;
	count = 0;
}
template <typename T>
void List<T>::update() {
	Node<T>*curr = head;
	int i = 0;
	while (curr != nullptr && count>i)
	{
		if (curr->getData()->getHealth() == 0)
			remove(i);
		
		curr = curr->getNext();
		i++;

	}
}
template <typename T>
void List<T>::push(const T& newItem) {
	Node<T>* newNode = new Node<T>(newItem);
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

template <typename T>
bool List<T>::remove(const T& val) {
	Node<T>* tempHead = new Node<int>(0, head);
	Node<T>* ptr = tempHead;
	Node<T>* tempDeleted;
	bool found = false;

	while (ptr->getNext() != NULL) {
		if (ptr->getNext()->getData() == val) {
			tempDeleted = ptr->getNext();
			ptr->setNext(tempDeleted->getNext());
			delete tempDeleted;
			found = true;
			count--;
		}
		else {
			ptr = ptr->getNext();
		}
	}
	head = tempHead->getNext();
	return found;
}

template<typename T>
bool List<T>::remove(int pos) {
	if (pos < 0 || pos >= count) 
		return false;
	else if (pos == 0)
	{
		Node<T>*temp = head;
		head = head->getNext();
		delete temp;
		count--;
		return true;
	}
	Node<T>* ptr = head;
	for (int i = 0; i < pos - 1; i++)
		ptr = ptr->getNext();
	Node<T>* tempDeleted = ptr->getNext();
	ptr->setNext(tempDeleted->getNext());
	delete tempDeleted;
	count--;
	return true;
}

template <typename T>
T List<T>::get(int pos) {
	if (pos < 0 || pos >= count) {
		string message = "get() called with a pos out of range";
		throw (new PrecondViolatedExcep(message));
	}
	Node<T>* ptr = head;
	for (int i = 0; i < pos; i++)
		ptr = ptr->getNext();
	return ptr->getData();
}

template <typename T>
template <typename S>
void List<T>::traverse(void (S::*func)()) {
	Node<T>* ptr = head;
	while(ptr != nullptr) {
		(ptr->getData()->*func)();
	}
}

template <typename T>
template <typename S>
void List<T>::traverse(void (S::*func)(T), S &fnCaller) {
	Node<T>* ptr = head;
	while (ptr != nullptr) {
		(fnPara.*func)(ptr->getData());
	}
}


template <typename T>
void List<T>::clear() {
	Node<T>* temp;
	while (head != nullptr) {
		temp = head;
		head = head->getNext();
		delete temp;
	}
}

template<typename T>
int List<T>::getCount() const {
	return count;
}

template<typename T>
bool List<T>::isEmpty() const {
	if (head == nullptr)
		return true;
	return false;
}

template<typename T>
void List<T>::pickRand() {
	if (count == 0) {
		return ;
	}
	else if (count == 1)
	{
		int ran = 0;
		T temp = get(ran);
		temp->setHealth(0);//kill the enemy
	}
	else {
		int ran = rand() % count;
		T temp = get(ran);
		temp->setHealth(0);//kill the enemy
	}
}

template <typename T>
List<T>::~List() {
	clear();
}

