#pragma once

#include <string> 
#include "LinkedListTrackPost.h"

//Data class for the User object.....
class SystemUser
{
private: 

		LinkedListTrackPost posts; 
		string username; 
		string password; 

public: 
	SystemUser(void);				//Create a new user object
	~SystemUser(void);				//Destroy a user; 
	void setUsername(string username); 
	void setPassword(string password); 
	void getPassword(string& var); 
	void getUsername(string& var); 
	void getPosts(LinkedListTrackPost& posts); 
};

