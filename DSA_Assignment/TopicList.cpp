//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//Feature highlighted: Display all topics by pages
//======================================================
#include "TopicList.h"
#include <iomanip>
using namespace std;

// Constructor
TopicList::TopicList() {
	size = 0;
	firstNode = NULL;
}

// Destructor
TopicList::~TopicList() {
	Node* temp = firstNode;
	while (temp) {
		Node* next = temp->next;
		delete temp;
		temp = next;
	}
}

// Check if empty
bool TopicList::isEmpty() {
	return firstNode == NULL;
}

// Add a topic item into the list, if success return true
bool TopicList::add(Topic item) {
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;
	if (firstNode == NULL) {
		firstNode = newNode;
	}
	else {
		Node* temp = firstNode;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	size += 1;
	return true;
}

// Add a topic item into a specfic location in the list, if succeess return true
bool TopicList::add(int index, Topic item) {
	if (index <= size && index >= 0) {
		Node* newNode = new Node;
		newNode->item = item;
		newNode->next = NULL;
		if (index == 0) {
			newNode->next = firstNode;
			firstNode = newNode;
		}
		else {
			Node* temp = firstNode;
			for (int i = 0; i < index - 1; i++) {
				temp = temp->next;
			}
			newNode->next = temp->next;
			temp->next = newNode;
		}
		size += 1;
		return true;
	}
	else {
		return false;
	}
}

// Remove a topic item in the specfic index
void TopicList::remove(int index) {
	if (index <= size && index >= 0) {
		if (index == 0) {
			firstNode = firstNode->next;
		}
		else {
			Node* temp = firstNode;
			for (int i = 0; i < index - 1; i++) {
				temp = temp->next;
			}
			Node* removeNode = firstNode;
			for (int i = 0; i < index; i++) {
				removeNode = removeNode->next;
			}
			temp->next = removeNode->next;
		}
		size -= 1;
	}
}

// Return the topic item found at the index
Topic TopicList::get(int index) {
	if (index <= size && index >= 0) {
		Node* temp = firstNode;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp->item;
	}
}

// Get the index by searching of the topic
int TopicList::get(string topic) {
	Node* tempNode = firstNode;
	for (int i = 0; i < size; i++) {
		if (tempNode->item.getTopic() == topic) {
			return i;
		}
		tempNode = tempNode->next;
	}
}

// Get the length of the list
int TopicList::getLength() {
	return size;
}

// Display the topics in list by paging and the targeted page
int TopicList::displayPages(int targetPage, string username) {
	if (isEmpty()) {
		cout << "No Topics yet" << endl;
		return 0;
	}
	int count = 1001;
	int topicsPerPage = 7;
	int totalTopics = 0;
	int totalPages = 0;
	int topicsFound = 0;
	int topicsBeSkipped = (targetPage - 1) * topicsPerPage;
	bool success = !isEmpty();
	Node* tempNode = firstNode;
	if (success) {
		int topicsPrinted = 0;
		if (username != "") {
			//Header
			cout << left << setw(25) << "ID" << setw(50) << "Discussion Topic" << "Total Posts" << endl;
			cout << left << setw(25) << "----"
				<< setw(50) << "----------------" << "----------" << endl;
			//Get total topics created by user
			while (tempNode != NULL) {
				if (tempNode->item.getAuthor() == username)
				{
					totalTopics += 1;
				}
				tempNode = tempNode->next;
			}
			//Reset the to the first node
			tempNode = firstNode;
			//Make total pages as double then round it up.
			totalPages = ceil(totalTopics / (double)topicsPerPage);
			while (tempNode != NULL) {
				if (tempNode->item.getAuthor() == username) {
					//Check if in the range of target page
					if (topicsFound >= topicsBeSkipped) {
						cout << left << setw(25) << count << setw(50) << tempNode->item.getTopic()
							<< setw(25) << tempNode->item.getTotalPost() << endl;
						topicsPrinted += 1;
					}
					if (topicsPrinted == topicsPerPage)
						break;
					topicsFound += 1;

				}
				count += 1;
				tempNode = tempNode->next;

			}
		}
		else {
			//Header
			cout << left << setw(25) << "ID" << setw(50) << "Discussion Topic" << setw(25)
				<< "Total Posts" << "Created by" << endl;
			cout << left << setw(25) << "----"
				<< setw(50) << "----------------" << setw(25) << "-----------" << "----------" << endl;
			totalPages = ceil(size / (double)topicsPerPage);
			while (tempNode != NULL) {
				if (topicsFound >= topicsBeSkipped) {
					cout << left << setw(25) << count
						<< setw(50) << tempNode->item.getTopic() << setw(25) << tempNode->item.getTotalPost()
						<< tempNode->item.getAuthor() << endl;
					topicsPrinted++;
				}
				if (topicsPrinted == topicsPerPage) {
					break;
				}
				topicsFound += 1;
				count += 1;
				tempNode = tempNode->next;

			}

		}
		cout << endl << "Total Pages: " << targetPage << " of " << totalPages << endl;

	}
	else {
		cout << "No Topics yet" << endl;
	}
	return totalPages;
}

//Use to mergesort link list from small to large
void TopicList::sort(TopicList& sortedList) {
	Node* sortedListHead = sort(firstNode, size);
	sortedList.firstNode = sortedListHead;
	sortedList.size = size;
	//Trying to avoid node pointed to unsorted list changed.
	
	//Node* sortedListHead = sort(firstNode, size);
	//sortedList.firstNode = NULL;
	//sortedList.size = 0;

	//Node* tempNode = sortedListHead;
	//while (tempNode != NULL) {
	//	sortedList.add(tempNode->item);
	//	tempNode = tempNode->next;
	//}
}

//Helper function for merge sort to separete link to to half and sort
TopicList::Node* TopicList::sort(Node* currentNode, int listSize) {
	//Base case
	if (listSize == 1) 
		return currentNode;

	Node* middleNode = getMiddleNode(currentNode, listSize);
	int leftListSize = listSize / 2;
	int rightListSize = listSize - leftListSize;
	Node* leftList = sort(currentNode, leftListSize);
	Node* rightList = sort(middleNode, rightListSize);
	return mergeLists(leftList, leftListSize, rightList, rightListSize);
}

// helper function of merge sort to merge the left and right list
TopicList::Node* TopicList::mergeLists(Node* leftList, int leftListSize, Node* rightList, int rightListSize) {
	Node tempNode;
	Node* tail = &tempNode;
	tempNode.next = NULL;
	while (leftListSize > 0 && rightListSize > 0) {
		if (leftList->item.getTotalPost() < rightList->item.getTotalPost()) {
			tail->next = leftList;
			leftList = leftList->next;
			leftListSize -= 1;
		}
		else {
			tail->next = rightList;
			rightList = rightList->next;
			rightListSize -= 1;
		}
		tail = tail->next;
	}
	if (leftListSize > 0) tail->next = leftList;
	else tail->next = rightList;
	return tempNode.next;
}

// helper function of merge sort to get the middle node
TopicList::Node* TopicList::getMiddleNode(Node* currentNode, int listSize) {
	Node* temp = currentNode;
	for (int i = 0; i < listSize / 2; i++) {
		temp = temp->next;
	}
	return temp;
}