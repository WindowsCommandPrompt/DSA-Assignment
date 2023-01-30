#include "Post.h" 
#include <string> 

//getters and setters for the Post data class. 

int Post::getNumberOfLikes(void) {
	return this->noOfLikes;
}

int Post::getNumberOfThumbsUp(void) {
	return this->noOfThumbsUp; 
}

string Post::getTitle(void) {
	return this->title; 
}

string Post::getContents(void) {
	return this->contents; 
}

void Post::setNumberOfLikes(int newNumberOfLikes) {
	this->noOfLikes = newNumberOfLikes; 
}

void Post::setContent(string content) {
	this->contents = content; 
}

void Post::setTitle(string title) {
	this->title = title; 
}

void Post::setNumberOfThumbsUp(int newNumberOfThumbsUp) {
	this->noOfThumbsUp = newNumberOfThumbsUp; 
}
