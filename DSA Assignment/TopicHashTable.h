// ==================================================================
// Student Number : S10228079B, S10222023J
// Student Name :   Ho Min Teck, Li Zhe Yun 
// Module Group :   P03
// ==================================================================

#pragma once
using namespace std;
#include <string>
#include "topic.h"
#include "Post.h"
#include "TopicHashTable.h"
#include "LinkedList.h"

const int MAX_ITEMS = 999;

// A hash table implementation of topic

class TopicHashTable {
private:
	struct Node
	{
		string key; // search key 
		Post value;
		Node* next;
	};

	Node* items[MAX_ITEMS];

public:
	// constructor
	TopicHashTable(void);   // Initialize a new "database"
	// destructor 
	~TopicHashTable(void); // destructors...
	int hash(string value);				// hash function to hash the user's value
	bool add(string, LinkedList<Post>);
	bool remove(string value);
	bool contains(string value);
	Post& get(string value); // get the list of posts related to the topic via the post.;
	int charvalue(char c);
	void updateFile(void);

};