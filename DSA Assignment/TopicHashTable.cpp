#define RAPIDJSON_HAS_STDSTRING 1

#include "TopicHashTable.h"
#include <string>
#include <fstream> 
#include <iostream>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Comment.h"


TopicHashTable::TopicHashTable(void) {
	std::fill_n(this->items, MAX_ITEMS, nullptr);
}

// Deconstructor
TopicHashTable::~TopicHashTable(void) {

}

int TopicHashTable::charvalue(char c) {
	return (int)c;
}

bool TopicHashTable::contains(string key) {
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
int TopicHashTable::hash(string key) {
	int hashNumber = 0;
	int topicChar;
	int length = key.length();
	if (key.length() < 2) {
		topicChar = charvalue(key[0]);
		return topicChar;
	}
	topicChar = (charvalue(key[0]) * 52 + charvalue(key[1])) % MAX_ITEMS;
	for (int c = 1; c + 1 < length; c++)
	{
		if (c + 1 != key.length()) {
			topicChar = (topicChar * 52 + charvalue(key[c + 1])) % MAX_ITEMS;

		}
	}
	return topicChar % MAX_ITEMS;
}

bool TopicHashTable::add(string newTopic, LinkedList<Post> postUnderTopic) {
	// Compute the index using hash function
	int index = hash(newTopic);
	if (this->items[index] == nullptr) {
		Node* newNode = new Node;
		Post topic(newTopic, postUnderTopic);
		newNode->value = std::move(topic);
		newNode->key = newTopic;
		newNode->next = nullptr;
		this->items[index] = newNode;
	}
	else {
		Node* current = this->items[index];
		while (current->next != nullptr) {
			// iterate to the next node
			current = current->next;
		}
		Node* newNode = new Node;
		newNode->key = newTopic;
		Post topic(newTopic, postUnderTopic);
		newNode->value = std::move(topic);
		newNode->next = nullptr;
	}
	return true;
}

bool TopicHashTable::remove(string key) {
	int index = hash(key);
	if (items[index] != NULL) {
		Node* firstTopic = this->items[index];
		while (firstTopic->next != nullptr && firstTopic->key != key) {
			firstTopic = firstTopic->next;
		}
		if (this->items[index]->next == nullptr) {
			Node* toBeDeleted = this->items[index];
			this->items[index] = nullptr;
			delete toBeDeleted;
		}
		else {
			if (firstTopic->next == nullptr) {
				Node* prevNode = this->items[index];
				while (prevNode->next != firstTopic) {
					prevNode = prevNode->next;
				}
				// prevNode is now one node before firstTopic
				prevNode->next = nullptr;
				delete firstTopic;
			}
			else if (firstTopic == this->items[index]) {
				Node* initialFirstNode = this->items[index];
				this->items[index] = initialFirstNode->next;
				delete initialFirstNode;
			}
		}
		return true;
	}
	else return false;
}

Post& TopicHashTable::get(string key) {
	if (this->items[hash(key)] != nullptr) {
		Node* firstItem = this->items[hash(key)];
		if (firstItem->key == key) return firstItem->value;
		while (firstItem->next != nullptr) {
			firstItem = firstItem->next;
			if (firstItem->key == key) return firstItem->value;
		}
	}
}

void TopicHashTable::updateFile(void) {
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
			rapidjson::Value accountUsername;
			rapidjson::Value listOfTopics;
			accountUsername.SetString(rapidjson::GenericStringRef<char>(firstNode->value.username.c_str()));
			listOfTopics.SetArray();
			LinkedList<Post> posts = firstNode->value.post;
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
					LinkedList<Comment> listOfComments = firstNode->value.post.get(i).comment;
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
					listOfTopics.PushBack(post, newJSONDocument.GetAllocator());
				}
			}
			userInfo.AddMember("Username", accountUsername, newJSONDocument.GetAllocator());
			userInfo.AddMember("Posts", listOfTopics, newJSONDocument.GetAllocator());
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
				
				rapidjson::Value accountUsername;
				accountUsername.SetString(rapidjson::GenericStringRef<char>(firstNode->value.username.c_str()));
				rapidjson::Value listOfPosts;
				listOfTopics.SetArray();
				LinkedList<Post> posts = firstNode->value.post;
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
						LinkedList<Comment> listOfComments = firstNode->value.post.get(i).comment;
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
				userInfo.AddMember("Topic", listOfTopics, newJSONDocument.GetAllocator());
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
	ofstream datFile("topic.dat");
	datFile << jsonString;
	datFile.close();
}
		
	






