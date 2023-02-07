// ==================================================================
// Student Number : S10228079B, S10222023J
// Student Name :   Ho Min Teck, Li Zhe Yun 
// Module Group :   P03
// ==================================================================


#pragma once
#include<string>

using namespace std;
//This file will be responsible for the tracking of the comments (reply).
class Comment
{
public:
	// default constructor
	Comment(const Comment&) = default;
	Comment& operator=(const Comment&) = default;
	// move constructor
	Comment(Comment&& otherComment) {
		// move the contents and number of likes using move semantics to be used in other files.. 
		this->contents = std::move(otherComment.contents);
		this->noOfLikes = std::move(otherComment.noOfLikes);

	}
	// default constructor
	Comment(void) {

	}
	// create a comment
	Comment(string contents, string user) {
		this->contents = contents;
		this->users = user;
		this->noOfLikes = 0;
		this->noOfThumbsUp = 0;

	}
	// create a comment
	Comment(string contents, string user, int noOfLikes, int noOfThumbsUp) {
		this->contents = contents;
		this->users = user;
		this->noOfLikes = noOfLikes;
		this->noOfThumbsUp = noOfThumbsUp;
	}
	// deconstructor
	~Comment(void) {

	}

	// variables
	string contents;
	string users;
	int noOfLikes;
	int noOfThumbsUp;
};

