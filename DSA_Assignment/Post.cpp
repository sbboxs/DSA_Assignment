#include "Post.h"

Post::Post()
{
	message = "";
	topic = "";
	title = "";
	author = "";
	description = "";
}

Post::Post(string msg, string top, string t, string user, string desc)
{
	message = msg;
	topic = top;
	title = t;
	author = user;
	description = desc;
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
	cout << "Message: " << message << endl;
	cout << "Topic: " << topic << endl;
	cout << "Title: " << title << endl;
	cout << "Author: " << author << endl;
	cout << "Description: " << description << endl;
}

string Post::getMessage()
{
	return message;
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

void Post::setMessage(string msg)
{
	this->message = msg;
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