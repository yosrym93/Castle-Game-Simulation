
#include "Array.h"
template<class T>
void Array<T>::swap(T*&f, T*&s)
{
	T* temp = f;
	f = s;
	s = temp;
}
template<class T>
void Array<T> ::update()
{
	for (int i = 0;i < size;i++)
	{
		if (arr[i]->getHealth() == 0)
			remove(arr[i]);
	}
}
template<class T>
T* Array<T>::pickRand()
{
	if (size == 0)
		return nullptr;
	return arr[rand() % size];
}
template<class T>
void Array<T>::quickSort(int start, int pivot)
{
	if (start >= pivot)
		return;
	int current = start;
	int wall = start;
	while (current != pivot)
		if (*arr[current] > *arr[pivot])
		{
			current++;
		}
		else
		{
			swap(arr[current], arr[wall]);
			current++;
			wall++;
		}
	swap(arr[wall], arr[pivot]);
	quickSort(start, wall - 1);
	quickSort(wall + 1, pivot);

}
template<class T>
void Array<T>::updateCapacity()
{
	if (size == capacity)
		if (capacity == 0)
		{
			capacity = 1;
			arr = new T*[capacity];
		}
		else
		{
			capacity *= 2;
			T** temp = arr;
			arr = new T*[capacity];
			for (int i = 0; i < size;i++)
			{
				arr[i] = temp[i];
			}
			delete[]temp;

		}
}
template <class T>
int Array<T>::getCount() const 
{
	return size;
}
template <class T>
Array<T>::Array()
{
	size = 0;
	capacity = 0;
}

template<class T>
void Array<T>::insert(T * x)
{
	updateCapacity();
	arr[size] = x;
	size++;
}

template<class T>
void Array<T>::sort()
{
	quickSort(0, size - 1);
}

template<class T>
bool Array<T>::remove(T *ptr)
{
	T*temp;
	for (int i = 0; i < size; i++)
	{
		if (ptr == arr[i])
		{
			temp = ptr;
			swap(arr[i], arr[size - 1]);
			size--;
			delete temp;
			temp = nullptr;
			return true;
		}
	}
	return false;
}

template<class T>
void Array<T>::clear()
{
	delete []arr;
	size = 0;
	capacity = 0;
}

template<class T>
bool Array<T>::isEmpty()
{
	return (size == 0);
}

template<class T>
T* Array<T>::get(int ind) throw(PrecondViolatedExcep)
{
	if (ind >= size || ind < 0)
	{
		string error = "get() called with an invalid index.";
		throw (new PrecondViolatedExcep(error));
	}
	else return arr[ind];
}

/*template<class T>
void Array<T>::print(GUI*pGUI)
{
	string print;
	if (size == 0)
	{
		pGUI->PrintMessage("No enemies");
	}
	else {

		for(int i=0;i<size;i++)
		{
			print = arr[i]->print();
			pGUI->PrintMessage(print);
		}
	}
}*/
template <class T>
Array<T>::~Array()
{
}

