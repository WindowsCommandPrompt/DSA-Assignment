#pragma once
#include "Comment.h"
#include <string> 


// WARNING THIS LINKED LIST ONLY TRACKS THE COMMENTS MADE BY USERS TO A POST!!!

class LinkedListTrackComments
{
private: 
	struct Node {
		Comment comment; 
		Node* nextComment; 
	};

	Node* firstComment; 
	int noOfComments; 

public: 
	LinkedListTrackComments(void); 
	~LinkedListTrackComments(void); 
	bool isEmpty(void); 
	bool add(string content, string username); 
	bool update(int noOfLikes); 
};

