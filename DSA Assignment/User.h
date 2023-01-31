#pragma once

#include <string> 
#include "LinkedList.h"
#include "Post.h"

using namespace std; 

//Data class for the User object.....
class SystemUser
{
public:
	SystemUser(void) {

	}
	SystemUser(string username, string password) {
		this->posts = LinkedList<Post>(); 
		this->username = username; 
		this->password = password; 
	}				//Create a new user object
	SystemUser(string username, string password, LinkedList<Post> posts) {
		this->posts = posts; 
		this->username = username; 
		this->password = password; 
	}
	~SystemUser(void) {

	}											
	LinkedList<Post> posts;
	string username;
	string password;
};

