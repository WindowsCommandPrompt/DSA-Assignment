#pragma once

#include <string> 

typedef std::string ItemType;

class LinkedListNormal
{
private: 
	struct Node {
		ItemType item; 
		Node* next; 
	};

	Node* firstNode; 
	int size; 

public:

	LinkedListNormal(void);
	~LinkedListNormal(void);
	bool add(const ItemType item);
	bool addAt(int index, const ItemType item);
	bool remove(int index);				//removee an item from a specified index position only. 
	ItemType get(int index);					//get the item from a particular index position. 
	bool isEmpty(void);
	int length(void);
	bool contains(const ItemType item) noexcept; 
	std::string to_string(const LinkedListNormal linkedList); 
	void replace(int index, ItemType newItem);
};

