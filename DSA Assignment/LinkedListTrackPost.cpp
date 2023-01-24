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

bool LinkedListTrackPost::add(const std::string postTitle, const std::string postContentsAsString) noexcept {
	Post newPost = Post(); 
	newPost.title = postTitle; 
	newPost.postContentsAsText = postContentsAsString; 
	DateTimeFormat dateOfPosting = DateTimeFormat(); 

	return true; 
}
