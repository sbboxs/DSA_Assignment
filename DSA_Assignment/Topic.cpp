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
	totalPost = 0;
}

Topic::Topic(string t, string auth, int tPost)
{
	topic = t;
	author = auth;
	totalPost = tPost;
}

bool Topic::addPost(Post& post)
{

	return postList.add(post);
}

//void Topic::deletePost(Post& post, PostList& postList)
//{
//	postList.deletePost(post);
//}

void Topic::print()
{
	cout << left << setw(25) << "Topic"
		<< setw(25) << "Created By" << setw(25) << "Total Post" << endl;
	cout << left << setw(25) << topic
		<< setw(25) << author << setw(25) << totalPost << endl;
}

string Topic::getTopic()
{
	return topic;
}

string Topic::getAuthor()
{
	return author;
}
int Topic::getTotalPost() {
	return totalPost;
}
PostList& Topic::getPosts()
{
	return postList;
}

void Topic::setTopic(string topic)
{
	this->topic = topic;
}

void Topic::setAuthor(string author)
{
	this->author = author;
}

void Topic::setTotalPost(int totalPost) {
	this->totalPost = totalPost;
}
