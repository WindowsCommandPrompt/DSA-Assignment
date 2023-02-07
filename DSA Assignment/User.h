// ==================================================================
// Student Number : S10228079B, S10222023J
// Student Name :   Ho Min Teck, Li Zhe Yun 
// Module Group :   P03
// ==================================================================

#pragma once

#include <string> 
#include "LinkedList.h"
#include "Post.h"

using namespace std; 

//Data class for the User object.....
class SystemUser
{
public:
	// default constructors
	SystemUser(const SystemUser&) = default;
	SystemUser& operator=(const SystemUser&) = default;
	SystemUser(void) {

	}
	// create new user
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
	//Create a new user object and topic 
	SystemUser(string username, string password, LinkedList<Topic> topic) {
		this->topics = topic;
		this->username = username;
		this->password = password;
	}
	// move the user object using && operator
	SystemUser(SystemUser&& user)
	{
		this->posts = std::move(user.posts);
		this->topics = std::move(user.topics);
		this->username = std::move(user.username);
		this->password = std::move(user.password);
	}
	// deconstructor
	~SystemUser(void) {

	}	
	// variables
	LinkedList<Post> posts;
	LinkedList<Topic> topics;
	LinkedList<Comment> comments;
	string username;
	string password;
};

