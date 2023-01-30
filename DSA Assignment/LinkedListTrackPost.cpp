#include "LinkedListTrackPost.h"
#include <chrono>


LinkedListTrackPost::LinkedListTrackPost(void){
	this->firstPost = nullptr; 
	this->posts = 0; 
}

LinkedListTrackPost::~LinkedListTrackPost(void) {
	while (!this->isEmpty()) {

	}
}

bool LinkedListTrackPost::isEmpty(void) {
	return this->firstPost == nullptr && this->posts == 0; 
}

int LinkedListTrackPost::length(void) {
	return this->posts; 
}

Post LinkedListTrackPost::get(int index) {
	if (index == 0) {
		return this->firstPost->post; 
	}
	else {
		Node* firstPost = this->firstPost; 
		for (int i = 0; i <= index; i++) {
			firstPost = firstPost->next; 
		}
		return firstPost->post; 
	}
}

bool LinkedListTrackPost::add(const std::string postTitle, const std::string postContentsAsString) noexcept {
	Post newPost = Post(); 
	newPost.setContent(postContentsAsString);
	newPost.setTitle(postTitle); 
	newPost.setNumberOfLikes(0);					//initialize the number of posts to 0....
	newPost.setNumberOfThumbsUp(0);					//initialize the number of thumbs up of the post to 0.....
	//Create a new node and attach it into the linked list.
	Node* newPostNode = new Node; 
	newPostNode->post = newPost; 
	if (this->isEmpty()) {
		this->firstPost = newPostNode; //if there are no posts within the 
		newPostNode->next = nullptr; 
	}
	else {
		Node* firstPostNode = this->firstPost;
		while (firstPostNode->next != nullptr) {
			firstPostNode = firstPostNode->next; 
		}
		firstPostNode->next = newPostNode; 
		newPostNode->next = nullptr; 
	} 
	return true; 
}
