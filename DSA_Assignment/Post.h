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
	ReplyList replyList;

public:
	//Methods
	Post();
	Post(string t, string desc, string msg, string user, string top);
	void addReply(Reply& reply, ReplyList& replyList);
	//void deleteReply(Reply& reply, ReplyList& replyList);
	void print();

	//Getter
	string getMessage();
	string getTopic();
	string getTitle();
	string getAuthor();
	string getDescription();
	ReplyList& getReplies();

	//Setter
	void setMessage(string msg);
	void setTopic(string topic);
	void setTitle(string title);
	void setAuthor(string author);
	void setDescription(string description);
};




