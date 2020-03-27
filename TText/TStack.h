#pragma once

template <class T>
struct TNode
{
	T val;
	TNode* pNext;
};

template <class T>
class TStack
{
private:
	TNode<T>* pFirst;
public:
	TStack();
	~TStack();

	void Push(const T& a);
	T Pop();
	T Top();
	bool IsEmpty();
	bool IsFull();
	void Clear();
};

template <class T>
TStack<T>::TStack()
{
	pFirst = NULL;
}

template <class T>
TStack<T>::~TStack()
{
	TNode<T>* tmp = pFirst;
	while (pFirst != NULL)
	{
		pFirst = pFirst->pNext;
		delete tmp;
		tmp = pFirst;
	}
}

template <class T>
void TStack<T>::Push(const T& a)
{
	if (IsFull())
	{
		throw 2;
	}
	TNode<T>* tmp = new TNode<T>;
	tmp->val = a;
	tmp->pNext = pFirst;
	pFirst = tmp;
}

template <class T>
T TStack<T>::Pop()
{
	if (IsEmpty())
	{
		throw 3;
	}
	T res = pFirst->val;
	TNode<T>* tmp = pFirst;
	pFirst = pFirst->pNext;
	delete tmp;
	return res;
}

template <class T>
T TStack<T>::Top()
{
	if (IsEmpty())
	{
		throw 3;
	}
	T tmp = pFirst->val;
	return tmp;
}

template <class T>
bool TStack<T>::IsEmpty()
{
	if (pFirst != NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template <class T>
bool TStack<T>::IsFull()
{
	TNode<T>* p = new TNode<T>;
	if (p)
	{
		delete p;
		return false;
	}
	else
	{
		return true;
	}
}

template <class T>
void TStack<T>::Clear()
{
	TNode<T>* tmp = pFirst;
	while (pFirst != NULL)
	{
		pFirst = pFirst->pNext;
		delete tmp;
		tmp = pFirst;
	}
}