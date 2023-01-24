#pragma once 


#include <string>

typedef int KeyType; 
typedef std::string ValueType; 

//A hash table is just basically an array of linked list....

class SystemHashTable {
private:
	struct Node
	{
		KeyType	 key;   // search key   (stays within the array) 
		ValueType item;	// data item	
		Node* next;	// pointer pointing to next item with same search key
	};

	Node* items[9999999];
	int  size;			// number of items in the Dictionary

public:
	// constructor
	SystemHashTable(void);
	// destructor
	~SystemHashTable(void);
	int hash(KeyType key);
	bool add(KeyType newKey, ValueType newItem);
	void remove(KeyType key);
	ValueType get(KeyType key);
	bool isEmpty();
	int getLength();
	void print();
	int charvalue(char c);
};