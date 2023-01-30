// Completed by Ho Min Teck and Li Zhe Yun 
#include "SystemHashTable.h"
#include <string>

SystemHashTable::SystemHashTable(void) {
	//array but using linked list from LinkedListTrackPost.
	std::fill_n(this->items, MAX_ITEMS, nullptr); 
}

// Deconstructor
SystemHashTable::~SystemHashTable(void) 
{

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

bool SystemHashTable::add(string newUser, string password)
{
	// create a new node 
	Node* newNode = new Node;
	// Compute the index using hash function 
	int index = hash(newUser);
	if (this->items[index] == nullptr){					//Check if there is any users at an index position.... 
		Node* newNode = new Node;  						// Create a new node
		SystemUser user = SystemUser(); 
		user.setPassword(password); 
		user.setUsername(newUser); 
		newNode->user = user;					// Set list at index to point to new node
		newNode->key = newUser;
		newNode->next = nullptr;
	}
	else {												//if there is a user at an index position, simply attach the user to the end of the linked list .....
		Node* current = items[index];					//point to the first item in the array..
		while (current->next != nullptr) {					// while not at last node  
			// iterate to the next node
			current = current->next;
		}
		//we are now at the end of the linked list....(technically)
		// create a new node
		Node* newNode = new Node;
		newNode->key = newUser;
		SystemUser user = SystemUser(); 
		user.setPassword(password); 
		user.setUsername(newUser); 
		newNode->user = user;
		newNode->next = nullptr;
	}
	return true;
}

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

SystemUser SystemHashTable::get(string key)
{
	return this->items[hash(key)]->user; 
}

string SystemHashTable::to_string(void) {
	string output = "{";
	//null, true, false
	/* 
	* rough structure of our json document. 
	  { 
	     "hashValue": [
			 { 
				"user": "username", 
				"posts": [ 
					{ 
						"noOfLikes": 12, 
						"noOfThumbsUp": 12, 
						"title": "some kind of title", 
						"content": "post contents as a text....", 
						"topic": "what topic it belongs to.
					}, 
					{ 
					   . . . . . 
					} 
				]
			 }, 
			 { 
				"user": "anotherUsername", 
				"posts": [ 

				]
			 } 
		 ], 
		 "hashValue": null
	  }
	*/
	for (int i = 0; i < MAX_ITEMS; i++) {
		if (this->items[i] != nullptr) {
			output += ("\"" + std::to_string(i) + "\":" + (this->items[i] == nullptr ? "null" : ([this, i] {
				string resultArrayAsString = "["; 
				Node* firstNode = this->items[i]; //start from the first node within the linked list
				//user property settled....
				resultArrayAsString += "{"; 
				resultArrayAsString += ("\"user: \"" + firstNode->key + "\""); 
				resultArrayAsString += ",";
				//posts property settled. 
				string linkedListPostsAsString = string("[");
				if (firstNode->item.isEmpty()) return "null";
				else {
					LinkedListTrackPost allPosts = firstNode->item;
					for (int i = 0; ; i++) {
						try {
							Post post = allPosts.get(i);
							linkedListPostsAsString += "{";
							linkedListPostsAsString += ("\"noOfLikes\"" + std::to_string(post.getNumberOfLikes()) + ",");
							linkedListPostsAsString += ("\"noOfThumbsUp\"" + std::to_string(post.getNumberOfThumbsUp()) + ",");
							linkedListPostsAsString += ("\"title\"" + post.getTitle() + ",");
							linkedListPostsAsString += ("\"content\"" + post.getContents());
							linkedListPostsAsString += "}";
						}
						catch (exception e) {
							break;
						}
						linkedListPostsAsString += ",";
					}
				}
				linkedListPostsAsString += "]}";
				resultArrayAsString += ("\"posts: \"" + linkedListPostsAsString);
				//Check for other users that are under the same index... 
				while (firstNode->next != nullptr) {
					resultArrayAsString += ",{";			//Append a comma if we are continuing on with the while loop.... 
					firstNode = firstNode->next; 
					resultArrayAsString += ("\"user: \"" + firstNode->key + "\"");
					resultArrayAsString += ","; 
					string linkedListPostsAsString = string("[");
					if (firstNode->item.isEmpty()) return "null";
					else {
						LinkedListTrackPost allPosts = firstNode->item;
						for (int i = 0; ; i++) {
							try {
								Post post = allPosts.get(i);
								linkedListPostsAsString += "{";
								linkedListPostsAsString += ("\"noOfLikes\"" + std::to_string(post.getNumberOfLikes()) + ",");
								linkedListPostsAsString += ("\"noOfThumbsUp\"" + std::to_string(post.getNumberOfThumbsUp()) + ",");
								linkedListPostsAsString += ("\"title\"" + post.getTitle() + ",");
								linkedListPostsAsString += ("\"content\"" + post.getContents());
								linkedListPostsAsString += "}";
							}
							catch (exception e) {
								break;
							}
							linkedListPostsAsString += ",";
						}
					}
					linkedListPostsAsString += "]}";
					resultArrayAsString += ("\"posts: \"" + linkedListPostsAsString);
				}
				resultArrayAsString += "]"; //end of appending post items into the string.... (for hashValue array)
				return resultArrayAsString; 
			})()));
		}
	}
}