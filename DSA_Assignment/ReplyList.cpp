//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include "ReplyList.h"
#include <iomanip>
using namespace std;

ReplyList::ReplyList() {
	size = 0;
	firstNode = NULL;
}
ReplyList::~ReplyList() {
	Node* temp = firstNode;
	while (temp) {
		Node* next = temp->next;
		delete temp;
		temp = next;
	}
}
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
Reply ReplyList::get(int index) {
	if (index <= size && index >= 0) {
		Node* temp = firstNode;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp->item;
	}
}
void ReplyList::display(string title, string topic, string author) {
	bool success = !isEmpty();
	Node* tempNode = firstNode;
	if (success) {
		cout << "Topic - " + topic << endl;
		cout << "----------------------------------------------------" << endl;
		while (tempNode != NULL) {
			if (tempNode->item.getTitle() == title && tempNode->item.getTopic() == topic) {
				printf("@%s has replied: ", tempNode->item.getAuthor().c_str());
				cout << endl << tempNode->item.getReply().c_str() << endl << endl;
				cout << "Replied on " << tempNode->item.getDate().c_str();
				cout << "----------------------------------------------------" << endl;
			}
			tempNode = tempNode->next;
		}
	}
	else {
		cout << "There has been no replies yet for this post" << endl;
	}
}
