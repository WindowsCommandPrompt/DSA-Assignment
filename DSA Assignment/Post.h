#pragma once

#include <string> 

using namespace std; 

//This file will be responsible for the tracking of the posts.
class Post {
public: 
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
};