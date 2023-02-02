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
	string topic;
	string title;
	string author;
	string description;
	ReplyList replyList;

public:
	//Methods
	Post();
	Post(string PostID, string Topic, string Title, string Author, string Desc);
	void addReply(Reply& reply, ReplyList& replyList);
	//void deleteReply(Reply& reply, ReplyList& replyList);
	void print();

	//Getter
	string getPostID();
	string getTopic();
	string getTitle();
	string getAuthor();
	string getDescription();
	ReplyList& getReplies();

	//Setter
	void setPostID(string pID);
	void setTopic(string topic);
	void setTitle(string title);
	void setAuthor(string author);
	void setDescription(string description);
};




