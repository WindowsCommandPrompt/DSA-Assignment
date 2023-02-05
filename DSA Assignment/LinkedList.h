#pragma once

#include <iostream>
#include <string> 

template <class T> 
class LinkedList
{
private: 
	struct Node {
		T item; 
		Node* next; 
	};


	Node* firstNode; 
	int size; 

public:
	LinkedList(const LinkedList&) = default; 
	LinkedList& operator=(const LinkedList&) = default; 
	//LINKED LIST DEFINITION....
	LinkedList(void) {
		this->firstNode = nullptr;
		this->size = 0;
	}
	LinkedList(LinkedList&& list)
	{
		firstNode = list.firstNode;
		list.firstNode = nullptr;
		size = list.size;
	}
	~LinkedList(void) {
		do {
			if (this->size > 1) {
				Node* currentNode = firstNode;
				Node* prevNode = firstNode;
				while (currentNode->next != nullptr) {
					currentNode = currentNode->next;
				}
				while (prevNode->next != currentNode) {
					prevNode = prevNode->next;
				}
				prevNode->next = nullptr;
				delete currentNode;
				--this->size;
			}
			else {
				delete firstNode;
				--this->size;
			}
		} while (this->size > 0);
	}
	// error: if both get method is in use, will result in read access violation -- 
	T& get1(int index) {
		if (index >= 0) { //Index of first element begins at 0, no negative numbers allowed here
			if (index == 0) {
				return firstNode->item;
			}
			else {
				Node* current = firstNode; //start at the first node
				int p = 0;
				while (p < index) {
					current = current->next;
					++p;
				}
				return current->item;
			}
		}
	}

	T&&& get2(int index) {			//For LinkedList<Reply>
		if (index >= 0) { //Index of first element begins at 0, no negative numbers allowed here
			if (index == 0) {
				return firstNode->item;
			}
			else {
				Node* current = firstNode; //start at the first node
				int p = 0;
				while (p < index) {
					current = current->next;
					++p;
				}
				return current->item;
			}
		}
	}

	T&& get(int index) {
		if (index >= 0) { 
			if (index == 0) {
				return std::move(firstNode->item);
			}
			else {
				Node* current = firstNode; 
				int p = 0;
				while (p < index) {
					current = current->next;
					++p;
				}
				return std::move(current->item);
			}
		}
	}


	bool isEmpty(void) {
		return this->firstNode == nullptr && this->size == 0;
	}

	int length(void) {
		return this->size;
	}

	bool add(T item) {
		if (this->firstNode == nullptr) {
			Node* newNode = new Node; //create a temporary node which stores the node that we are going to insert into the linked list; 
			newNode->item = item; //assign the item segment of that node with the item
			newNode->next = nullptr;
			this->firstNode = newNode;
		}
		else
		{
			Node* current = this->firstNode; //pointing towards the first node
			Node* newNode = new Node; //create a temporary node which stores the node that we are going to insert into the linked list; 
			newNode->item = item; //assign the item segment of that node with the item
			while (current->next != nullptr) {
				current = current->next; //IS THIS THE TRAVERSAL PART????? 
			}
			//once the program breaks out of the while loop, we should arrive at the end of the linked list (current) that is a null
			current->next = newNode; //point to the newNode
			newNode->next = nullptr;
		}
		this->size++;
		return true;
	}

	bool addAt(int index, T item) {
		// [ e1, e2, e3 ]
		//   0   1   2 
		bool inRange = index >= 0 && index <= this->size;
		if (inRange) {
			//Create a new node first of the node that you want to insert into the linked list
			Node* newNode = new Node;
			if (index == 0) {
				newNode->next = nullptr;
				newNode->item = item;
				this->firstNode = newNode;
			}
			else { //for all values that is greater than 0
				if (index + 1 <= size - 1) {
					//Create a new node which points to the node that you are trasversing to in the linked list
					Node* prev = this->firstNode; //previous node 
					Node* after = this->firstNode; //next node
					int p = 0;
					while (p < index - 1) {
						prev = prev->next; //go to the previous node
						++p;
					}
					p = 0;
					while (p < index) {
						after = after->next; //go to the next node 
						++p;
					}
					newNode->item = item; //set item to attribute of newNode to item as supplied in the parameter
					prev->next = newNode;
					++this->size;
					newNode->next = after;
				}
				else {
					newNode->item = item;
					Node* current = this->firstNode;
					while (current->next != NULL) {
						current = current->next; //IS THIS THE TRAVERSAL PART????? 
					}
					//once the program breaks out of the while loop, we should arrive at the end of the linked list (current) that is a null
					current->next = newNode; //point to the newNode
					newNode->next = NULL;
				}
			}
		}
		this->size++;
		return inRange;
	}

	bool remove(int index) {
		if (index >= 0) {
			if (index == 0) {
				Node* current = this->firstNode;
				this->firstNode = (current->next);
			}
			else {
				Node* previous = this->firstNode;
				Node* after = this->firstNode;
				int p = 0;
				while (p < index - 1) {
					previous = previous->next;
					++p;
				}
				p = 0;
				while (p < index + 1) {
					after = after->next;
					++p;
				}
				delete previous->next; //delete the node after previous first!!!
				previous->next = index == this->size - 1 ? nullptr : after; //connect previous node and after node together (skipping current node)
			}
			--this->size;
			return true;
		}
		else {
			return false;
		}
	}

	bool contains(const T target) {
		Node* firstNode = this->firstNode;
		while (firstNode) {
			firstNode = firstNode->next;
			if (firstNode->item == target) return true;
		}
		return false;
	}
};

