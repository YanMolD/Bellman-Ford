#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

template <class T>
struct Node
{
	T value;
	Node* next;
	Node* prev;
	Node(T value)
	{
		this->value = value;
		next = NULL;
		prev = NULL;
	}
	Node(T* value)
	{
		this->value = *value;
		next = NULL;
		prev = NULL;
	}
	Node()
	{
		value = NULL;
		next = NULL;
		prev = NULL;
	}
};

template <class T>
class List
{
private:
	Node<T>* Root;
	Node<T>* Last;
	int Size;
public:
	List()
	{
		Root = NULL;
		Last = NULL;
		Size = 0;
	}
	~List()
	{
		while (Root != NULL)
		{
			Node<T>* n = Root->next;
			delete Root;
			Root = n;
		}
	}
	Node<T>* Get_Root()
	{
		return Root;
	}
	Node<T>* Get_Last()
	{
		return Last;
	}
	void push_back(T* value)
	{
		if (Last != NULL)
		{
			Last->next = new Node<T>(value);
			Last->next->prev = Last;
			Last = Last->next;
		}
		else
		{
			Last = new Node<T>(value);
			Root = Last;
		}
		Size++;
	}
	void push_front(T* value)
	{
		Node<T>* buf = new Node<T>(value);
		buf->next = Root;
		if (Root == NULL)
		{
			Root = buf;
			Last = Root;
		}
		else
		{
			Root->prev = buf;
			Root = Root->prev;
		}
		Size++;
	}
	void pop_back()
	{
		if (Last != Root)
		{
			Node<T>* buf = Last->prev;
			delete Last;
			Last = buf;
			Last->next = NULL;
			Size--;
		}
		else
			clear();
	}
	void pop_front()
	{
		if (Root != Last)
		{
			Node<T>* n = Root->next;
			delete Root;
			Root = n;
			Root->prev = NULL;
		}
		else
			clear();
	}
	T at(int number)
	{
		if (number > size_t() || (number < 0))
			throw out_of_range("Index more than size of List");
		Node<T>* n = Root;
		for (int f = 0; f < number; f++)
			n = n->next;
		return n->value;
	}
	void remove(int number)
	{
		if (number > size_t() || (number < 0))
			throw out_of_range("Index more than size of List");
		Node<T>* n = Root;
		if (number > 0)
		{
			for (int f = 0; f < number; f++)
				n = n->next;
			if (n == Last)
			{
				pop_back();
				return;
			}
			n->prev->next = n->next;
			n->prev->next->prev = n->prev;
			delete n;
		}
		else
			pop_front();
		Size--;
	}
	int size_t()
	{
		return Size;
	}
	void clear()
	{
		while (Root != NULL)
		{
			Node<T>* buf_list = Root->next;
			delete Root;
			Root = buf_list;
		}
		Root = NULL;
		Last = NULL;
	}
	bool isEmpty()
	{
		if (Root == NULL)
			return 1;
		return 0;
	}
};
