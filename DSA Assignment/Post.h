#pragma once

#include <string> 

using namespace std; 

//This file will be responsible for the tracking of the posts.
class Post {
private: 
	
	int noOfLikes; 
	int noOfThumbsUp; 
	string title; 
	string contents; 

public: 
	int getNumberOfLikes(void); 
	int getNumberOfThumbsUp(void); 
	string getTitle(void); 
	string getContents(void); 
	void setNumberOfLikes(int a); 
	void setNumberOfThumbsUp(int a); 
	void setTitle(string title); 
	void setContent(string content); 
};