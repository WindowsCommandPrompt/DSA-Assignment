#include "User.h"
#include <string> 

SystemUser::SystemUser(void) {
	this->posts = LinkedListTrackPost();		//Initialize a new post thread.. 
}

SystemUser::~SystemUser(void) {
	//Leave blank for now
}

void SystemUser::setPassword(string password) {
	this->password = password; 
}

void SystemUser::setUsername(string username) {
	this->username = username; 
}

void SystemUser::getPassword(string& password) {
	password = this->password; 
}

void SystemUser::getUsername(string& username) {
	username = this->username; 
}

void SystemUser::getPosts(LinkedListTrackPost& posts) {
	posts = this->posts; 
}