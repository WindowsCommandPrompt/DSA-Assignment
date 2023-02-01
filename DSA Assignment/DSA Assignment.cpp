// DSA Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> 
#include <sstream> 
#include <Windows.h>
#include "Comment.h"
#include "LinkedList.h" 
#include "SystemHashTable.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>


#define IS_LOGGED_IN false

using namespace std; 
using namespace rapidjson; 

static string user = ""; 

void login(void) {
    //Print out some kind of menu like thing
    cout << "===========================================================" << endl;
    cout << "#         WELCOME TO THE PRO EDUCATIONIST FORUM!!!        #" << endl;
    cout << "#                                                         #" << endl;
    cout << "# [0] Quit Program                                        #" << endl; 
    cout << "# [1] Login into an account                               #" << endl; 
    cout << "# [2] Temporarily disable account                         #" << endl; 
    cout << "# [3] Create a new account                                #" << endl; 
    cout << "# [4] Forgot my account credentials                       #" << endl; 
    cout << "# [5] Privacy policy                                      #" << endl;  
    cout << "===========================================================" << endl; 
} 

//main user interface once the 
void mainMenu(void) {
    cout << "Hello, " << user << endl; 
    cout << "===========================================================" << endl; 
    cout << "# [0] Logout                                              #" << endl; 
    cout << "# [1] Create a new thread                                 #" << endl;
    cout << "# [2] Create a new post                                   #" << endl;
    cout << "# [3] Browse post                                         #" << endl; 
    cout << "===========================================================" << endl; 
}

void main(void)
{
    //// create a JSON object
    //Document jsonDoc;
    //jsonDoc.SetObject();
    //Value user;
    //user.SetString("Peter Dan");
    //jsonDoc.AddMember("User", user, jsonDoc.GetAllocator());
    //Value PostThumbsUp;
    //PostThumbsUp.SetInt(12);
    //jsonDoc.AddMember("Post Thumbs Up", PostThumbsUp, jsonDoc.GetAllocator());
    //Value PostLikes;
    //PostLikes.SetInt(12);
    //jsonDoc.AddMember("Post Likes", PostLikes, jsonDoc.GetAllocator());
    //Value title;
    //title.SetString("Implementing Hash Table");
    //jsonDoc.AddMember("Title", title, jsonDoc.GetAllocator());
    //Value content;
    //content.SetString("Hash table is a type of data structures...");
    //jsonDoc.AddMember("Content", content, jsonDoc.GetAllocator());
    //Value topic;
    //topic.SetString("C++");
    //jsonDoc.AddMember("Topic", topic, jsonDoc.GetAllocator());
    //StringBuffer buffer;
    //Writer<StringBuffer> writer(buffer);
    //jsonDoc.Accept(writer);
    //string jsonString = buffer.GetString();
    //ofstream datFile;
    //datFile.open("post.dat");
    //datFile << jsonString;
    //datFile.close();



    for (; ; ) {                    //Initiate an infinite loop. 
        login();                    //Display the main menu to the user. 
        cout << "Your choice: ";    //Prompting the user for his / her choice
        string var = "";            //string variable to capture the user's choice
        getline(cin, var);          //Accepts spacings between words....
        try {
            int a = stoi(var);      //try converting the string to an integer. 
            if (a == 0) {           //quit the program if the user selects 0. 
                return;
            }
            else if (a == 1) {
                //Login to an account
                system("cls"); 
                Sleep(500); 
                cout << "Username: ";
                string username = ""; string password = "";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                ifstream something("post.dat");
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
                                            cout << "Welcome " << document[j]["User"]["Username"].GetString() << "!" << endl;
                                            user = document[j]["User"]["Username"].GetString();
                                            system("cls"); 
                                            Sleep(1000); 
                                            for (; ; ) {
                                                mainMenu(); 
                                                cout << "What do you plan to do today? " << endl; 
                                                string decision = ""; 
                                                getline(cin, decision); 
                                                if (decision == "0") {      //Sign out of account.....
                                                    user = ""; 
                                                    goto LOGOUT; 
                                                }
                                                else if (decision == "1") {     //Create a new thread......

                                                }
                                                else if (decision == "2") {     //Create a post.....
                                                    system("cls"); 
                                                    Sleep(500); 
                                                    string postTitle = ""; 
                                                    string postContents = ""; 
                                                    cout << "Please enter the title of your post: " << endl; 
                                                    cout << "Key in 'EXIT' or 'exit' or 'Exit' to exit to the main menu." << endl; 
                                                    getline(cin, postTitle); 
                                                    if (postTitle == "EXIT" || postTitle == "exit" || postTitle == "Exit") {
                                                        system("cls"); 
                                                        Sleep(500); 
                                                        continue; 
                                                    }
                                                    else {
                                                        system("cls"); 
                                                        Sleep(500); 
                                                        cout << "Please enter the contents of your post: " << endl; 
                                                        getline(cin, postContents); 
                                                        cout << "YOUR POST: " << endl; 
                                                        cout << "=====================================================" << endl; 
                                                        cout << "Title: " << postTitle << endl; 
                                                        cout << "Contents: " << postContents << endl; 
                                                        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl; 
                                                        cout << "[0] Exit to the main menu (Your changes will be lost)" << endl; 
                                                        cout << "[1] Edit title" << endl; 
                                                        cout << "[2] Edit contents" << endl;
                                                        cout << "[3] Post" << endl;
                                                        cout << "=====================================================" << endl; 
                                                        cout << "Your choice?: "; 
                                                        string choice = ""; 
                                                        getline(cin, choice); 
                                                        if (choice == "0") {
                                                            continue; 
                                                        }
                                                        else if (choice == "3") {
                                                            //update the user.
                                                            system("cls"); 
                                                            Sleep(500); 
                                                            cout << "POSTING...." << endl; 
                                                            SystemHashTable snapshot = SystemHashTable();
                                                            for (int j = 0; j < document.Size(); j++) {
                                                                string username = document[j]["User"]["Username"].GetString();
                                                                string password = document[j]["User"]["Password"].GetString();
                                                                LinkedList<Post> copy = LinkedList<Post>();
                                                                if (document[j]["User"]["Posts"].IsArray()) {
                                                                    for (SizeType k = 0; k < document[j]["User"]["Posts"].Size(); k++) {
                                                                        copy.add(Post(
                                                                            document[j]["User"]["Posts"]["Title"].GetString(),
                                                                            document[j]["User"]["Posts"]["Contents"].GetString(),
                                                                            document[j]["User"]["Posts"]["NumberOfLikes"].GetInt64(),
                                                                            document[j]["User"]["Posts"]["NumberOfThumbsUp"].GetInt64()
                                                                        ));
                                                                    }
                                                                }
                                                                snapshot.add(username, password, copy); // erase the previous post - bug 
                                                            }
                                                            cout << "Initial posts length: " << snapshot.get(username).posts.length() << endl; 
                                                            LinkedList<Post>& d = snapshot.get(username).posts; 
                                                            d.add(Post(postTitle, postContents, 0, 0));
                                                            
                                                            cout << "New posts length\n" << snapshot.get(username).posts.length() << endl;




                                                            //snapshot.updateFile();
                                                        }
                                                    }
                                                }
                                                else if (decision == "3") {
                                                    //Browse posts that the user has made. 
                                                    SystemHashTable snapshot = SystemHashTable(); 
                                                    for (int j = 0; j < document.Size(); j++) {
                                                        string username = document[j]["User"]["Username"].GetString();
                                                        string password = document[j]["User"]["Password"].GetString();
                                                        LinkedList<Post> copy = LinkedList<Post>();
                                                        if (document[j]["User"]["Posts"].IsArray()) {
                                                            for (SizeType k = 0; k < document[j]["User"]["Posts"].Size(); k++) {
                                                                copy.add(Post(
                                                                    document[j]["User"]["Posts"]["Title"].GetString(),
                                                                    document[j]["User"]["Posts"]["Contents"].GetString(),
                                                                    document[j]["User"]["Posts"]["NumberOfLikes"].GetInt64(),
                                                                    document[j]["User"]["Posts"]["NumberOfThumbsUp"].GetInt64()
                                                                ));
                                                            }
                                                        }
                                                        snapshot.add(username, password, copy);
                                                    }
                                                    LinkedList<Post> postsList = snapshot.get(username).posts; 
                                                    if (postsList.isEmpty()) {
                                                        cout << "No posts to display for now" << endl; 
                                                    }
                                                    else {
                                                        for (int i = 0; i < postsList.length(); i++) {

                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            cout << "File is modified! Please reinstall the application again!" << endl; 
                            goto LOGOUT; 
                        }
                    }
                    cout << "Sorry, wrong username or password! Please try again!" << endl; 
                }
            LOGOUT: 
                system("cls"); 
                Sleep(1000); 
            }
            else if (a == 2) {
                //Temporarily disable an account....
            }
            else if (a == 3) {
            REDO:
                //Create a new account.....
                system("cls"); 
                Sleep(500); 
                cout << "Please enter the username of your new account: ";
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
                    for (int i = 0; i < fileContents.length(); i++) {
                        rapidjson::Document document = rapidjson::Document(); 
                        document.Parse(fileContents.get(i).c_str());
                        if (document.IsArray()) {
                            for (SizeType j = 0; j < document.Size(); j++) {
                                if (document[j]["Username"].GetString() == newAccountUsername) {
                                    cout << "Duplicate username found! Please try entering another username!" << endl; 
                                    Sleep(1000); 
                                    goto REDO; 
                                } 
                            }
                            for (; ; ) {
                                //Now prompt for the password....
                                std::cout << "Please enter the password for your new account: ";
                                getline(cin, newAccountPassword);
                                if (newAccountPassword.length() >= 8 && newAccountPassword.length() < 30) {
                                    system("cls"); 
                                    Sleep(500); 
                                    break;
                                }
                                cout << "Sorry, your account password should be between 8 and 30 characters." << endl;
                                Sleep(2000);
                                system("cls");
                                Sleep(500);
                            }
                            for (int j = 0; j < document.Size(); j++) {
                                string username = document[j]["User"]["Username"].GetString();
                                string password = document[j]["User"]["Password"].GetString();
                                LinkedList<Post> copy = LinkedList<Post>();
                                if (document[j]["User"]["Posts"].IsArray()) {
                                    for (SizeType k = 0; k < document[j]["User"]["Posts"].Size(); k++) {
                                        copy.add(Post(
                                            document[j]["User"]["Posts"]["Title"].GetString(),
                                            document[j]["User"]["Posts"]["Contents"].GetString(),
                                            document[j]["User"]["Posts"]["NumberOfLikes"].GetInt64(),
                                            document[j]["User"]["Posts"]["NumberOfThumbsUp"].GetInt64()
                                        ));
                                    }
                                }
                                snapshot.add(username, password, copy);
                                snapshot.updateFile();
                            } 
                        }
                    }
                    snapshot.add(newAccountUsername, newAccountPassword); 
                    snapshot.updateFile(); 
                }
                else {   //if file does not exist
                    cout << "File does not exist!" << endl; 
                    SystemHashTable userList = SystemHashTable();           //Initialize a new hash table 
                    string newAccountPassword = "";
                    for (; ; ) {
                        cout << "Please enter the password of your new account: ";
                        getline(cin, newAccountPassword);
                        if (newAccountPassword.length() < 8 && newAccountPassword.length() > 30) {
                            cout << "Please make sure that the length of your password is between 8 (inclusive) and 30 characters(inclusive)" << endl;
                        }
                        else {
                            break;
                        }
                    }
                    userList.add(newAccountUsername, newAccountPassword);
                    userList.updateFile();
                }
            }
            else if (a == 4) {
                //Reset password
            }
            else if (a == 5) {
                //Privacy policy
            }
        }
        catch (exception e) {
            const char* varcstr = var.c_str();
            for (int i = 0; i < strlen(varcstr); i++) {

            }
        }
    }
} 



    




   


