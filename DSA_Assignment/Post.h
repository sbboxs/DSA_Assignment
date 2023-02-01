
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
	string username;
	string description;
	ReplyList replyList;

public:
	Post();
	Post(string id, string t, string user, string desc, ReplyList rList);
};




