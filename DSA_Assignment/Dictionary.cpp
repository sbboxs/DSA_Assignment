#include "Dictionary.h"

//Constructor
Dictionary::Dictionary() {
	size = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = NULL;
	}
}

Dictionary::~Dictionary() {
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
	int index = hash(key); //compute index

	if (items[index] == NULL) {
		//new node
		Node* newNode = new Node();
		newNode->key = key;
		newNode->item = newItem;
		newNode->next = NULL;
		//set list at index to point to new node
		items[index] = newNode;
	}
	else {
		Node* temp = nullptr;
		temp = items[index];
		if (items[index]->key == key)
			std::cout << "Same key value: " << key << std::endl;
		return false;
		while (temp->next != NULL) {
			temp = temp->next;
			if (temp->key == key)
				std::cout << "Same key value!" << std::endl;
			return false;
		}
		Node* newNode = new Node();
		newNode->key = key;
		newNode->item = newItem;
		newNode->next = NULL;
		temp->next = newNode;
	}
	size += 1;
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
	return items[index]->item;
}

bool Dictionary::isEmpty() {
	if (size == 0)
		return true;
	else
		false;
}

int Dictionary::getLength() {
	return size;
}

void Dictionary::print() {
	for (int i = 0; i < MAX_SIZE; i++) {
		if (items[i] != NULL) {
			std::cout << "Index: " << i << std::endl;
			Node* temp = items[i];
			while (temp) {
				std::cout << temp->key << " ";
				std::cout << temp->item.getPassword() << " ";
				temp = temp->next;
			}
			std::cout << endl;
		}
	}
}