//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include "Post.h"

Post::Post()
{
	message = "";
	topic = "";
	title = "";
	author = "";
	description = "";
}

Post::Post(string t, string desc, string msg, string user, string top)
{
	message = msg;
	topic = top;
	title = t;
	author = user;
	description = desc;
}



void Post::print()
{
	cout << "Topic: " << endl << title.c_str() << endl;;
	cout << "----------------------------------------------------------------------------------" << endl;
	cout << "Description: " << endl << description << endl;;
	cout << "----------------------------------------------------------------------------------" << endl;
	cout << "@" << author.c_str() << endl << message << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
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