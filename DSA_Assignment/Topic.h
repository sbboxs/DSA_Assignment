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
	int totalPost;
	PostList postList;

public:
	//Methods 
	Topic();
	Topic(string topic, string auth, int totalPost);
	void updateTotalPost();
	bool addPost(Post& post);
	void print();

	//Getter
	string getTopic();
	string getAuthor();
	int getTotalPost();
	PostList& getPosts();

	//Setter
	void setTopic(string topic);
	void setAuthor(string author);
	void setTotalPost(int totalPost);

};

