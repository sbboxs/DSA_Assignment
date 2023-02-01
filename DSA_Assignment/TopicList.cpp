#include "TopicList.h"
using namespace std;

TopicList::TopicList() {
	size = 0;
	firstNode = NULL;
}
TopicList::~TopicList() {
	Node* temp = firstNode;
	while (temp) {
		Node* next = temp->next;
		delete temp;
		temp = next;
	}
}
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
Topic TopicList::get(int index) {
	if (index <= size && index >= 0) {
		Node* temp = firstNode;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp->item;
	}
}
void TopicList::display() {
	Node* temp = firstNode;
}
