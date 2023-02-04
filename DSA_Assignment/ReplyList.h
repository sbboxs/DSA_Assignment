// List.h - - Specification of List ADT (implemented using Pointers)
#pragma once
#include<string>
#include<iostream>
#include "Reply.h"
using namespace std;

class ReplyList
{
private:
	struct Node
	{
		Reply item;	// item
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;		// number of items in the list

public:
	// constructor
	ReplyList();

	// destructor
	~ReplyList();

	// add an item to the back of the list (append)
	bool add(Reply item);

	// add an item at a specified position in the list (insert)
	bool add(int index, Reply item);

	// remove an item at a specified position in the list
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	Reply get(int index);

	// check if the list is empty
	bool isEmpty();

	// check the size of the list
	int getLength();

	// display all the items in the list
	void display(string title, string topic, string author);
};

