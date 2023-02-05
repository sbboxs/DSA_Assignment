//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
// List.h - - Specification of List ADT (implemented using Pointers)
#pragma once
#include<string>
#include<iostream>
#include "Topic.h"
#include "User.h"
using namespace std;

class TopicList
{
public:
	struct Node
	{
		Topic item;	// item
		Node* next;	// pointer pointing to next item
	};
	Node* firstNode;	// point to the first item
	int  size;		// number of items in the list


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

	int get(string topic);

	// check if the list is empty
	bool isEmpty();

	// check the size of the list
	int getLength();

	//To display topics by pages
	int displayPages(int targetPage, string username);

	//sort the linked list using merge sort
	void sort(TopicList& sortedList);

	//Helper functions for merge sort
	Node* sort(Node* currentNode, int listSize);
	Node* mergeLists(Node* leftList, int leftListSize, Node* rightList, int rightListSize);
	Node* getMiddleNode(Node* currentNode, int listSize);
};