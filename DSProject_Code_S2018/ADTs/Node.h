#pragma once
template <typename T>
class Node
{
	T data;
	Node* next;
public:
	Node();
	Node(const T&, Node<T>* = nullptr);	//initializer constructor
	void setData(const T& d);		//sets the data
	T getData() const;				//returns the data
	void setNext(Node*);			//sets the next pointer
	Node<T>* getNext() const;				//returns the next pointer
	~Node();
};


template <typename T>
Node<T>::Node()
{
}

template <typename T>
Node<T>::Node(const T& d, Node<T>* n) : data(d), next(n)
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
Node<T>* Node<T>::getNext() const {
	return next;
}

template <typename T>
Node<T>::~Node()
{
}


