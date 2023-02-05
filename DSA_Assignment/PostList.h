//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
// List.h - - Specification of List ADT (implemented using Pointers)
#pragma once
#include<string>
#include<iostream>
#include "Post.h"
using namespace std;

class PostList
{
private:
	struct Node
	{
		Post item;	// item
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;		// number of items in the list

public:
	// constructor
	PostList();

	// destructor
	~PostList();

	// add an item to the back of the list (append)
	bool add(Post item);

	// add an item at a specified position in the list (insert)
	bool add(int index, Post item);

	// remove an item at a specified position in the list
	void remove(int index);

	// get an item at a specified position of the list (retrieve)
	Post get(int index);

	// check if the list is empty
	bool isEmpty();

	// check the size of the list
	int getLength();

	// display all the items in the list
	void userDisplay(string username);
	void topicDisplay(string topic);
};

