#pragma once

#include <string> 
#include "Comment.h"

using namespace std; 

//This file will be responsible for the tracking of the posts.
class Post {
public: 
	Post(const Post&) = default; 
	Post& operator=(const Post&) = default; 
	Post(Post&& otherPost) {
		this->title = std::move(otherPost.title);
		this->contents = std::move(otherPost.contents);
		this->noOfLikes = std::move(otherPost.noOfLikes);
		this->noOfThumbsUp = std::move(otherPost.noOfThumbsUp); 
		
	}
	Post(void) {
		 
	}
	Post(string title, string contents, int noOfLikes, int noOfThumbsUp) {
		this->title = title; 
		this->contents = contents; 
		this->noOfLikes = noOfLikes; 
		this->noOfThumbsUp = noOfThumbsUp; 
	}
	Post(string title, string contents) {
		this->title = title; 
		this->contents = contents; 
		this->noOfLikes = 0; 
		this->noOfThumbsUp = 0; 
	}
	~Post(void) {

	}
	int noOfLikes; 
	int noOfThumbsUp; 
	string title; 
	string contents; 

	// include linked list of comments since users will be able to view comments? 
	LinkedList<Comment> comment; 
};