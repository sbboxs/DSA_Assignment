//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include "ReplyList.h"
#include <iomanip>
using namespace std;

// Constructor
ReplyList::ReplyList() {
	size = 0;
	firstNode = NULL;
}

// Destructor
ReplyList::~ReplyList() {
	Node* temp = firstNode;
	while (temp) {
		Node* next = temp->next;
		delete temp;
		temp = next;
	}
}

// Check if reply list is empty, return true if empty
bool ReplyList::isEmpty() {
	return firstNode == NULL;
}
bool ReplyList::add(Reply item) {
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

// Add a reply to a specfic location of the reply list
bool ReplyList::add(int index, Reply item) {
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

// Remove a reply by the specific location
void ReplyList::remove(int index) {
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

// Get the reply by its index
Reply ReplyList::get(int index) {
	if (index <= size && index >= 0) {
		Node* temp = firstNode;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp->item;
	}
}

// Get the length of reply list
int ReplyList::getLength() {
	return size;
}

// Display the replies
void ReplyList::display(string title, string topic, string author) {
	bool success = !isEmpty();
	Node* tempNode = firstNode;
	if (success) {
		while (tempNode != NULL) {
			if (tempNode->item.getTitle() == title && tempNode->item.getTopic() == topic) {
				printf("@%s ", tempNode->item.getAuthor());
				cout << endl << "----------------------------" << endl;
				cout << tempNode->item.getReply() << endl << endl;
				cout << "Replied on " << tempNode->item.getDate() << endl;
				cout << "----------------------------------------------------" << endl;
			}
			tempNode = tempNode->next;
		}
	}
	else {
		cout << "There has been no replies yet for this post" << endl;
	}
}
