#pragma once

#include <string> 
#include "Comment.h"
#include "topic.h"
#include "LinkedList.h"

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
		this->comment = std::move(otherPost.comment);
	}
	Post(void) {

	}
	Post(string title, string contents, int noOfLikes, int noOfThumbsUp, LinkedList<Comment> comments) {
		this->title = title;
		this->contents = contents;
		this->noOfLikes = noOfLikes;
		this->noOfThumbsUp = noOfThumbsUp;
		this->comment = comments;
	}
	Post(string title, string contents, int noOfLikes, int noOfThumbsUp, LinkedList<Post> post) {
		this->title = title;
		this->contents = contents;
		this->noOfLikes = noOfLikes;
		this->noOfThumbsUp = noOfThumbsUp;
		this->post = post;
	}
	Post(string title, string contents) {			//new Post
		this->title = title;
		this->contents = contents;
		this->noOfLikes = 0;
		this->noOfThumbsUp = 0;
		this->comment = LinkedList<Comment>();
	}

	Post(string topic, LinkedList<Post> post) {			// new Topic
		this->post = post;
		this->topic = topic;
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
	string username;
	string topic;

	// include linked list of comments since users will be able to view comments? 
	LinkedList<Comment> comment;
	LinkedList<Post> post;
};