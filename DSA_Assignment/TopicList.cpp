#include "TopicList.h"
#include <iomanip>
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
bool TopicList::isEmpty() {
	return firstNode == NULL;
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

int TopicList::getLength() {
	return size;
}

//Topic TopicList::userDisplay(string username) {
//	bool success = !isEmpty();
//	Node* tempNode = firstNode;
//	if (success) {
//		while (tempNode != NULL) {
//			if (tempNode->item.getAuthor().c_str() == username) {
//				return tempNode->item;
//			}
//			else {
//				tempNode = tempNode->next;
//			}
//		}
//	}
//}

void TopicList::display(string username) {
	int count = 1001;
	bool success = !isEmpty();
	Node* tempNode = firstNode;
	if (success) {
		cout << left << setw(20) << "ID"
			<< setw(30) << "Discussion Topic" << setw(25) << "Created By" << endl;

		while (tempNode != NULL) {
			if (username == "") {
				cout << left << setw(20) << count
					<< setw(30) << tempNode->item.getTopic() << setw(25) << tempNode->item.getAuthor() << endl; 
			}
			else {
				if (tempNode->item.getAuthor() == username) {
					cout << left << setw(20) << count
						<< setw(30) << tempNode->item.getTopic() << setw(25) << tempNode->item.getAuthor() << endl;
				}
			}
			tempNode = tempNode->next;
			count += 1;
		}
	}
	else {
		cout << "No Topics yet" << endl;
	}
}

void TopicList::userDisplay(string username) {
	int count = 1001;
	bool success = !isEmpty();
	Node* tempNode = firstNode;
	if (success) {
		cout << left << setw(20) << "ID"
			<< setw(30) << "Discussion Topic" << setw(25) << endl;
		while (tempNode != NULL) {
			if (tempNode->item.getAuthor() == username) {
				cout << left << setw(20) << count
					<< setw(30) << tempNode->item.getTopic() << setw(25) << endl;
			}
			tempNode = tempNode->next;
			count += 1;
		}
	}
	else {
		cout << "No Topics yet" << endl;
	}
}



