
#pragma once
#include <iostream>
#include "ADTs\PrecondViolatedExcep.h"
using namespace std;
template <class T>
class Array
{
	T** arr;								//Array of pointers to Template.
	int size;								//Array size.
	int capacity;							//Array capacity.
	void swap(T* &f, T *&s);				//Swaps two elements in sorting.
	void quickSort(int start, int pivot);	//Sorts using quicksort technique.
	void updateCapacity();					//Adjusts array's capacity based on needed size.


public:
	Array();								//Constructor for the array.
	void insert(T* x);						//Adds new element to the array.
	void sort();							//Sorts the array.
	bool remove(T*);						//Removes a specific pointer from the array.
	void clear();							//Clears all the pointers from the array.
	bool isEmpty();							//Checks whether the array is empty.
	T get(int) throw (PrecondViolatedExcep);//Gets an item using it's index if it exists.
	~Array();
};
