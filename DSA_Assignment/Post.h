//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================

#pragma once
// Post.h - Definition of Post class

#include<string>
#include<iostream>
#include "ReplyList.h"

using namespace std;

class Post
{
private:
	string message;
	string topic;
	string title;
	string author;
	string description;

public:
	//Methods
	Post();
	Post(string t, string desc, string msg, string user, string top);
	void print();

	//Getter
	string getMessage();
	string getTopic();
	string getTitle();
	string getAuthor();
	string getDescription();

	//Setter
	void setMessage(string msg);
	void setTopic(string topic);
	void setTitle(string title);
	void setAuthor(string author);
	void setDescription(string description);
};




