
// Customer.cpp - Implementation of Customer class
#include "Post.h"

Post::Post() {}

Post::Post(string PostID, string Topic, string Title, string Author, string Desc)
{
	postID = PostID;
	topic = Topic;
	title = Title;
	author = Author;
	description = Desc;
}


