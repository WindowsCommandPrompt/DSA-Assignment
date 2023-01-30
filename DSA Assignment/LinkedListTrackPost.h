#pragma once

#include <string> 
#include "Post.h"

//WARNING: THIS LINKED LIST IS ONLY MEANT FOR TRACKING THE POSTS THAT THE USER HAS MADE SO FAR. 
 
class LinkedListTrackPost
{
private:
	struct Node {
		Post post; 
		Node* next; 
	};

    Node* firstPost; 
	int posts = 0; 

public: 
	LinkedListTrackPost(void);																//A constructor to initialize a new linked list
	~LinkedListTrackPost(void);																//A destructor to destroy a linked list
	bool add(const std::string title, const std::string postContentsAsText) noexcept;		//A method to append a new item at the end of the linked list
	bool remove(const std::string title, const std::string postContentsAsText) noexcept;	//A method to remove an item from the back of the linked list 
	int length(void); 
	bool isEmpty(void); 
	Post get(int index); 
	std::string to_string(const LinkedListTrackPost curr); 
	bool equals(const LinkedListTrackPost other); 
	Post searchUsingSequentialSearch(Post item); 
};

