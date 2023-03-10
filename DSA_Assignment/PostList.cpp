//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include "PostList.h"
#include <iomanip>

using namespace std;

// Constructor
PostList::PostList() {
	size = 0;
	firstNode = NULL;
}
// Destructor
PostList::~PostList() {
	Node* temp = firstNode;
	while (temp) {
 		Node* next = temp->next;
		delete temp;
		temp = next;
	}
}

// Add post item into the list, return true if success
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

// Add post item into specific location of the list, return true if success
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

// Remove post from the specific index location
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

// Get the post from specific location
Post PostList::get(int index) {
	if (index <= size && index >= 0) {
		Node* tempNode = firstNode;
		for (int i = 0; i < index; i++) {
			tempNode = tempNode->next;
		}
		return tempNode->item;
	}
}

// Get the index by searching the topic
int PostList::get(string topic) {
	Node* tempNode = firstNode;
	for (int i = 0; i < size; i++) {
		if (tempNode->item.getTopic()== topic) {
			return i;
		}
		tempNode = tempNode->next;
	}
}

// Check if the post list is empty, return true if empty
bool PostList::isEmpty() {
	return size == 0;
}

// get and return the size of post list
int PostList::getLength() {
	return size;
}

// Display the postlist in paging and its targeted page
int PostList::displayPages(int targetPage, string username) {
	int count = 1001;
	int postsPerPage = 7;
	int totalPosts = 0;
	int totalPages = 0;
	int postsFound = 0;
	int postsBeSkipped = (targetPage - 1) * 7;
	bool success = !isEmpty();
	Node* tempNode = firstNode;
	if (success) {
		//Header
		cout << left << setw(25) << "ID" << setw(30) << "Title"
			<< setw(50) << "Description" << "Author" << endl;
		cout << left << setw(25) << "----" << setw(30) << "-----"
			<< setw(50) << "-----------" << "------" << endl;

		int postsPrinted = 0;
		if (username != "") {
			//Get total posts by user
			while (tempNode != NULL) {
				if (tempNode->item.getAuthor() == username)
				{
					totalPosts += 1;
				}
				tempNode = tempNode->next;
			}
			//Reset the to the first node
			tempNode = firstNode;
			//Make total pages as double then round it up.
			totalPages = ceil(totalPosts / (double)postsPerPage);
			while (tempNode != NULL) {
				if (tempNode->item.getAuthor() == username) {
					//Check if in the range of target page
					if (postsFound >= postsBeSkipped) {
						cout << left << setw(25) << count << setw(30) << tempNode->item.getTitle() << setw(50)
							<< tempNode->item.getDescription() << tempNode->item.getAuthor() << endl;
						postsPrinted += 1;
					}
					if (postsPrinted == postsPerPage)
						break;
					postsFound += 1;

				}
				count += 1;
				tempNode = tempNode->next;

			}
		}
		else {
			totalPages = ceil(size / (double)postsPerPage);
			while (tempNode != NULL) {
				if (postsFound >= postsBeSkipped) {
					cout << left << setw(20) << count
						<< setw(30) << tempNode->item.getTopic() << endl;
					postsPrinted++;
				}
				if (postsPrinted == postsPerPage) {
					break;
				}
				postsFound += 1;
				count += 1;
				tempNode = tempNode->next;

			}

		}
		if (postsPrinted == 0)
			cout << "No Posts yet" << endl;
		cout << endl << "Total Pages: " << targetPage << " of " << totalPages << endl;

	}
	else {
		cout << "No Posts yet" << endl;
	}
	return totalPages;
}

// Display all the post by the selected topics in paging.
int PostList::displayPagesByTopics(int targetPage, string topic) {
	int count = 1001;
	int postsPerPage = 7;
	int totalPosts = 0;
	int totalPages = 0;
	int postsFound = 0;
	int postsBeSkipped = (targetPage - 1) * 7;
	bool success = !isEmpty();
	Node* tempNode = firstNode;
	if (success) {
		//Header
		cout << left << setw(25) << "ID" << setw(30) << "Title"
			<< setw(50) << "Description" << "Author" << endl;
		cout << left << setw(25) << "----" << setw(30) << "-----"
			<< setw(50) << "-----------" << "------" << endl;

		int postsPrinted = 0;
		if (topic != "") {
			//Get total posts created by topics
			while (tempNode != NULL) {
				if (tempNode->item.getTopic() == topic)
				{
					totalPosts += 1;
				}
				tempNode = tempNode->next;
			}
			//Reset the to the first node
			tempNode = firstNode;
			//Make total pages as double then round it up.
			totalPages = ceil(totalPosts / (double)postsPerPage);
			while (tempNode != NULL) {
				if (tempNode->item.getTopic() == topic) {
					//Check if in the range of target page
					if (postsFound >= postsBeSkipped) {
						cout << left << setw(25) << count << setw(30) << tempNode->item.getTitle() << setw(50)
							<< tempNode->item.getDescription() << tempNode->item.getAuthor() << endl;
						postsPrinted += 1;
					}
					if (postsPrinted == postsPerPage)
						break;
					postsFound += 1;

				}
				count += 1;
				tempNode = tempNode->next;

			}
		}
		else {
			totalPages = ceil(size / (double)postsPerPage);
			while (tempNode != NULL) {
				if (postsFound >= postsBeSkipped) {
					cout << left << setw(20) << count
						<< setw(30) << tempNode->item.getTopic() << endl;
					postsPrinted++;
				}
				if (postsPrinted == postsPerPage) {
					break;
				}
				postsFound += 1;
				count += 1;
				tempNode = tempNode->next;

			}

		}
		if (postsPrinted == 0)
			cout << "No Posts yet" << endl;

		cout << endl << "Total Pages: " << targetPage << " of " << totalPages << endl;

	}
	else {
		cout << "No Posts yet" << endl;
	}
	return totalPages;
}
