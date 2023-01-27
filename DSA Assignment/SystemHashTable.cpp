// Completed by Ho Min Teck and Li Zhe Yun 
#include "SystemHashTable.h"

SystemHashTable::SystemHashTable(void) {
	//array but using linked list from LinkedListTrackPost.
	this->size = 0; 
}

// Deconstructor
SystemHashTable::~SystemHashTable() 
{

}

// hash function
int SystemHashTable::hash(KeyType key) 
{
	int hashNo = 0;
	int index;
	
	//int characters;
	//int len = key.length();
	//if (key.length() < 2) {
	//	characters = charvalue(key[0]);
	//	return characters;
	//}
	//characters = (charvalue(key[0]) * 52 + charvalue(key[1]))%MAX_SIZE;

	//for (int c = 1; c + 1 < len; c++) 
	//{
	//	if (c + 1 != key.length())
	//	{
	//		characters = (characters * 52 + charvalue(key[c + 1])) % MAX_SIZE;
	//	}
	//}
	//return 	characters % MAX_SIZE;
	size++;
	return index;
}

bool SystemHashTable::add(KeyType newKey, ValueType newItem)
{
	// create a new node 
	Node* newNode = new Node;
	// Compute the index using hash function 
	int index = hash(newKey);
	if (items[index] == NULL) {
		// Create a new node
		Node* newNode = new Node;
		// Set list at index to point to new node
		newNode->item = newItem;
		newNode->key = newKey;
		newNode->next = NULL;
	}
	else {
		// set current pointer to the first node at index
		items[index] = newNode;
		Node* current = items[index];
		// if current node has the same key, then return false
		if (current->key == newKey) {
			return false;
		}
		// while not at last node 
		while (current->next != NULL) {
			// iterate to the next node
			current = current->next;
			// if current node has the same key, then return false
			if (current->key == newKey) {
				return false;
			}
		}
		// create a new node
		Node* newNode = new Node;
		newNode->key = newKey;
		newNode->item = newItem;
		newNode->next = NULL;
		// set the last node to point to the new node
		current->next = newNode;

	}
	// increase size by 1 
	size++;
	return true;
}

void SystemHashTable::remove(KeyType key)
{
	int index = hash(key);
	if (items[index] != NULL) {
		for (int pos = index; pos < size; pos++)
			items[index] = items[pos + 1];
		size--;
	}
}

ValueType SystemHashTable::get(KeyType key)
{
	int index = hash(key);
	return ValueType();
}

bool SystemHashTable::isEmpty()
{
	return size == -1;
}

int SystemHashTable::getLength()
{
	return size;
}