#pragma once
#include <string>

using namespace std; 

// This file will be responsible for the tracking of the topics
class Topic {
public:
    Topic(const Topic&) = default;
    Topic& operator=(const Topic&) = default;
    Topic(Topic&& otherTopic) {
        this->TopicTitle = std::move(otherTopic.TopicTitle);
        this->contents = std::move(otherTopic.contents);
        this->noOfLikes = std::move(otherTopic.noOfLikes);
    }
    Topic(void) {

    }
    Topic(string TopicTitle, string contents)
    {
        this->TopicTitle = TopicTitle;
        this->contents = contents;
        this->noOfPosts = 0;
        this->noOfLikes = 0;
    }
    ~Topic(void) {

    }
    int noOfPosts;
    int noOfLikes; 
    string TopicTitle;
    string contents;

};