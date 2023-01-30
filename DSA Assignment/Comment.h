#pragma once
#include<string>
using namespace std;
//This file will be responsible for the tracking of the comments (reply).
class Comment
{
private: 
   string contents;
   string users;
   int noOfLikes; 
   int noOfThumbsUp; 
public: 
	int getNumberOfLikes(void); 
	int getNumberOfThumbsUp(void); 
	string getContents(void);
	string getUsers(void);
	void setNumberOfLikes(int a); 
	void setNumberOfThumbsUp(int a); 
	void setContent(string content); 
	void setUsers(string user);
};

