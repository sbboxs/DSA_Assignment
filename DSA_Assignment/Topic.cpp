//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include "Topic.h"
#include <iomanip>

Topic::Topic()
{
	topic = "";
	author = "";
}

Topic::Topic(string t, string auth)
{
	topic = t;
	author = auth;
}

//void Topic::deletePost(Post& post, PostList& postList)
//{
//	postList.deletePost(post);
//}

void Topic::print()
{
	cout << left << setw(25) << "Topic"
		<< setw(25) << "Created By" << endl;
	cout << left << setw(25) << topic
		<< setw(25) << author << endl;
}

string Topic::getTopic()
{
	return topic;
}

string Topic::getAuthor()
{
	return author;
}


void Topic::setTopic(string topic)
{
	this->topic = topic;
}

void Topic::setAuthor(string author)
{
	this->author = author;
}

