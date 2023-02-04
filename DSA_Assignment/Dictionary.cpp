//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include "Dictionary.h"

//Constructor
Dictionary::Dictionary() {
	size = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = nullptr;
	}
}

Dictionary::~Dictionary() {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* current = items[i];
		while (current != nullptr) {
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}
}

int Dictionary::hash(KeyType key) {
	int index = 0;
	for (int i = 0; i < key.length(); i++) {
		int c = key[i];
		index += c;
	}
	index = index * 52 % MAX_SIZE;
	return index;
}

bool Dictionary::add(KeyType key, ItemType newItem) {
	int index = hash(key);

	Node* temp = items[index];
	while (temp != nullptr) {
		if (temp->key == key) {
			return false;
		}
		temp = temp->next;
	}

	Node* newNode = new Node();
	newNode->key = key;
	newNode->item = newItem;
	newNode->next = items[index];
	items[index] = newNode;

	size++;
	return true;
}

void Dictionary::remove(KeyType key) {
	int index = hash(key);
	if (items[index] != NULL) {
		Node* temp = nullptr;
		temp = items[index];
		//if first at index
		if (temp->key == key) {
			std::cout << "Removed: " << temp->key << " " << temp->item.getPassword() << std::endl;
			items[index] = temp->next;
			delete temp;
		}
		else {
			while (temp) {
				if (temp->next->key == key) {
					Node* deletedNode = temp->next;
					temp->next = deletedNode->next;
					std::cout << "Removed: " << deletedNode->key << " " << deletedNode->item.getPassword() << std::endl;
					delete deletedNode;
					break;
				}
				else
					temp = temp->next;
			}
		}

		size -= 1;
	}
	else
		std::cout << "Index out of range" << std::endl << std::endl;
}

ItemType Dictionary::get(KeyType key) {
	int index = hash(key);

	Node* temp = items[index];
	while (temp != nullptr) {
		if (temp->key == key) {
			return temp->item;
		}
		temp = temp->next;
	}
	return ItemType();
}

bool Dictionary::isEmpty() {
	return size == 0;
}

int Dictionary::getLength() {
	return size;
}

void Dictionary::print() {
	for (int i = 0; i < MAX_SIZE; i++) {
		if (items[i] != NULL) {
			std::cout << "Index: " << i << std::endl;
			Node* temp = items[i];
			while (temp != nullptr) {
				std::cout << temp->key << " " << temp->item.getPassword() << std::endl;
				temp = temp->next;
			}
		}
	}
}