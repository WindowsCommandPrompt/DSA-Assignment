#pragma once 

using namespace std;
#include <string>
#include "LinkedListTrackPost.h"
#include "User.h" 

typedef LinkedListTrackPost Posts; 
const int MAX_ITEMS = 9999999;

//A hash table is just basically an array of linked list....

class SystemHashTable {
private:
	struct Node
	{
		string  key;   // search key   (stays within the array) 
		SystemUser user; 
		Node* next;	// pointer pointing to next item with same search key
	};

	Node* items[MAX_ITEMS];

public:
	// constructor
	SystemHashTable(void);					//Initialize a new "database" 
	// destructor
	~SystemHashTable(void);					//destructors.....
	int hash(string username);						//hash function to hash the user's username 
	bool add(string username, string password);	//add a new user into the hash table. 
	bool remove(string username);					//delete a user from the hash table
	SystemUser get(string username);					//get the list of posts via the user... 
	string to_string(void);
	int charvalue(char c);
};