#include "Queue.h"

template <typename T>
Queue<T>::Queue() {
	count = 0;
}

template <typename T>
bool Queue<T>::enqueue(const T& item) {
	Node* newNode = new Node(item);
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

template <typename T>
void Queue<T>::enqueue(Node<T>* newNode) {
	newNode->setNext(nullptr);
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
T Queue<T>::peek() {
	return head->getData();
}

template <typename T>
T Queue<T>::dequeue() {
	if (head == nullptr) return false;
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
	Node* temp;
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