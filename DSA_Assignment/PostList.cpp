#include "PostList.h"
#include <iomanip>

using namespace std;

PostList::PostList() {
	size = 0;
	firstNode = NULL;
}
PostList::~PostList() {
	Node* temp = firstNode;
	while (temp) {
		Node* next = temp->next;
		delete temp;
		temp = next;
	}
}
bool PostList::add(Post item) {
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
bool PostList::add(int index, Post item) {
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
void PostList::remove(int index) {
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
Post PostList::get(int index) {
	if (index <= size && index >= 0) {
		Node* temp = firstNode;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp->item;
	}
}

bool PostList::isEmpty() {
	bool ifEmpty = size = 0;
	return ifEmpty;
}

int PostList::getLength() {
	return size;
}

void PostList::display() {
	cout << left << setw(25) << "Title"
		 << setw(25) << "Description"
		 << setw(25) << "Author" << endl;
	Node* tempNode = firstNode;
	while (tempNode != NULL) {
		cout << left << setw(25) << tempNode->item.getTitle().c_str()
			 << setw(25) << tempNode->item.getDescription().c_str()
			 << setw(25) << tempNode->item.getAuthor().c_str() << endl;
		tempNode = tempNode->next;
	}
}
