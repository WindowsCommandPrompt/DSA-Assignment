#pragma once
#include<string>

using namespace std; 
//This file will be responsible for the tracking of the comments (reply).
class Comment
{
public: 
    Comment(void) {

   }
   Comment(string contents, string user) {
	   this->contents = contents; 
	   this->users = user; 
	   this->noOfLikes = 0; 
	   this->noOfThumbsUp = 0; 
   }
   ~Comment(void) {

   }
   string contents;
   string users;
   int noOfLikes; 
   int noOfThumbsUp; 
};

