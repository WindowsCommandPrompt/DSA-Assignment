#include "topic.h"
#include<string>

// getter and setter for topic data class

int Topic::getTopicTitle(void) {
	return this->TopicTitle;
}

string Topic::getContents(void)
{
	return this->contents;
}

int Topic::getNumberOfLikes(void) {
	return this->noOfLikes;
}

int Topic::getNumberOfPosts(void) {
	return this->noOfPosts; 
}

void Topic::setNumberOfPosts(int newPost)
{
	this->noOfPosts = newPost;
}

void Topic::setTopicTitle(string newTopicTitle)
{
	this->TopicTitle = newTopicTile;
}

void Topic::setNumberOfLikes(int newNumberOfLikes) {
	this->noOfLikes = newNumberOfLikes; 
}

void Topic::setContent(string content) {
	this->contents = content; 
}