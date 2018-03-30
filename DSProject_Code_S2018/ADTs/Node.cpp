#include "Node.h"


template <typename T>
Node<T>::Node()
{
}

template <typename T>
Node<T>::Node(const T& d, T* n) : data(d), next(n)
{
}

template <typename T>
void Node<T>::setData(const T& d) {
	data = d;
}

template <typename T>
T Node<T>::getData() const {
	return data;
}

template <typename T>
void Node<T>::setNext(Node* n) {
	next = n;
}

template <typename T>
T* Node<T>::getNext() const {
	return next;
}

template <typename T>
Node<T>::~Node()
{
}
