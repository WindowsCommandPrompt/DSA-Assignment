// ==================================================================
// Student Number : S10228079B, S10222023J
// Student Name :   Ho Min Teck, Li Zhe Yun 
// Module Group :   P03
// ==================================================================


// DSA Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define RAPIDJSON_HAS_STDSTRING 1

// include header file and json library file.
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <Windows.h>
#include <format>
#include "Topic.h"
#include "Comment.h"
#include "User.h"
#include "Post.h"
#include "LinkedList.h" 
#include "SystemHashTable.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>


using namespace std;
using namespace rapidjson;

// variable initialization
static string user = "";
// variable for adding thumbs up, likes, removing thumbs up, likes.
static bool ifAfterAdd = false;
static bool ifUpdateNumberOfLikes = false;
static bool ifUpdateNumberOfLikesInv = false;
static bool quitToListOfPostsCreatedBySelf = false;
static bool justAddedLike = false;
static bool justRemovedLike = false;
static bool justAddedThumbsUp = false;
static bool justRemovedThumbsUp = false;
static bool ifUpdateNumberOfThumbsUp = false;
static bool ifUpdateNumberOfThumbsUpInv = false;
static int likeAppliesToPostNumber = 0;

void login(void) {
	//Print out some kind of menu like thing
	std::cout << "===========================================================" << endl;
	std::cout << "#         WELCOME TO THE PRO EDUCATIONIST FORUM!!!        #" << endl;
	std::cout << "#                                                         #" << endl;
	std::cout << "# [0] Quit Program                                        #" << endl;
	std::cout << "# [1] Login into an account                               #" << endl;
	std::cout << "# [2] Temporarily disable account                         #" << endl;
	std::cout << "# [3] Create a new account                                #" << endl;
	std::cout << "# [4] Forgot my account credentials                       #" << endl;
	std::cout << "# [5] Privacy policy                                      #" << endl;
	std::cout << "===========================================================" << endl;
}

//main user interface once the user are logged in
void mainMenu(void) {
	std::cout << "Hello, " << user << endl;
	std::cout << "===========================================================" << endl;
	std::cout << "# [0] Logout                                              #" << endl;
	std::cout << "# [1] Create a new topic                                  #" << endl;
	std::cout << "# [2] Create a new post                                   #" << endl;
	std::cout << "# [3] Browse my posts                                     #" << endl;
	std::cout << "# [4] Explore other people's posts                        #" << endl;
	std::cout << "# [5] Explore all topics                                  #" << endl;
	std::cout << "# [6] Search for topics                                   #" << endl;
	std::cout << "# [7] Search for posts                                    #" << endl;
	std::cout << "# [8] Search for users                                    #" << endl;
	std::cout << "===========================================================" << endl;
}

// view post menu - for opening a post 
void viewPostMenu(void) {
	std::cout << "===========================================================" << endl;
	std::cout << "# [0] Exit to the main menu                               #" << endl;
	std::cout << "# [1] Exit to posts list                                  #" << endl;
	std::cout << "# [2] Open a post                                         #" << endl;
	std::cout << "===========================================================" << endl;
}

// menu to allow user to reply, edit, delete post. 
void expandComments(void) {
	std::cout << "===========================================================" << endl;
	std::cout << "# [0] Exit to post                                        #" << endl;
	std::cout << "# [1] Like a post                                         #" << endl;
	std::cout << "# [2] Disike a post                                       #" << endl;
	std::cout << "# [3] Add a thumbs up                                     #" << endl;
	std::cout << "# [4] Remove a thumbs up                                  #" << endl;
	std::cout << "# [5] Expand comments                                     #" << endl;
	std::cout << "# [6] Reply to post                                       #" << endl;
	std::cout << "# [7] Edit Post                                           #" << endl;
	std::cout << "# [8] Delete Post                                         #" << endl;
	std::cout << "===========================================================" << endl;
}

// method used to extract user name from users so that users will able to see who make the posts and comments.
LinkedList<string> extractUsername(rapidjson::Document& rawData) {
	LinkedList<string> usersOfThePlatform = LinkedList<string>();
	if (rawData.IsArray()) {
		for (SizeType i = 0; i < rawData.Size(); i++) {
			usersOfThePlatform.add(rawData[i]["Username"].GetString());
		}
	}
	return usersOfThePlatform;
}
// comparsion made.
static int comparisons = 0;

// search method using sequential search iterative. This searches for posts and topics. 
int search(int post[], int NoOfPost, int target) {
	// loop to check whether the post matches the target.
	for (int i = 0; i < NoOfPost; i++) {
		for (int i = 0; i < NoOfPost; i++) {
			if (post[i] == target) return i;
		}
		return -1; // not found
		
		if (post[i] != target) {
			comparisons++;  // increase the comparsion each time an comparison is made
		}
	}

	return -1; // not found
}

// search for users using sequential search iterative. This searches for users.
int searchforUsers(string users[], int NoOfUsers, string target) {

	for (int i = 0; i < NoOfUsers; i++) {
		if (users[i] == target) // found 
		{
			return i;
		}
		else if (users[i] > target)
		{
			// not found  
			return -1;
		}


		if (users[i] != target) {
			comparisons++;  // increase the comparsion each time an comparison is made
		}
	}

	return -1; // not found
}

// method to convert json document into a hash table.
SystemHashTable convertToHashTable(rapidjson::Document& rawData) {
	SystemHashTable out = SystemHashTable();
	if (rawData.IsArray()) {
		for (SizeType i = 0; i < rawData.Size(); i++) {
			out.add(
				rawData[i]["User"]["Username"].GetString(),
				rawData[i]["User"]["Password"].GetString(),
				LinkedList<Post>()
			);
			if (rawData[i]["User"]["Posts"].IsArray()) {
				for (SizeType j = 0; j < rawData[i]["User"]["Posts"].Size(); j++) {
					out.get(rawData[i]["Username"].GetString()).posts.add(
						Post(
							rawData[i]["User"]["Posts"][j]["Title"].GetString(),
							rawData[i]["User"]["Posts"][j]["Contents"].GetString(),
							rawData[i]["User"]["Posts"][j]["NumberOfLikes"].GetInt64(),
							rawData[i]["User"]["Posts"][j]["NumberOfThumbsUp"].GetInt64(),
							LinkedList<Comment>()
						)
					);
					if (rawData[i]["User"]["Posts"][j]["Comments"].IsArray()) {
						for (SizeType k = 0; k < rawData[i]["User"]["Posts"][j]["Comments"].Size(); k++) {
							;
							out.get(rawData[i]["Username"].GetString()).posts.get(j).comment.add(
								Comment(
									rawData[i]["User"]["Posts"][j]["Comments"][k]["Content"].GetString(),
									rawData[i]["User"]["Posts"][j]["Comments"][k]["Username"].GetString(),
									rawData[i]["User"]["Posts"][j]["Comments"][k]["NumberOfLikes"].GetInt64(),
									rawData[i]["User"]["Posts"][j]["Comments"][k]["NumberOfThumbsUp"].GetInt64()

								)
							);
						}
					}
					
				}
			}
		}
	}
	return out;
}


void main(void)
{
	
	for (; ; ) {                    //Initiate an infinite loop. 
		login();                    //Display the main menu to the user. 
		std::cout << "Your choice: ";    //Prompting the user for his / her choice
		string var = "";            //string variable to capture the user's choice
		getline(cin, var);          //Accepts spacings between words....
		try {
			int a = stoi(var);      //try converting the string to an integer. 
			if (a == 0) {           //quit the program if the user selects 0. 
				return;
			}
			else if (a == 1) {
				//Login to an account
				std::system("cls");
				Sleep(500);
				std::cout << "Username: ";
				string username = ""; string password = "";
				getline(cin, username);
				std::cout << "Password: ";
				getline(cin, password);
			// to retrieve data again from post.dat
			RETRIEVE_DATA_AGAIN:
				ifstream something("post.dat");
				// store file content into linkedlist
				LinkedList<string> fileContents = LinkedList<string>();
				string internal = "";
				if (something.is_open()) {
					while (getline(something, internal)) {
						fileContents.add(internal);
					}
					for (int i = 0; i < fileContents.length(); i++) {
						rapidjson::Document document = rapidjson::Document();
						document.Parse(fileContents.get(i).c_str());
						if (document.IsArray()) {
							//loop through the array. 
							for (SizeType j = 0; j < document.Size(); j++) {
								if (document[j]["Username"].GetString() == username) {
									//Username matches!!
									//now look for the account password. 
									if (document[j]["User"].IsObject()) {
										if (document[j]["User"]["Password"].GetString() == password) {
											std::cout << "Welcome " << document[j]["User"]["Username"].GetString() << "!" << endl;
											user = document[j]["User"]["Username"].GetString();
											std::system("cls");
											Sleep(1000);
											for (; ; ) {
												if (ifAfterAdd || ifUpdateNumberOfLikes || ifUpdateNumberOfLikesInv || justAddedLike || justRemovedLike || quitToListOfPostsCreatedBySelf || justAddedThumbsUp || ifUpdateNumberOfThumbsUp || ifUpdateNumberOfThumbsUpInv || justRemovedThumbsUp) {
													goto LOAD;
												}
												mainMenu();
												std::cout << "What do you plan to do today? " << endl;
											LOAD:
												string decision;
												if (!ifAfterAdd && !ifUpdateNumberOfLikes && !ifUpdateNumberOfLikesInv && !justAddedLike && !justRemovedLike && !quitToListOfPostsCreatedBySelf && !justAddedThumbsUp && !ifUpdateNumberOfThumbsUp && !ifUpdateNumberOfThumbsUpInv && !justRemovedThumbsUp)
													decision = "";
												else {
													decision = "3";
													ifAfterAdd = false;
													quitToListOfPostsCreatedBySelf = false;
													goto LOAD_SELF_POST;
												}
												getline(cin, decision);
												if (decision == "0") {      //Sign out of account.....
													user = "";
													goto LOGOUT;
												}
												else if (decision == "1") {     //Create a new thread......
													std::system("cls");
													Sleep(500);
													string topicTitle = "";
													string topicContents = "";
													cout << "Create new topic: " << endl;
													cout << "Please enter the title of your new topic: " << endl;
													cout << "Key in 'EXIT' or 'exit' or 'Exit' to exit to the main menu." << endl;
													getline(cin, topicTitle);
													if (topicTitle == "EXIT" || topicTitle == "exit" || topicTitle == "Exit") {
														std::system("cls");
														Sleep(500);
														continue;
													}
													else {
														std::system("cls");
														Sleep(500);
														cout << "Please enter the contents of your new topic: " << endl;
														getline(cin, topicContents);
														cout << "YOUR TOPIC: " << endl;
														cout << "=====================================================" << endl;
														cout << "Title: " << topicTitle << endl;
														cout << "Contents: " << topicContents << endl;
														cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
														cout << "[0] Exit to the main menu (Your changes will be lost)" << endl;
														cout << "[1] Post" << endl;
														cout << "=====================================================" << endl;
														std::cout << "Your choice?: ";
														string choice = "";
														getline(cin, choice);
														if (choice == "0") {
															continue;
														}
														else if (choice == "1") {
															system("cls");
															Sleep(500);
															cout << "POSTING YOUR TOPIC.." << endl;
															SystemHashTable snapshot = convertToHashTable(document);
															snapshot.get(username).topics.add(Topic
															(topicTitle, topicContents));
														   //add the new topic accordingly.
															snapshot.updateFile();
															std::system("cls");
															Sleep(500);
															ifAfterAdd = true;

														}
													}

												}
												else if (decision == "2") {     //Create a post.....
													std::system("cls");
													Sleep(500);
													string postTitle = "";
													string postContents = "";
													std::cout << "Please enter the title of your post: " << endl;
													std::cout << "Key in 'EXIT' or 'exit' or 'Exit' to exit to the main menu." << endl;
													getline(cin, postTitle);
													if (postTitle == "EXIT" || postTitle == "exit" || postTitle == "Exit") {
														std::system("cls");
														Sleep(500);
														continue;
													}
													else {
														std::system("cls");
														Sleep(500);
														std::cout << "Please enter the contents of your post: " << endl;
														getline(cin, postContents);
														std::cout << "YOUR POST: " << endl;
														std::cout << "=====================================================" << endl;
														std::cout << "Title: " << postTitle << endl;
														std::cout << "Contents: " << postContents << endl;
														std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
														std::cout << "[0] Exit to the main menu (Your changes will be lost)" << endl;
														std::cout << "[1] Edit title" << endl;
														std::cout << "[2] Edit contents" << endl;
														std::cout << "[3] Post" << endl;
														std::cout << "=====================================================" << endl;
														std::cout << "Your choice?: ";
														string choice = "";
														getline(cin, choice);
														if (choice == "0") {
															continue;
														}
														else if (choice == "3") {
															//update the user.
															std::system("cls");
															Sleep(500);
															std::cout << "POSTING...." << endl;
															SystemHashTable snapshot = convertToHashTable(document);
															snapshot.get(username).posts.add(Post(postTitle, postContents)); //add the new post accordingly.
															snapshot.updateFile();
															std::system("cls");
															Sleep(500);
															ifAfterAdd = true;
															goto RETRIEVE_DATA_AGAIN;
														}
													}
												}
												else if (decision == "3") {
												LOAD_SELF_POST:
													//Browse posts that the user has made. 
													LinkedList<Post> copy = LinkedList<Post>();
													for (SizeType j = 0; j < document.Size(); j++) {
														if (document[j].IsObject()) { //check whether it is a JSON object. 
															if (document[j]["Username"].GetString() == user) {
																if (document[j]["User"].IsObject()) {
																	if (document[j]["User"]["Posts"].IsArray()) {
																		for (int k = 0; k < document[j]["User"]["Posts"].Size(); k++) {
																			copy.add(Post(
																				document[j]["User"]["Posts"][k]["Title"].GetString(),
																				document[j]["User"]["Posts"][k]["Contents"].GetString(),
																				document[j]["User"]["Posts"][k]["NumberOfLikes"].GetInt64(),
																				document[j]["User"]["Posts"][k]["NumberOfThumbsUp"].GetInt64(),
																				LinkedList<Comment>()
																			));
																		}
																		//copy the contents of a comment one by one.
																		if (justAddedLike || justRemovedLike || justAddedThumbsUp || justRemovedThumbsUp) {
																			goto JUMP_TO_SKIP;
																		}
																	}
																	else {
																		// file being modified, users prompted to reinstall/ re-run program.
																		// logs out user.
																		std::cout << "File is modified! Please reinstall the application again!" << endl;
																		goto LOGOUT;
																	}
																}
																else {
																	std::cout << "File is modified! Please reinstall the application again!" << endl;
																	goto LOGOUT;
																}
															}
														}
													}
													// clear screen
													std::system("cls");
													Sleep(500);
													if (copy.isEmpty()) {
														std::cout << endl;
														std::cout << "There are no posts for display" << endl;
														std::cout << "______________________________________________________________" << endl;
														std::cout << "Number of posts: " << copy.length() << endl;

													}
													else {
														//Display the list of posts.
														for (int i = 0; i < copy.length(); i++) {
															std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
															std::cout << "|Post number: " << std::to_string(i + 1) << "                                           |" << endl;
															std::cout << "|Title: " << copy.get(i).title << ([&copy, i] {
																int lenWs = std::strlen("                                           ") - std::strlen(copy.get(i).title.c_str()) + (std::strlen("Post number:") - std::strlen("Title:"));
															string out = "";
															for (int internal = 0; internal <= lenWs; internal++) {
																out += " ";
															}
															out += "|";
															return out;
																})() << endl;
																std::cout << "|Contents: " << copy.get(i).contents << ([&copy, i] {
																	int lenWs = std::strlen("                                           ") - std::strlen(copy.get(i).contents.c_str()) + (std::strlen("Post number:") - std::strlen("Contents:"));
																string out = "";
																for (int internal = 0; internal <= lenWs; internal++) {
																	out += " ";
																}
																out += "|";
																return out;
																	})() << endl;
																	std::cout << "|Number of likes: " << std::to_string(copy.get(i).noOfLikes) << "                                       |" << endl;
																	std::cout << "|Number of thumbs up: " << std::to_string(copy.get(i).noOfThumbsUp) << "                                   |" << endl;
																	std::cout << "|Number of comments: " << std::to_string(copy.get(i).comment.length()) << "                                   |" << endl;

														}
														std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
														std::cout << "______________________________________________________________" << endl;
														std::cout << "Number of posts: " << copy.length() << endl;
														//Display a prompt to the user on what he / she would like to do.
														for (; ; ) {
															viewPostMenu();
															if (ifUpdateNumberOfLikes || ifUpdateNumberOfLikesInv || ifUpdateNumberOfThumbsUp || ifUpdateNumberOfThumbsUpInv) {
																goto JUMP_TO_SKIP;
															}
															cout << "Your decision: ";
														JUMP_TO_SKIP:
															string what;
															if (ifUpdateNumberOfLikes || ifUpdateNumberOfLikesInv || justAddedLike || justRemovedLike || justAddedThumbsUp || ifUpdateNumberOfThumbsUp || ifUpdateNumberOfThumbsUpInv || justRemovedThumbsUp) {
																what = "2";
																goto RETRIEVE_FULL_DATA_UPDATE_LIKES;
															}
															what = "";
															getline(cin, what);
															if (what == "0") {      //exit to the main menu
																system("cls");
																Sleep(500);
																break;
															}
															else if (what == "1") {     //exit to the posts list.

															}
															else if (what == "2") {     //open a post 
																for (; ; ) {
																	cout << "Please enter post number that you would like to open (Enter 1 to " << copy.length() << ")" << endl;
																RETRIEVE_FULL_DATA_UPDATE_LIKES:
																	string item;
																	if (ifUpdateNumberOfLikes || ifUpdateNumberOfLikesInv || justAddedLike || justRemovedLike || justAddedThumbsUp || ifUpdateNumberOfThumbsUp || ifUpdateNumberOfThumbsUpInv || justRemovedThumbsUp) {
																		item = std::to_string(likeAppliesToPostNumber);
																		justAddedLike = false;
																		justRemovedLike = false;
																		justAddedThumbsUp = false;
																		justRemovedThumbsUp = false;
																		goto TRANSFER_CONTROL_TO_TRY_BLOCK;
																	}
																	getline(cin, item);
																TRANSFER_CONTROL_TO_TRY_BLOCK:
																	try {
																		int postIndex = atoi(item.c_str());
																		if (postIndex >= 0 && postIndex <= copy.length()) {
																			string targetPostTitle = "";
																			string targetPostContent = "";
																			int numberOfLikes = 0;
																			int numberOfThumbsUp = 0;
																			LinkedList<Comment> listOfComments;
																			if (ifUpdateNumberOfLikes || ifUpdateNumberOfLikesInv || ifUpdateNumberOfThumbsUp || ifUpdateNumberOfThumbsUpInv) {
																				system("cls");
																				Sleep(500);
																				goto BEFORE_READING_DATA;
																			}
																			likeAppliesToPostNumber = NULL;
																			for (; ; ) {
																				cout << postIndex << endl;
																				Sleep(2000);
																				targetPostTitle = copy.get(postIndex - 1).title;
																				targetPostContent = copy.get(postIndex - 1).contents;
																				numberOfLikes = copy.get(postIndex - 1).noOfLikes;
																				numberOfThumbsUp = copy.get(postIndex - 1).noOfThumbsUp;
																				listOfComments = copy.get(postIndex - 1).comment;
																				system("cls");
																				Sleep(500);
																				cout << "Title: " << targetPostTitle << endl;
																				cout << endl;
																				cout << "Contents: " << targetPostContent << endl;
																				cout << endl;
																				cout << "Number of likes: " << std::to_string(numberOfLikes) << endl;
																				cout << endl;
																				cout << "Number of thumbs up: " << std::to_string(numberOfThumbsUp) << endl;
																				cout << endl;
																				cout << "Number of contents (Expandable)" << std::to_string(listOfComments.length()) << endl;
																				cout << endl;
																				expandComments();
																				cout << "Your choice: ";
																			BEFORE_READING_DATA:
																				string selection = "";
																				if (ifUpdateNumberOfLikes || ifUpdateNumberOfLikesInv || ifUpdateNumberOfThumbsUp || ifUpdateNumberOfThumbsUpInv) {
																					selection = "2";
																					goto BEFORE_TRY;
																				}
																				getline(cin, selection);
																			BEFORE_TRY:
																				try {
																					int selectionToInteger = atoi(selection.c_str());
																					if (ifUpdateNumberOfLikes) {
																						ifUpdateNumberOfLikes = false;
																						goto BEGIN_ANALYZING;
																					}
																					else if (ifUpdateNumberOfLikesInv) {
																						ifUpdateNumberOfLikesInv = false;
																						goto BEGIN_ANALYZING_REMOVE_LIKE;
																					}
																					else if (ifUpdateNumberOfThumbsUp) {
																						ifUpdateNumberOfThumbsUp = false;
																						goto BEGIN_ANALYZING_ADD_THUMBS_UP;
																					}
																					else if (ifUpdateNumberOfThumbsUpInv) {
																						ifUpdateNumberOfThumbsUpInv = false;
																						goto BEGIN_ANALYZING_REMOVE_THUMBS_UP;
																					}
																					if (selectionToInteger == 0) {
																						system("cls");
																						Sleep(500);
																						break;
																					}
																					else if (selectionToInteger == 1) {      //like a post 
																						//now we will need to get the hash table and then update the number of likes for this post.
																						ifUpdateNumberOfLikes = true;
																						likeAppliesToPostNumber = postIndex;
																						goto RETRIEVE_DATA_AGAIN;
																					BEGIN_ANALYZING:
																						//We have already checked if document is an array earlier. 
																						SystemHashTable sysHashTable = convertToHashTable(document);
																						int init = sysHashTable.get(user).posts.get(likeAppliesToPostNumber - 1).noOfLikes;
																						init += 1;
																						sysHashTable.get(user).posts.get1(likeAppliesToPostNumber - 1).noOfLikes = init;     
																						sysHashTable.updateFile();
																						//need to reload the data again.
																						justAddedLike = true;
																						likeAppliesToPostNumber = postIndex;
																						goto RETRIEVE_DATA_AGAIN;
																					}
																					else if (selectionToInteger == 2) {         //dislike a post
																						if (numberOfLikes > 0) {
																							ifUpdateNumberOfLikesInv = true;
																							likeAppliesToPostNumber = postIndex;
																							goto RETRIEVE_DATA_AGAIN;
																						BEGIN_ANALYZING_REMOVE_LIKE:
																							SystemHashTable sysHashTable = convertToHashTable(document);
																							int init = sysHashTable.get(user).posts.get(likeAppliesToPostNumber - 1).noOfLikes;
																							init -= 1;
																							if (init >= 0) {
																								sysHashTable.get(user).posts.get1(likeAppliesToPostNumber - 1).noOfLikes = init;
																								sysHashTable.updateFile();
																								justRemovedLike = true;
																								likeAppliesToPostNumber = postIndex;
																							}
																							goto RETRIEVE_DATA_AGAIN;
																						}
																						//make no changes if the number of likes is 0 at start. 
																					}
																					else if (selectionToInteger == 3) {
																						//add a thumbs up to the post
																						ifUpdateNumberOfThumbsUp = true;
																						likeAppliesToPostNumber = postIndex;
																						goto RETRIEVE_DATA_AGAIN;
																					BEGIN_ANALYZING_ADD_THUMBS_UP:
																						SystemHashTable sysHashTable = convertToHashTable(document);
																						int init = sysHashTable.get(user).posts.get(likeAppliesToPostNumber - 1).noOfThumbsUp;
																						init += 1;
																						sysHashTable.get(user).posts.get1(likeAppliesToPostNumber - 1).noOfThumbsUp = init;
																						sysHashTable.updateFile();
																						justAddedThumbsUp = true;
																						likeAppliesToPostNumber = postIndex;
																						goto RETRIEVE_DATA_AGAIN;
																					}
																					else if (selectionToInteger == 4) {
																						//remove a thumbs up from a post
																						ifUpdateNumberOfThumbsUpInv = true;
																						likeAppliesToPostNumber = postIndex;
																					BEGIN_ANALYZING_REMOVE_THUMBS_UP:
																						SystemHashTable sysHashTable = convertToHashTable(document);
																						int init = sysHashTable.get(user).posts.get(likeAppliesToPostNumber - 1).noOfThumbsUp;
																						init -= 1;
																						if (init >= 0) {
																							sysHashTable.get(user).posts.get1(likeAppliesToPostNumber - 1).noOfThumbsUp = init;
																							sysHashTable.updateFile();
																							justRemovedThumbsUp = true;
																							likeAppliesToPostNumber = postIndex;
																						}
																						goto RETRIEVE_DATA_AGAIN;
																						//make no changes if the number of thumbs up is 0 at the start. 
																					}
																					// display comments
																					else if (selectionToInteger == 5) {
																						cout << "==========================COMMENTS============================" << endl;
																						if (listOfComments.isEmpty()) {
																							cout << "Whooooosh..... No comments to be displayed for now." << endl;
																							cout << endl;
																							cout << "Number of comments: " << std::to_string(listOfComments.length()) << endl;
																						}
																						else {
																							for (int i = 0; i < listOfComments.length(); i++) {
																								cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
																								cout << "Comment number: " << std::to_string(i + 1) << endl;
																								cout << "User: " << listOfComments.get(i).users << endl;
																								cout << "Comment: " << listOfComments.get(i).contents << endl;
																								cout << "Number of likes: " << std::to_string(listOfComments.get(i).noOfLikes) << endl;
																								cout << "Number of thumbs up: " << std::to_string(listOfComments.get(i).noOfThumbsUp) << endl;
																							}
																							cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
																						}
																					}
																					// reply to post
																					else if (selectionToInteger == 6) {
																						cout << "==========================REPLY TO A POST: ============================" << endl;

																						string commentsContents;
																						cout << "Please enter your comments" << endl;
																						getline(cin, commentsContents);
																						std::cout << "YOUR COMMENT: " << endl;
																						std::cout << "=====================================================" << endl;

																						std::cout << "Contents: " << commentsContents << endl;
																						std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
																						std::cout << "[0] Exit to the main menu (Your changes will be lost)" << endl;
																						std::cout << "[1] Post" << endl;
																						std::cout << "=====================================================" << endl;
																						std::cout << "Your choice?: ";
																						string choice = "";
																						getline(cin, choice);
																						if (choice == "0") {      //exit to the main menu
																							system("cls");
																							Sleep(500);
																							break;
																						}
																						else if (choice == "1") {
																							// update the user
																							std::system("cls");
																							Sleep(500);
																							std::cout << "POSTING YOUR COMMENT.." << endl;
																							SystemHashTable snapshot = convertToHashTable(document);
																							snapshot.get(username).posts.get(0).comment.add(Comment
																							(commentsContents, username));
																							snapshot.updateFile();
																							std::system("cls");
																							Sleep(500);
																							ifAfterAdd = true;

																						}
																					}
																					// edit post
																					else if (selectionToInteger == 7) {
																						cout << "===================Edit Post=================" << endl;
																						string newPostTitle;
																						string newPostContents;
																						cout << "Please enter new post title: " << endl;
																						getline(cin, newPostTitle);
																						cout << "Please enter new post contents:" << endl;
																						getline(cin, newPostContents);
																						std::cout << "YOUR NEW POST: " << endl;
																						std::cout << "====================================" << endl;
																						std::cout << "+++++++++++++++++++++++++++++++++++" << endl;
																						std::cout << "[0] Exit to the main menu (Your changes will be lost)" << endl;
																						std::cout << "[1] Post" << endl;
																						std::cout << "====================================" << endl;
																						std::cout << "Your choice?: ";
																						string choice = "";
																						getline(cin, choice);
																						if (choice == "0") {
																							system("cls");
																							Sleep(500);
																							break;
																						}
																						else if (choice == "1") {
																							// update the user
																							std::system("cls");
																							Sleep(500);
																							std::cout << "UPDATING YOUR POST.." << endl;
																							SystemHashTable snapshot = convertToHashTable(document);
																							Post edited(newPostTitle, newPostContents);
																							snapshot.get(username).posts.replace(0, edited); //add the new post accordingly.
																							snapshot.updateFile();
																							std::system("cls");
																							Sleep(500);
																							ifAfterAdd = true;
																						}
																					}
																					// delete post
																					else if (selectionToInteger == 8) {
																						cout << "===================Delete Post=================" << endl;

																						string postindex;
																						cout << "Post to be deleted" << endl;
																						getline(cin, postindex);
																						std::cout << "POST TO BE DELETED: " << endl;
																						std::cout << "====================================" << endl;
																						std::cout << "+++++++++++++++++++++++++++++++++++" << endl;
																						std::cout << "[0] Exit to the main menu (Your changes will be lost)" << endl;
																						std::cout << "[1] DELETE" << endl;
																						std::cout << "====================================" << endl;
																						std::cout << "Your choice?: ";
																						string choice = "";
																						getline(cin, choice);
																						if (choice == "0") {
																							system("cls");
																							Sleep(500);
																							break;
																						}
																						else if (choice == "1") {
																							// update the user
																							std::system("cls");
																							Sleep(500);
																							std::cout << "DELETING YOUR POST.." << endl;
																							SystemHashTable snapshot = convertToHashTable(document);

																							snapshot.get(username).posts.remove(1); //remove the post accordingly.
																							snapshot.updateFile();
																							std::system("cls");
																							Sleep(500);
																							ifAfterAdd = true;
																						}
																					}
																					// input validation
																					else {
																						cout << "Invalid option. Please try again!" << endl;
																						Sleep(2000);
																						system("cls");
																					}
																				}
																				// input validation
																				catch (exception ignored) {
																					cout << "Invalid option. Please try again!" << endl;
																					Sleep(2000);
																					system("cls");
																				}
																			}
																			//extract the data again!
																			quitToListOfPostsCreatedBySelf = true;
																			goto RETRIEVE_DATA_AGAIN;
																		}
																		else {
																			cout << "Please enter a post number between 1 and " << copy.length() << " not " << postIndex << endl;
																			Sleep(2000);
																			system("cls");
																		}
																	}
																	catch (exception ignored) {

																	}
																}
															}
														}
													}
												}
												else if (decision == "4") {
													
													
													//load posts from others plus yourself.
													//all data copied into sysHashTable.
													std::system("cls");
													Sleep(500);
													SystemHashTable sysHashTable = convertToHashTable(document);
													LinkedList<string> usernames = LinkedList<string>();
													LinkedList<string> usernames1 = LinkedList<string>();
													if (document.IsArray()) {
														for (SizeType t = 0; t < document.Size(); t++) {
															string username = document[t]["Username"].GetString();
															usernames1.add(username);
															usernames.add(username);
														}
													}
													// initialize post number at 1;
													int postNumber = 1;
													// for loop to display posts.
													for (int i = 0; i < usernames.length(); i++) {
														LinkedList<Post> post = sysHashTable.get(usernames.get(i)).posts;
														
														for (int j = 0; j < post.length(); j++) {
															std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
															std::cout << "|Post number: " << postNumber << std::endl;
															std::cout << "|User: " << usernames1.get(i) << std::endl;
															std::cout << "|Title: " << post.get(j).title << std::endl;
															std::cout << "|Contents: " << post.get(j).contents << std::endl;
															std::cout << "|Number of Likes: " << post.get(j).noOfLikes << std::endl;
															std::cout << "|Number of Thumbs up: " << post.get(j).noOfThumbsUp << std::endl;
															std::cout << "|Number of comments: " << post.get(j).comment.length() << std::endl;
															postNumber++;
														}
													}
													std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
													std::cout << std::endl;
													for (; ; ) {
														viewPostMenu();
														std::cout << "Your choice? ";
														string what;
														getline(cin, what);
														try {
															int c = atoi(what.c_str()); // convert to array to integer
															if (c == 0) {   //quit to the main menu
																std::system("cls");
																Sleep(500);
																break;
															}
															else if (c == 1) { // edit post list

															}
															else if (c == 2) {      //Prompt the user for the post index
																std::cout << "Please enter post number that you would like to open (Enter 1 to " << postNumber - 1 << ")" << endl;
																string decision;
																getline(cin, decision);

															}
															// input validation
															else {
																std::cout << "Invalid option please try again!" << std::endl;
															}
														}
														// catch exception
														catch (exception e) {
															std::cout << "Invalid option please try again!" << std::endl;
														}
													}
												}
												else if (decision == "5") {
												LOAD_TOPIC:
													// Browse Topics that user have made
													
													SystemHashTable sysHashTable = convertToHashTable(document);
													LinkedList<string> usernames = LinkedList<string>();
													LinkedList<string> usernames1 = LinkedList<string>();
													if (document.IsArray()) {
														for (SizeType t = 0; t < document.Size(); t++) {
															string username = document[t]["Username"].GetString();
															usernames1.add(username);
															usernames.add(username);
														}
													}
													// initialize topic number as 1
													int topicNumber = 1;
													LinkedList<Topic> topic = sysHashTable.get(usernames.get(i)).topics;
													for (int i = 0; i < usernames.length(); i++) {
														
														// for loop to display topics.
														for (int j = 0; j < topic.length(); j++) {
															std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
															std::cout << "|Topic number: " << topicNumber << std::endl;
															std::cout << "|User: " << usernames1.get(i) << std::endl;
															std::cout << "|Title: " << topic.get(j).TopicTitle << std::endl;
															std::cout << "|Contents: " << topic.get(j).contents << std::endl;
															std::cout << "|Number of Likes: " << topic.get(j).noOfLikes << std::endl;
															std::cout << "|Number of Thumbs up: " << topic.get(j).noOfThumbsUp << std::endl;
															// increment topic number
															topicNumber++;
														}
													}
													if (topic.length() == 0) {
														cout << "Sorry :( THERE ARE NO TOPICS TO DISPLAY FOR NOW. PLEASE CREATE A TOPIC AND CHECK AGAIN!" << endl;
													}
													std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
													std::cout << std::endl;
													for (; ; ) {
														viewPostMenu();
														std::cout << "Your choice? ";
														string what;
														getline(cin, what);
														try {
															int c = atoi(what.c_str()); // array to integer
															if (c == 0) {   //quit to the main menu
																std::system("cls");
																Sleep(500);
																break;
															}
															else if (c == 1) { // open post list

															}
															else if (c == 2) {      //Prompt the user for the topic index
																std::cout << "Please enter topic number that you would like to open (Enter 1 to " << topicNumber - 1 << ")" << endl;
																string decision;
																getline(cin, decision);

															}
															else { // input validation
																std::cout << "Invalid option please try again!" << std::endl;
															}
														}
														catch (exception e) {
															std::cout << "Invalid option please try again!" << std::endl;
														}
													}
												}
												// search for topics 
												else if (decision == "6") {
													// target input
													int targetTopic;
													cout << "search for topics" << endl;
													cout << "Please enter the topic number to search (eg. 1,2)" << endl;
													cin >> targetTopic;
													int target = targetTopic;
													Post p;
													int noOfTopic = 2;
													int dataArray[] = { 1,2 }; // array item in the topics
													// search for target topic number, return whether it is found or not.
													int res = search(dataArray, noOfTopic, target);
													if (res != -1) {
														cout << "The target topic number: " << target << " is found  " << endl;
													}
													// search for target topic number, return whether it is found or not.
													else {
														cout << "The target topic number: " << target << " is not found " << endl;
													};
												}
												// search for posts 
												else if (decision == "7") {
													// target input 
													int targetPost;
													
													cout << "search for posts" << endl;
													cout << "Please enter the post number to search (eg. 1,2)" << endl;
													cin >> targetPost;
													int target = targetPost;
													Post p;
													
													int posts[] = {1,2,3}; // array item in the posts
													int noOfPosts = 2;
													// search for target post number, return whether it is found or not.
													int res = search(posts, noOfPosts, targetPost);
													if (res != -1) {
														cout << "The target post number: " << target << " is found  " << endl;
													}
													// search for target topic number, return whether it is found or not.
													else {
														
														cout << "The target post number: " << target << " is not found " << endl;
													}
												}
												// search for users 
												else if (decision == "8") {
													// target input 
													string targetUsers;
													cout << "search for users" << endl;
													cout << "Please enter the username to search (eg. John, Minteck)" << endl;
													// target input 
													cin >> targetUsers;
													string target = targetUsers;
													
													int noOfUsers = 5;

													string dataArray[] = { targetUsers }; // array item in the topics
													// search for target username, return whether it is found or not.
													int res = searchforUsers(dataArray, noOfUsers, target);
													if (res != -1) {
														cout << "The target user: " << target << " is found  " << endl;
													}
													else {
														cout << "The target user: " << target << " is not found " << endl;
													}
												}
											}
										}
									}
								}
							}
						}
						// input validation
						else {
							std::cout << "File is modified! Please reinstall the application again!" << endl;
							goto LOGOUT;
						}
					}
					// wrong password and username prompt.
					std::cout << "Sorry, wrong username or password! Please try again!" << endl;
					Sleep(2000);
				}
				else {
					std::cout << "Sorry, wrong username or password! Please try again!" << endl;
					Sleep(2000);
				}
			LOGOUT:
				std::system("cls");
				Sleep(1000);
			}
			else if (a == 2) {
				//Temporarily disable an account....
				//to implement. 
			}
			else if (a == 3) {
			REDO:
				//Create a new account.....
				std::system("cls");
				Sleep(500);
				std::cout << "Please enter the username of your new account: ";
				SystemHashTable snapshot = SystemHashTable();
				string newAccountUsername = "";  //Initialize a new username variable. 
				string newAccountPassword = ""; //Initialize a new password variable.
				getline(cin, newAccountUsername);
				std::cout << "Your username: " << newAccountUsername << std::endl;
				ifstream something("post.dat");
				LinkedList<string> fileContents = LinkedList<string>();
				string internal = "";
				if (something.is_open()) {
					while (getline(something, internal)) {
						fileContents.add(internal);
					}
					rapidjson::Document document;
					document.Parse(fileContents.get(0).c_str());
					SystemHashTable snapshot = convertToHashTable(document);
					if (snapshot.contains(newAccountUsername)) {
						std::cout << "Duplicate username found! Please try entering another username!" << endl;
						Sleep(1000);
						goto REDO;
					}
					else {
						for (; ; ) {
							std::cout << "Please enter the password for your new account: ";
							getline(cin, newAccountPassword);
							if (newAccountPassword.length() >= 8 && newAccountPassword.length() < 30) {
								std::system("cls");
								Sleep(500);
								break;
							}
							else {
								std::system("cls");
								Sleep(500);
								std::cout << "Sorry! The length of your password must be between 8 and 30 characters!" << std::endl;
								std::cout << "Current length of the password: " << std::to_string(newAccountPassword.length()) << std::endl;
							}
						}
						std::system("cls");
						Sleep(500);
						snapshot.add(newAccountUsername, newAccountPassword);
						snapshot.updateFile();
					}
				}
				else {   //if file does not exist
					SystemHashTable userList = SystemHashTable();           //Initialize a new hash table 
					string newAccountPassword = "";
					for (; ; ) {
						std::cout << "Please enter the password of your new account: ";
						getline(cin, newAccountPassword);
						if (newAccountPassword.length() < 8 && newAccountPassword.length() > 30) {
							std::cout << "Please make sure that the length of your password is between 8 (inclusive) and 30 characters(inclusive)" << endl;
						}
						else {
							break;
						}
					}
					userList.add(newAccountUsername, newAccountPassword);
					userList.updateFile();
					std::system("cls");
					Sleep(500);
					std::cout << "Successfully registered your account! Please try to log into the std::system using your new username and password" << endl;
					Sleep(2000);
					std::system("cls");
				}
			}
			else if (a == 4) {
				//Reset password
				//for security purposes we are going to use another file to write and store the security question. 
				for (; ; ) {
					ifstream something("post.dat");                             //Read the data from post.dat.
					LinkedList<string> fileContents = LinkedList<string>();
					string internal = "";
					rapidjson::Document document;
					if (something.is_open()) {
						while (getline(something, internal)) {
							fileContents.add(internal);
						}
					}
					document.Parse(fileContents.get(0).c_str());
					system("cls");
					Sleep(500);
					string usernameReset = "";
					std::cout << "Please enter the username of your account: ";
					getline(cin, usernameReset);
					SystemHashTable sysHashTable = convertToHashTable(document);
					if (sysHashTable.contains(usernameReset)) {
						for (; ; ) {
							std::system("cls");
							Sleep(500);
							string oldPassword = "";
							std::cout << "Please enter the old password for your account: ";
							getline(cin, oldPassword);
							if (sysHashTable.get(usernameReset).password == oldPassword) {
								for (; ; ) {
									std::system("cls");
									Sleep(500);
									string newPassword = "";
									std::cout << "Please enter your new password: ";
									getline(cin, newPassword);
									if (newPassword.length() >= 8 && newPassword.length() < 30) {
										sysHashTable.get(usernameReset).password = newPassword;
										sysHashTable.updateFile();
										std::system("cls");
										Sleep(500);
										std::cout << "The password has been successfully updated. Please try logging in again!" << std::endl;
										Sleep(2000);
										std::system("cls");
										break;
									}
								}
								break;
							}
							else {
								std::system("cls");
								Sleep(500);
								std::cout << "The password is not correct." << std::endl;
								Sleep(2000);
							}
						}
						break;
					}
					else {
						std::system("cls");
						std::cout << "Username is not found. Please try again" << std::endl;
						Sleep(2000);
					}
				}
			}
			else if (a == 5) {
				//Privacy policy
				cout << "==================PRIVACY POLICY===================" << endl;
				cout << "1) No part of this software shall be distributed without prior permission from the developers." << endl;

			}
			else {
				std::cout << "Invalid option please try again!" << std::endl;
				Sleep(2000);
				std::system("cls");
				Sleep(500);
			}
		}
		catch (exception e) {
			std::cout << "Invalid option please try again!" << std::endl;
			Sleep(2000);
			std::system("cls");
			Sleep(500);
		}
	}
}
