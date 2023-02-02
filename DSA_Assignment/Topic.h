#pragma once
// Topic.h - Definition of Topic class

#include<string>
#include<iostream>
#include "PostList.h"

using namespace std;

class Topic
{
private:
	string topic;
	string author;
	PostList postList;

public:

	//Methods 
	Topic();
	Topic(string topic, string auth, PostList pList);
	void addPost(Post& post, PostList& postList);
	//void deletePost(Post& post, PostList& postList);
	void print();

	//Getter
	string getTopic();
	string getAuthor();
	PostList& getPosts();

	//Setter
	void setTopic(string topic);
	void setAuthor(string author);
	void setPostList(Post pList);

};

