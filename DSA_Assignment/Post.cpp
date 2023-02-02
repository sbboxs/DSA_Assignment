#include "Post.h"

Post::Post()
{
	postID = "";
	topic = "";
	title = "";
	author = "";
	description = "";
}

Post::Post(string PostID, string Topic, string Title, string Author, string Desc)
{
	postID = PostID;
	topic = Topic;
	title = Title;
	author = Author;
	description = Desc;
}

void Post::addReply(Reply& reply, ReplyList& replyList)
{
	replyList.add(reply);
}

//void Post::deleteReply(Reply& reply, ReplyList& replyList)
//{
//	replyList.remove();
//}

void Post::print()
{
	cout << "Post ID: " << postID << endl;
	cout << "Topic: " << topic << endl;
	cout << "Title: " << title << endl;
	cout << "Author: " << author << endl;
	cout << "Description: " << description << endl;
}

string Post::getPostID()
{
	return postID;
}

string Post::getTopic()
{
	return topic;
}

string Post::getTitle()
{
	return title;
}

string Post::getAuthor()
{
	return author;
}

string Post::getDescription()
{
	return description;
}

ReplyList& Post::getReplies()
{
	return replyList;
}

void Post::setPostID(string pID)
{
	postID = pID;
}

void Post::setTopic(string topic)
{
	this->topic = topic;
}

void Post::setTitle(string title)
{
	this->title = title;
}

void Post::setAuthor(string author)
{
	this->author = author;
}

void Post::setDescription(string description)
{
	this->description = description;
}