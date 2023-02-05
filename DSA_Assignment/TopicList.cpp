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
		//Header
		cout << left << setw(20) << "ID"<< setw(30) << "Discussion Topic" << setw(25) << "Total Posts" << endl;

		int topicsPrinted = 0;
		if (username != "") {
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
						cout << left << setw(20) << count << setw(30) << tempNode->item.getTopic() << setw(25) << tempNode->item.getTotalPost() << endl;
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

TopicList TopicList::mergeSort(TopicList tList, int first, int last)
{
	int mid = (first + last) / 2;
	if (first < last)
	{
		TopicList left = mergeSort(tList, first, mid);
		TopicList right = mergeSort(tList, mid + 1, last);
		merge(left, right);
	}
	else
	{
		TopicList result;
		result.add(tList.get(first));
		return result;
	}
}

TopicList TopicList::merge(TopicList left, TopicList right)
{
	TopicList result;
	int i = 0, j = 0;
	int leftSize = left.getLength();
	int rightSize = right.getLength();
	while (i < leftSize && j < rightSize)
	{
		if (left.get(i).getTopic() <= right.get(j).getTopic())
		{
			result.add(left.get(i));
			i++;
		}
		else
		{
			result.add(right.get(j));
			j++;
		}
	}
	//Add remaining
	while (i < leftSize)
	{
		result.add(left.get(i));
		i++;
	}
	while (j < rightSize)
	{
		result.add(right.get(j));
		j++;
	}
	return result;
}