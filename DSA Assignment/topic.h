#pragma once
#include <string>
// This file will be responsible for the tracking of the topics
class Topic {
private:
    int noOfPosts;
    int noOfLikes; // will this be needed?
    string TopicTitle;
    string contents;

public:
    int getNumberOfPosts(void);
    int getNumberOfLikes(void);
    string getTopicTitle(void);
    string getContents(void);
    void setNumberOfPosts(int newPost);
    void setNumberOfLikes(int a);
    void setTopicTitle(string newTopicTitle);
    void setContents(string content);
};