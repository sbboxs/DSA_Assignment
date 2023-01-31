// List.h - - Specification of List ADT (implemented using Pointers)
#pragma once
#include<string>
#include<iostream>

using namespace std;

template<typename Itemtype>

class LinkList
{
private:
	struct Node
	{
		TopicType item;	// item
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;		// number of items in the list

public:
	// constructor
	LinkedList();

	// destructor
	~LinkedList();

	// add an item to the back of the list (append)
	bool add(TopicType item);

	// add an item at a specified position in the list (insert)
	bool add(int index, TopicType item);

	// remove an item at a specified position in the list
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	ItemType get(int index);

	// check if the list is empty
	bool isEmpty();

	// check the size of the list
	int getLength();

	// display all the items in the list
	void display();
};



