#include "LinkedListTrackComments.h"

LinkedListTrackComments::LinkedListTrackComments(void) {
	this->noOfComments = 0; 
	this->firstComment = nullptr; 
}

LinkedListTrackComments::~LinkedListTrackComments(void) {
	//Destructor can put to last to implement... 
}

bool LinkedListTrackComments::isEmpty(void) {
	return this->noOfComments == 0 && this->firstComment == nullptr; 
}

bool LinkedListTrackComments::add(string content, string username) {
	Comment c = Comment(); 
	c.setContent(content); 
	c.setUsers(username); 
	c.setNumberOfLikes(0); //since if its a new comment, the comment will have 0 likes at the start... 
	c.setNumberOfThumbsUp(0); //Same goes for number of thumbs up.. 
	Node* newComment = new Node; 
	newComment->comment = c; 
	if (this->isEmpty()) {
		//there are no comments, so just attach without traversing. 
		this->firstComment = newComment; 
		newComment->nextComment = nullptr; 
		this->noOfComments++; 
	}
	else {
		Node* firstComment = this->firstComment; 
		while (firstComment->nextComment != nullptr) {
			firstComment = firstComment->nextComment; 
		}
		firstComment->nextComment = newComment; 
		newComment->nextComment = nullptr; 
		this->noOfComments++; 
	}
}