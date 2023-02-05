//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//Feature highlighted: Display all topics by pages
//======================================================
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

int TopicList::displayPages(int targetPage, string username) {
	int count = 1001;
	int topicsPerPage = 7;
	int totalTopics = 0;
	int totalPages = 0;
	int topicsFound = 0;
	int topicsBeSkipped = (targetPage - 1) * 7;
	bool success = !isEmpty();
	Node* tempNode = firstNode;
	if (success) {
		int topicsPrinted = 0;
		if (username != "") {
			//Header
			cout << left << setw(20) << "ID"
				<< setw(30) << "Discussion Topic" << endl;
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
						cout << left << setw(20) << count
							<< setw(30) << tempNode->item.getTopic() << endl;
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
			cout << left << setw(30) << "ID"
				<< setw(60) << "Discussion Topic" <<  "Created by" << endl;
			cout << left << setw(30) << "----"
				<< setw(60) << "----------------" <<  "----------" << endl;
			totalPages = ceil(size / (double)topicsPerPage);
			while (tempNode != NULL) {
				if (topicsFound >= topicsBeSkipped) {
					cout << left << setw(30) << count
						<< setw(60) << tempNode->item.getTopic() <<  tempNode->item.getAuthor() << endl;
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

void TopicList:: mergeSort(TopicList tList, int first, int last) {
	if (first < last) {
		int mid = (first + last) / 2;
		mergeSort(tList, first, mid);
		mergeSort(tList, mid + 1, last);
		merge(tList, first, mid, last);
	}
}

void TopicList::merge(TopicList tList, int first, int mid, int last) {
	TopicList tempList;

	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	int index = first1;
	for (int i = 0; (first1 <= last1) && (first2 <= last2); i++) {
		if (tList.get(i).getTotalPost() < tList.get(first1).getTotalPost()) {
			tempList.get(i) = tList.get(first1);
			first1++;
		}
		else {
			tempList.get(i) = tList.get(first2);
			first2++;
		}
	}
}