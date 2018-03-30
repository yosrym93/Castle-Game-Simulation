#pragma once
template <typename T>
class Node
{
	T data;
	Node* next;
public:
	Node();
	Node(const T&, T* = nullptr);	//initializer constructor
	void setData(const T& d);		//sets the data
	T getData() const;				//returns the data
	void setNext(Node*);			//sets the next pointer
	T* getNext() const;				//returns the next pointer
	~Node();
};

