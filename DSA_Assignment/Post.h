#pragma once
// Post.h - Definition of Post class

#include<string>
#include<iostream>
#include "ReplyList.h"

using namespace std;

class Post
{
private:
	string postID;
	string title;
	string author;
	string description;
	ReplyList replyList;

public:
	//Methods
	Post();
	Post(string id, string title, string author,string desc, ReplyList rList);
	void addReply(Reply& reply, ReplyList& replyList);
	void deleteReply(Reply& reply, ReplyList& replyList);
	void print();

	//Getter
	string getPostID();
	string getTitle();
	string getUsername();
	string getDescription();
	ReplyList& getReplies();

	//Setter
	void setTitle(string title);
	void setAuthor(string author);
	void setDescription(string description);
};




