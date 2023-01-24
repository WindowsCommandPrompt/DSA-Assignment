// DSA Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> 
#include <sstream> 
#include <iomanip> 
#include "LinkedListNormal.h" 
#include <string>
#include <chrono>

#define IS_LOGGED_IN false

using namespace std; 
using namespace std::chrono; 

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

int main(void)
{

    ofstream ToFile("users.txt");   //where user information is stored. 
    ToFile << "C++ reading file not working";
    ToFile.close();

    string myText;
    ifstream MyReadFile("users.txt");
    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText)) {
        // Output the text from the file
        cout << myText;
    }

    // Close the file
    MyReadFile.close();
}
    //for (; ; ) {   
    //    login(); 
    //    cout << "Your choice: "; 
    //    string var = ""; 
    //    getline(cin, var);          //Accepts spacings between words....
    //    try {
    //        int a = stoi(var); 
    //        if (a == 0) {
    //            break; 
    //        }
    //        else if (a == 1) {
    //            //Login to an account
    //            cout << "Username: " << endl; 
    //            string username = ""; string password = ""; 
    //            getline(cin, username); 
    //            cout << "Password: " << endl; 
    //            getline(cin, password); 
    //        }
    //        else if (a == 2) {
    //            //Temporarily disable an account....
    //        }
    //        else if (a == 3) {
    //            //Create a new account.....
    //            cout << "Please enter the username of your new account: "; 
    //            string newAccountUsername = ""; 
    //            getline(cin, newAccountUsername); 
    //            //need to look through the list of usernames under users.txt and check for existance of the user.


    




    //            ToFile << "sfsidfjsfjsljdflsdfjssddsdsfdsfsdsdf"; 
    //        }
    //        else if (a == 4) {
    //            //Reset password
    //        }
    //        else if (a == 5) {
    //            //Privacy policy
    //        }
    //    }
    //    catch (exception e) {
    //        const char* varcstr = var.c_str(); 
    //        for (int i = 0; i < strlen(varcstr); i++) {
    //            
    //        }
    //    }
    //}


    




    //if (FromFile.is_open()) {
    //    // Get the file size
    //    FromFile.seekg(0, FromFile.end);
    //    int size = FromFile.tellg();
    //    FromFile.seekg(0, FromFile.beg);

    //    // Allocate memory for the buffer
    //    char* buffer = new char[size];

    //    // Read the data into the buffer
    //    FromFile.read(buffer, size);

    //    // Do something with the data
    //    for (int i = 0; i < size; i++) {
    //        cout << buffer[i];
    //    }

    //    // Close the file
    //    FromFile.close();
    //} else {
    //    cout << "Unable to open file" << endl;
    //}
    //return 0;
   
}

