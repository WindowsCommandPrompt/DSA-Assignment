// ==================================================================
// Student Number : S10228079B, S10222023J
// Student Name :   Ho Min Teck, Li Zhe Yun 
// Module Group :   P03
// ==================================================================

#define RAPIDJSON_HAS_STDSTRING 1

#include "SystemHashTable.h"
#include <string>
#include <fstream> 
#include <iostream>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


SystemHashTable::SystemHashTable(void) {
	//array but using linked list from LinkedList.h.
	std::fill_n(this->items, MAX_ITEMS, nullptr); 
}

// Deconstructor
SystemHashTable::~SystemHashTable(void) 
{

}

// get the char value of the hash function
int SystemHashTable::charvalue(char c) {
	return (int)c; 
}

// check if the key in the items index. used for checking the hashtable contains a certain key i.e. username
bool SystemHashTable::contains(string key) {
	int index = this->hash(key); 
	if (this->items[index] == nullptr) return false; 
	else {
		Node* firstNode = this->items[index]; 
		if (firstNode->key == key) return true; 
		else {
			while (firstNode->next != nullptr) {
				firstNode = firstNode->next; 
				if (firstNode->key == key) return true; 
			}
		}
	}
	return false; 
}

// hash function
int SystemHashTable::hash(string key) 
{
	int hashNo = 0;
	int characters;
	int len = key.length();
	if (key.length() < 2) {
		characters = charvalue(key[0]);
		return characters;
	}
	characters = (charvalue(key[0]) * 52 + charvalue(key[1])) % MAX_ITEMS;
	for (int c = 1; c + 1 < len; c++) 
	{
		if (c + 1 != key.length())
		{
			characters = (characters * 52 + charvalue(key[c + 1])) % MAX_ITEMS;
		}
	}
	return 	characters % MAX_ITEMS;
}

// add the new users into the hash table
bool SystemHashTable::add(string newUser, string password, LinkedList<Post> posts) {
	// Compute the index using hash function 
	int index = hash(newUser);
	if (this->items[index] == nullptr) {					//Check if there is any users at an index position.... 
		Node* newNode = new Node;  						// Create a new node
		SystemUser user(newUser, password, posts);
		newNode->value = std::move(user);					// Set list at index to point to new node
		newNode->key = newUser;
		newNode->next = nullptr; 
		this->items[index] = newNode;
	}
	else {												//if there is a user at an index position, simply attach the user to the end of the linked list .....
		Node* current = this->items[index];					//point to the first item in the array..
		while (current->next != nullptr) {					// while not at last node  
			// iterate to the next node
			current = current->next;
		}
		//we are now at the end of the linked list....(technically)
		// create a new node
		Node* newNode = new Node;
		newNode->key = newUser;
		SystemUser user(newUser, password, posts);
		newNode->value = std::move(user);
		newNode->next = nullptr;
	}
	return true;
}
// add the new users into the hash table
bool SystemHashTable::add(string newUser, string password)
{
	// Compute the index using hash function 
	int index = hash(newUser);
	if (this->items[index] == nullptr){					//Check if there is any users at an index position.... 
		Node* newNode = new Node;  						// Create a new node
		SystemUser user = SystemUser(newUser, password); 
		newNode->value = user;					// Set list at index to point to new node
		newNode->key = newUser;
		newNode->next = nullptr;
		this->items[index] = newNode; 
	}
	else {												//if there is a user at an index position, simply attach the user to the end of the linked list .....
		Node* current = this->items[index];					//point to the first item in the array..
		while (current->next != nullptr) {					// while not at last node  
			// iterate to the next node
			current = current->next;
		}
		//we are now at the end of the linked list....(technically)
		// create a new node
		Node* newNode = new Node;
		newNode->key = newUser;
		SystemUser user = SystemUser(newUser, password); 
		newNode->value = user;
		newNode->next = nullptr;
	}
	return true;
}
// remove the new topic into the hash table
bool SystemHashTable::remove(string key)
{
	int index = hash(key);							//hash the key to get the index position within the array.... 
	if (items[index] != NULL) {						//Try to access that index position using the given hash value.... 
		Node* firstUser = this->items[index];
		while (firstUser->next != nullptr && firstUser->key != key) {
			firstUser = firstUser->next;			//Traversing through the linked list.... 
		}
		if (this->items[index]->next == nullptr) {
			//only one item in the array
			Node* toBeDeleted = this->items[index];
			this->items[index] = nullptr;
			delete toBeDeleted;
		}
		else {
			//more than one item in the linkedlist. 
			//we should technically be at the correct node.
			if (firstUser->next == nullptr) {
				//end of the linkedlist!
				Node* prevNode = this->items[index];
				while (prevNode->next != firstUser) {
					prevNode = prevNode->next;
				}
				//prevNode is now one node before firstUser. 
				prevNode->next = nullptr;
				delete firstUser;
			}
			else if (firstUser == this->items[index]) {
				//if this is the firstnode, but not the one and only node
				Node* initialFirstNode = this->items[index];
				this->items[index] = initialFirstNode->next;
				delete initialFirstNode;
			}
		}
		return true;
	}
	else return false; 
}
// get the users from the hash table
SystemUser& SystemHashTable::get(string key)
{
	if (this->items[hash(key)] != nullptr) {
		Node* firstItem = this->items[hash(key)]; 
		if (firstItem->key == key) return firstItem->value; 
		while (firstItem->next != nullptr) {
			firstItem = firstItem->next; 
			if (firstItem->key == key) return firstItem->value; 
		}
	}
}

// update the users into the file
void SystemHashTable::updateFile(void) { 
	rapidjson::Document newJSONDocument;
	auto& allocator = newJSONDocument.GetAllocator(); 
	newJSONDocument.SetArray();                             //Create an array because we are storing a list of users.
	for (int i = 0; i < MAX_ITEMS; i++) {
		//start looping through the entire array.... 
		if (this->items[i] != nullptr) { //if its not a null linked list
			Node* firstNode = this->items[i];
			rapidjson::Value user;
			user.SetObject();
			rapidjson::Value username;
			username.SetString(rapidjson::GenericStringRef<char>(firstNode->key.c_str()));
			rapidjson::Value userInfo;
			userInfo.SetObject();
			rapidjson::Value password;
			rapidjson::Value accountUsername;
			rapidjson::Value listOfPosts;
			password.SetString(rapidjson::GenericStringRef<char>(firstNode->value.password.c_str()));
			accountUsername.SetString(rapidjson::GenericStringRef<char>(firstNode->value.username.c_str()));
			listOfPosts.SetArray();
			LinkedList<Post> posts = firstNode->value.posts;
			if (!posts.isEmpty()) {
				for (int i = 0; i < posts.length(); i++) {
					rapidjson::Value post;
					post.SetObject();
					rapidjson::Value numberOfLikes;
					rapidjson::Value numberOfThumbsUp;
					rapidjson::Value title;
					rapidjson::Value contents;
					numberOfLikes.SetInt64(posts.get(i).noOfLikes);
					numberOfThumbsUp.SetInt64(posts.get(i).noOfThumbsUp);
					title.SetString(posts.get(i).title.c_str(), allocator);
					contents.SetString(posts.get(i).contents.c_str(), allocator);
					post.AddMember("NumberOfLikes", numberOfLikes, newJSONDocument.GetAllocator());
					post.AddMember("NumberOfThumbsUp", numberOfThumbsUp, newJSONDocument.GetAllocator());
					post.AddMember("Title", title, newJSONDocument.GetAllocator());
					post.AddMember("Contents", contents, newJSONDocument.GetAllocator());
					//Add a new property that allows users to view their comments
					rapidjson::Value commentsList;
					commentsList.SetArray();		//Declare the value type as an array
					LinkedList<Comment> listOfComments = firstNode->value.posts.get(i).comment; 
					if (!listOfComments.isEmpty()) {
						for (int j = 0; j < listOfComments.length(); j++) {		//Loop through the entire linked list of comments....
							rapidjson::Value aSingleComment;
							aSingleComment.SetObject();
							rapidjson::Value commenterUsername;
							rapidjson::Value postContent;
							rapidjson::Value noOfLikes;
							rapidjson::Value noOfThumbsUp;
							commenterUsername.SetString(listOfComments.get(j).users, allocator);
							postContent.SetString(listOfComments.get(j).contents, allocator);
							noOfLikes.SetInt64(listOfComments.get(j).noOfLikes);
							noOfThumbsUp.SetInt64(listOfComments.get(j).noOfThumbsUp);
							aSingleComment.AddMember("Username", commenterUsername, newJSONDocument.GetAllocator());
							aSingleComment.AddMember("Content", postContent, newJSONDocument.GetAllocator());
							aSingleComment.AddMember("NumberOfLikes", noOfLikes, newJSONDocument.GetAllocator());
							aSingleComment.AddMember("NumberOfThumbsUp", noOfThumbsUp, newJSONDocument.GetAllocator());
							commentsList.PushBack(aSingleComment, newJSONDocument.GetAllocator());
						}
					}
					post.AddMember("Comments", commentsList, newJSONDocument.GetAllocator());
					listOfPosts.PushBack(post, newJSONDocument.GetAllocator());
				}
			}
			userInfo.AddMember("Username", accountUsername, newJSONDocument.GetAllocator());
			userInfo.AddMember("Password", password, newJSONDocument.GetAllocator());
			userInfo.AddMember("Posts", listOfPosts, newJSONDocument.GetAllocator());
			user.AddMember("Username", username, newJSONDocument.GetAllocator());
			user.AddMember("User", userInfo, newJSONDocument.GetAllocator());
			newJSONDocument.PushBack(user, newJSONDocument.GetAllocator());
			//repeat for all other items in the linked list? 
			while (firstNode->next != nullptr) {
				firstNode = firstNode->next;
				rapidjson::Value user;
				user.SetObject();
				rapidjson::Value username;
				username.SetString(rapidjson::GenericStringRef<char>(firstNode->key.c_str()));
				rapidjson::Value userInfo;
				userInfo.SetObject();
				rapidjson::Value password;
				password.SetString(rapidjson::GenericStringRef<char>(firstNode->value.password.c_str()));
				rapidjson::Value accountUsername;
				accountUsername.SetString(rapidjson::GenericStringRef<char>(firstNode->value.username.c_str()));
				rapidjson::Value listOfPosts;
				listOfPosts.SetArray();
				LinkedList<Post> posts = firstNode->value.posts;
				if (!posts.isEmpty()) {
					for (int i = 0; i < posts.length(); i++) {
						rapidjson::Value post;
						post.SetObject();
						rapidjson::Value numberOfLikes;
						rapidjson::Value numberOfThumbsUp;
						rapidjson::Value title;
						rapidjson::Value contents;
						numberOfLikes.SetInt64(posts.get(i).noOfLikes);
						numberOfThumbsUp.SetInt64(posts.get(i).noOfThumbsUp);
						title.SetString(posts.get(i).title.c_str(), allocator);
						contents.SetString(posts.get(i).contents.c_str(), allocator);
						post.AddMember("NumberOfLikes", numberOfLikes, newJSONDocument.GetAllocator());
						post.AddMember("NumberOfThumbsUp", numberOfThumbsUp, newJSONDocument.GetAllocator());
						post.AddMember("Title", title, newJSONDocument.GetAllocator());
						post.AddMember("Contents", contents, newJSONDocument.GetAllocator());
						//Add a new property that allows users to view their comments
						rapidjson::Value commentsList; 
						commentsList.SetArray();		//Declare the value type as an array
						LinkedList<Comment> listOfComments = firstNode->value.posts.get(i).comment; 
						if (!listOfComments.isEmpty()) {
							for (int j = 0; j < listOfComments.length(); j++) {		//Loop through the entire linked list of comments....
								rapidjson::Value aSingleComment;
								aSingleComment.SetObject();
								rapidjson::Value commenterUsername;
								rapidjson::Value postContent;
								rapidjson::Value noOfLikes;
								rapidjson::Value noOfThumbsUp;
								commenterUsername.SetString(listOfComments.get(j).users, allocator);
								postContent.SetString(listOfComments.get(j).contents, allocator);
								noOfLikes.SetInt64(listOfComments.get(j).noOfLikes);
								noOfThumbsUp.SetInt64(listOfComments.get(j).noOfThumbsUp);
								aSingleComment.AddMember("Username", commenterUsername, newJSONDocument.GetAllocator());
								aSingleComment.AddMember("Content", postContent, newJSONDocument.GetAllocator());
								aSingleComment.AddMember("NumberOfLikes", noOfLikes, newJSONDocument.GetAllocator());
								aSingleComment.AddMember("NumberOfThumbsUp", noOfThumbsUp, newJSONDocument.GetAllocator());
								commentsList.PushBack(aSingleComment, newJSONDocument.GetAllocator());
							}
						} 
						post.AddMember("Comments", commentsList, newJSONDocument.GetAllocator()); 
						listOfPosts.PushBack(post, newJSONDocument.GetAllocator());
					}
				}
				userInfo.AddMember("Username", accountUsername, newJSONDocument.GetAllocator());
				userInfo.AddMember("Password", password, newJSONDocument.GetAllocator());
				userInfo.AddMember("Posts", listOfPosts, newJSONDocument.GetAllocator());
				user.AddMember("Username", username, newJSONDocument.GetAllocator());
				user.AddMember("User", userInfo, newJSONDocument.GetAllocator());
				newJSONDocument.PushBack(user, newJSONDocument.GetAllocator());
			}
		}
	} 
	//start saving the json document into the text file. 
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	newJSONDocument.Accept(writer);
	string jsonString = buffer.GetString();
	ofstream datFile("post.dat");
	datFile << jsonString;
	datFile.close();
}