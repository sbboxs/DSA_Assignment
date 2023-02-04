#pragma once
// Topic.h - Definition of Topic class

#include<string>
#include<iostream>
#include "PostList.h"

using namespace std;

//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================

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
	bool addPost(Post& post);
	//void deletePost(Post& post, PostList& postList);
	bool load(string topic);
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

