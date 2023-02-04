#include "Reply.h"

Reply::Reply()
{
	replyMessage = "";
	author = "";
	topic = "";
	postTitle = "";
	date = "";
}

Reply::Reply(string message, string auth, string top, string title, string dateTime)
{
	replyMessage = message;
	author = auth;
	topic = top;
	postTitle = title;
	date = dateTime;
}

void Reply::print()
{
	cout << "Reply Message: " << replyMessage << endl;
	cout << "Author: " << author << endl;
	cout << "Reply Date: " << date << endl;
}

string Reply::getReply()
{
	return replyMessage;
}

string Reply::getAuthor()
{
	return author;
}

string Reply::getTopic()
{
	return topic;
}

string Reply::getTitle()
{
	return postTitle;
}

string Reply::getDate()
{
	return date;
}

void Reply::setReply(string reply)
{
	this->replyMessage = reply;
}

void Reply::setAuthor(string author)
{
	this->author = author;
}

void Reply::setTopic(string topic)
{
	this->topic = topic;
}

void Reply::setTitle(string title)
{
	this->postTitle = title;
}

void Reply::setDate(string date)
{
	this->date = date;
}