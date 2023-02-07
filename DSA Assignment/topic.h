// ==================================================================
// Student Number : S10228079B, S10222023J
// Student Name :   Ho Min Teck, Li Zhe Yun 
// Module Group :   P03
// ==================================================================



#pragma once
#include <string>
#include "Post.h"
using namespace std; 

// This file will be responsible for the tracking of the topics
class Topic {
public:
    // default constructor
    Topic(const Topic&) = default;
    Topic& operator=(const Topic&) = default;
    // move constructor
    Topic(Topic&& otherTopic) {
        this->TopicTitle = std::move(otherTopic.TopicTitle);
        this->contents = std::move(otherTopic.contents);
        this->noOfLikes = std::move(otherTopic.noOfLikes);
    }
    Topic(void) {

    }
    Topic(string TopicTitle, string contents) // new Topic
    {
        this->TopicTitle = TopicTitle;
        this->contents = contents;
        this->noOfPosts = 0;
        this->noOfLikes = 0;
    }
    Topic (string TopicTitle,string contents, string user, int noOfLikes, int noOfThumbsUp, LinkedList<Post> post) {  // new Topic
        this->TopicTitle = TopicTitle;
        this->contents = contents;
        this->users = user;
        this->noOfLikes = 0;
        this->noOfThumbsUp = 0;
        this->post = post;
    }
    // deconstructor
    ~Topic(void) {

    }
    // variables
    int noOfPosts;
    int noOfLikes; 
    string TopicTitle;
    string contents;
    string users;
    int noOfThumbsUp;
    LinkedList<Post> post;
};