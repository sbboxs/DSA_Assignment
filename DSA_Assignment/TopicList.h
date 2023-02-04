// List.h - - Specification of List ADT (implemented using Pointers)
#pragma once
#include<string>
#include<iostream>
#include "Topic.h"
#include "User.h"
using namespace std;

class TopicList
{
private:
	struct Node
	{
		Topic item;	// item
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;		// number of items in the list

public:
	// constructor
	TopicList();

	// destructor
	~TopicList();

	// add an item to the back of the list (append)
	bool add(Topic item);

	// add an item at a specified position in the list (insert)
	bool add(int index, Topic item);

	// remove an item at a specified position in the list
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	Topic get(int index);

	// check if the list is empty
	bool isEmpty();

	// check the size of the list
	int getLength();

	// display all the items in the list
	void display(string username);

	//TopicList userDisplay(string username);
	void userDisplay(string username);

	//To display topics by pages
	void displayPages(int page, string username);
};