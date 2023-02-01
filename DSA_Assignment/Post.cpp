
// Customer.cpp - Implementation of Customer class
#include "Post.h"

Post::Post() {}

Post::Post(string id, string t, string user, string desc, ReplyList rList)
{
	postID = id;
	title = t;
	username = user;
	description = desc;
	replyList = rList;

}


