// DSA Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> 
#include <sstream> 
#include <iomanip> 
#include "LinkedListNormal.h" 
#include "SystemHashTable.h"
#include "rapidjson/document.h"
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

int main(void)
{
    ofstream ToFile("users.txt");               //To write to 
    ifstream MyReadFile("users.txt");           //To read from 

    //ofstream ToFile("users.txt");   //where user information is stored. 
    //ToFile << "C++ reading file not working";
    //ToFile.close();
    //string myText;
    //ifstream MyReadFile("users.txt");
    //// Use a while loop together with the getline() function to read the file line by line
    //while (getline(MyReadFile, myText)) {
    //    // Output the text from the file
    //    cout << myText;
    //}
    //// Close the file
    //MyReadFile.close();
    //ToFile <<  { 
//         "0": [
//             { 
//                "user": "username", 
//                "posts": [ 
//                    { 
//                        "noOfLikes": 12, 
//                        "noOfThumbsUp": 12, 
//                        "title": "some kind of title", 
//                        "content": "post contents as a text....", 
//                        "topic": "what topic it belongs to.
//                    }, 
//                    { 
//                       . . . . . 
//                    } 
//                ]
//             }, 
//             { 
//                "user": "anotherUsername", 
//                "posts": [                 ]
//             } 
//         ], 
//         "1": null
//      }


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
                cout << "Username: " << endl;
                string username = ""; string password = "";
                getline(cin, username);
                cout << "Password: " << endl;
                getline(cin, password);
            }
            else if (a == 2) {
                //Temporarily disable an account....
            }
            else if (a == 3) {
                Reprompt: 
                    //Create a new account.....
                    cout << "Please enter the username of your new account: ";
                    string newAccountUsername = "";                                 //Initialize a new variable.
                    getline(cin, newAccountUsername);
                    //need to look through the list of usernames under users.txt and check for existance of the user.
                    string stringifiedJSONDocumentLine = "";
                    LinkedListNormal fileContents = LinkedListNormal();
                    while (getline(MyReadFile, stringifiedJSONDocumentLine)) {
                        fileContents.add(stringifiedJSONDocumentLine);
                    }
                    MyReadFile.close();                         //close the file after reading....
                    if (fileContents.isEmpty()) {               //if list is empty means no users yet can just add.
                        SystemHashTable newHashTable = SystemHashTable();
                        for (; ; ) {
                            cout << "Please enter a password for your new account: ";
                            string pre = "";
                            getline(cin, pre);
                            cout << "Please enter your password again: ";
                            string post = "";
                            getline(cin, post);
                            if (pre == post) {
                                newHashTable.add(newAccountUsername, pre);
                                break;
                            }
                        }
                        break; //Break to the main menu for the user to sign in using the account.
                    }
                    else {
                        //Analyze the fileContents....
                        string open = "";
                        for (int i = 0; i < fileContents.length(); i++) {
                            open += fileContents.get(i);
                        }
                        const char* hashTableAsString = open.c_str();
                        Document document = Document();
                        document.Parse(hashTableAsString);
                        if (document.IsObject()) {
                            //loop through the array and look through its properties....
                            for (SizeType i = 0; ; i++) {
                                try {
                                    if (document[std::to_string(i).c_str()].IsArray()) {
                                        for (SizeType j = 0; j < document[std::to_string(i).c_str()].Size(); ++j) {
                                            if (document[std::to_string(i).c_str()][j]["username"] == newAccountUsername) {
                                                //duplicate username has been found and the program will tell the user that he / she needs to enter a new username again. 

                                                cout << "Duplicate username found within the database! Please try again" << endl; 
                                                goto Reprompt; 
                                            }
                                        }
                                    }

                                }
                                catch (exception e) { goto PasswordPrompt; }
                            }
                        }
                    PasswordPrompt: 
                        cout << "Please enter a password: " << endl; 

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
//     { 
//         "0": [
//             { 
//                "user": "username", 
//                "posts": [ 
//                    { 
//                        "noOfLikes": 12, 
//                        "noOfThumbsUp": 12, 
//                        "title": "some kind of title", 
//                        "content": "post contents as a text....", 
//                        "topic": "what topic it belongs to.
//                    }, 
//                    { 
//                       . . . . . 
//                    } 
//                ]
//             }, 
//             { 
//                "user": "anotherUsername", 
//                "posts": [                 ]
//             } 
//         ], 
//         "1": null
//      }
//}


    




   


