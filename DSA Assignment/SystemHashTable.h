#pragma once 

using namespace std;
#include <string>
#include "User.h" 

const int MAX_ITEMS = 999;

//A hash table is just basically an array of linked list....

class SystemHashTable {
private:
	struct Node
	{
		string key;   // search key   (stays within the array) 
		SystemUser value; 
		Node* next;
	};

	Node* items[MAX_ITEMS];

public:
	// constructor
	SystemHashTable(void);					//Initialize a new "database" 
	// destructor
	~SystemHashTable(void);					//destructors.....
	int hash(string value);						//hash function to hash the user's value 
	bool add(string value, string password, LinkedList<Post> posts); 
	bool add(string value, string password, LinkedList<Topic> topics); // to be validated, LinkedList<Topic> topics? is it correct?
	bool add(string value, string password);	//add a new user into the hash table. 
	bool remove(string value);					//delete a user from the hash table
	SystemUser& get(string value);					//get the list of posts via the user... 
	int charvalue(char c);
	void updateFile(void); 
};
