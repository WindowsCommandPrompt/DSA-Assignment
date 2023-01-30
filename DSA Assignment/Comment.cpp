#include "Comment.h"
#include<string>

//getters and setters for the Comment data class. 

int Comment::getNumberOfLikes(void) {
	return this->noOfLikes;
}

int Comment::getNumberOfThumbsUp(void) {
	return this->noOfThumbsUp; 
}
string Comment::getContents(void) {
	return this->contents; 
}

string Comment::getUsers(void) {
	return this->users;
}

void Comment::setUsers(string newUsers)
{
	this->users = newUsers;
}

void Comment::setNumberOfLikes(int newNumberOfLikes) {
	this->noOfLikes = newNumberOfLikes; 
}

void Comment::setNumberOfThumbsUp(int newNumberOfThumbsUp) {
	this->noOfThumbsUp = newNumberOfThumbsUp; 
}

void Comment::setContent(string content) {
	this->contents = content; 
}