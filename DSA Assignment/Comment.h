#pragma once
#include<string>

using namespace std; 
//This file will be responsible for the tracking of the comments (reply).
class Comment
{
public: 
	Comment(const Comment&) = default;
	Comment& operator=(const Comment&) = default;
	Comment(Comment&& otherComment) {
		
		this->contents = std::move(otherComment.contents);
		this->noOfLikes = std::move(otherComment.noOfLikes);

	}
    Comment(void) {

   }
   Comment(string contents, string user) {
	   this->contents = contents; 
	   this->users = user; 
	   this->noOfLikes = 0; 
	   this->noOfThumbsUp = 0; 
	   
   }
   Comment(string contents, string user, int noOfLikes, int noOfThumbsUp) {
	   this->contents = contents; 
	   this->users = user; 
	   this->noOfLikes = noOfLikes; 
	   this->noOfThumbsUp = noOfThumbsUp; 
   }
   ~Comment(void) {

   }
   string contents;
   string users;
   int noOfLikes; 
   int noOfThumbsUp; 
};

