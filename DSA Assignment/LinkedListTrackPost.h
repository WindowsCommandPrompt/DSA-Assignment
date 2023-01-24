#pragma once

#include <string> 
 
class LinkedListTrackPost
{
private: 
	struct DateTimeFormat {
		unsigned int hour; 
		unsigned int minute;
		unsigned int seconds; 
		unsigned int day; 
		unsigned int month; 
		unsigned long year; 
	};

	struct Post {
		std::string title;						//The title of the post that the user has posted in the forum...
		std::string postContentsAsText;			//The contents of the post....
	};

	struct PostNode {
		unsigned long numberOfLikes;			//Number of likes that the post has attained so far....
		unsigned long numberOfThumbsUp;			//Number of thumbs up that the post has attained so far....
		Post post; 
		DateTimeFormat timePosted;				//The date and time where the post was created by the user....
		PostNode* nextPost;						//pointer to the next post.
	};

	PostNode* firstPost; 
	int posts = 0; 

public: 
	LinkedListTrackPost(void);																//A constructor to initialize a new linked list
	~LinkedListTrackPost(void);																//A destructor to destroy a linked list
	bool add(const std::string title, const std::string postContentsAsText) noexcept;		//A method to append a new item at the end of the linked list
	bool remove(const std::string title, const std::string postContentsAsText) noexcept;	//A method to remove an item from the back of the linked list 
	int length(void); 
	bool isEmpty(void); 
	std::string to_string(const LinkedListTrackPost curr); 
	bool equals(const LinkedListTrackPost other); 
	Post searchUsingSequentialSearch(Post item); 
};

