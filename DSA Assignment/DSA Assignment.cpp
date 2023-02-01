// DSA Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define RAPIDJSON_HAS_STDSTRING 1

#include <iostream>
#include <fstream> 
#include <sstream> 
#include <Windows.h>
#include <format>
#include "Comment.h"
#include "LinkedList.h" 
#include "systemHashTable.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>

using namespace std; 
using namespace rapidjson; 

static string user = ""; 
static bool ifAfterAdd = false; 

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

//main user interface once the 
void mainMenu(void) {
    std::cout << "Hello, " << user << endl; 
    std::cout << "===========================================================" << endl; 
    std::cout << "# [0] Logout                                              #" << endl; 
    std::cout << "# [1] Create a new thread                                 #" << endl;
    std::cout << "# [2] Create a new post                                   #" << endl;
    std::cout << "# [3] Browse my posts                                     #" << endl; 
    std::cout << "# [4] Explore other people's posts                        #" << endl; 
    std::cout << "===========================================================" << endl; 
}

void viewPostMenu(void) {
    std::cout << "===========================================================" << endl; 
    std::cout << "# [0] Exit to the main menu                               #" << endl; 
    std::cout << "# [1] Exit to posts list                                  #" << endl; 
    std::cout << "# [OPEN] Open a post                                      #" << endl; 
    std::cout << "===========================================================" << endl;
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
                RETRIEVE_DATA_AGAIN:
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
                                            std::cout << "Welcome " << document[j]["User"]["Username"].GetString() << "!" << endl;
                                            user = document[j]["User"]["Username"].GetString();
                                            std::system("cls");
                                            Sleep(1000);
                                            for (; ; ) {
                                                if (ifAfterAdd) {
                                                    goto LOAD;
                                                }
                                                mainMenu();
                                                std::cout << "What do you plan to do today? " << endl;
                                            LOAD:
                                                string decision; 
                                                if (!ifAfterAdd)
                                                    decision = "";
                                                else {
                                                    decision = "3";
                                                    goto LOAD_SELF_POST;
                                                } 
                                                getline(cin, decision);
                                                if (decision == "0") {      //Sign out of account.....
                                                    user = "";
                                                    goto LOGOUT;
                                                }
                                                else if (decision == "1") {     //Create a new thread......

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
                                                            SystemHashTable snapshot = SystemHashTable();
                                                            LinkedList<Post> copy;
                                                            for (int j = 0; j < document.Size(); j++) {
                                                                std::cout << "Entered the for loop and start retrieving the data" << endl;
                                                                string username = document[j]["User"]["Username"].GetString();
                                                                string password = document[j]["User"]["Password"].GetString();
                                                                copy = LinkedList<Post>();              //Insert a blank linked list into the std::system hash table. Don't add anything
                                                                snapshot.add(username, password, copy); // erase the previous post - bug 
                                                            }
                                                            //Start copying the contents into the hash table accordingly....
                                                            if (document[j]["User"]["Posts"].IsArray()) {
                                                                for (SizeType k = 0; k < document[j]["User"]["Posts"].Size(); k++) {
                                                                    snapshot.get(username).posts.add(Post(
                                                                        document[j]["User"]["Posts"][k]["Title"].GetString(),
                                                                        document[j]["User"]["Posts"][k]["Contents"].GetString(),
                                                                        document[j]["User"]["Posts"][k]["NumberOfLikes"].GetInt64(),
                                                                        document[j]["User"]["Posts"][k]["NumberOfThumbsUp"].GetInt64()
                                                                    ));
                                                                }
                                                            }
                                                            snapshot.get(username).posts.add(Post(postTitle, postContents, 0, 0)); //add the new post accordingly.
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
                                                                                document[j]["User"]["Posts"][k]["NumberOfThumbsUp"].GetInt64()
                                                                            ));
                                                                        }
                                                                    }
                                                                    else {
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
                                                    int length = copy.length(); 
                                                    std::system("cls"); 
                                                    Sleep(500); 
                                                    if (copy.isEmpty()) {
                                                        std::cout << endl; 
                                                        std::cout << "There are no posts for display" << endl; 
                                                        std::cout << "______________________________________________________________" << endl; 
                                                        std::cout << "Number of posts: " << length << endl; 
                                                        
                                                    }
                                                    else {
                                                        //Display the list of posts.
                                                        for (int i = 0; i < length; i++) {
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
                                                        }
                                                        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
                                                        std::cout << "______________________________________________________________" << endl;
                                                        std::cout << "Number of posts: " << length << endl;
                                                        //Display a prompt to the user on what he / she would like to do.
                                                        for (; ; ) {
                                                            viewPostMenu();
                                                            cout << "Your decision: ";
                                                            string what;
                                                            getline(cin, what);
                                                            if (what == "0") {
                                                                
                                                            }
                                                            else if (what == "1") {
                                                                break; 
                                                            }
                                                            else if (what == "OPEN") {

                                                            }
                                                        } 
                                                    }
                                                }
                                                else if (decision == "4") {
                                                    //to implement
                                                    //only load the posts from toher users....
                                                    LinkedList<Post> copyPosts = LinkedList<Post>(); 
                                                    for (SizeType j = 0; j < document.Size(); j++) {

                                                    }
                                                } 
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            std::cout << "File is modified! Please reinstall the application again!" << endl;
                            goto LOGOUT;
                        }
                    }
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
                    for (int i = 0; i < fileContents.length(); i++) {
                        rapidjson::Document document = rapidjson::Document();
                        document.Parse(fileContents.get(i).c_str());
                        if (document.IsArray()) {
                            for (SizeType j = 0; j < document.Size(); j++) {
                                if (document[j]["Username"].GetString() == newAccountUsername) {
                                    std::cout << "Duplicate username found! Please try entering another username!" << endl;
                                    Sleep(1000);
                                    goto REDO;
                                }
                            }
                            for (; ; ) {
                                //Now prompt for the password....
                                std::cout << "Please enter the password for your new account: ";
                                getline(cin, newAccountPassword);
                                if (newAccountPassword.length() >= 8 && newAccountPassword.length() < 30) {
                                    std::system("cls");
                                    Sleep(500);
                                    break;
                                }
                                std::cout << "Sorry, your account password should be between 8 and 30 characters." << endl;
                                Sleep(2000);
                                std::system("cls");
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
                    std::system("cls");
                    Sleep(500);
                    std::cout << "Successfully registered your account! Please try to log into the std::system using your new username and password" << endl;
                    Sleep(2000);
                    std::system("cls");
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