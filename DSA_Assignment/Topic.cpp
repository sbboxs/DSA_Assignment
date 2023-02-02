#include "Topic.h"

Topic::Topic()
{
	topic = "";
	author = "";
}

Topic::Topic(string t, string auth, PostList pList)
{
	topic = t;
	author = auth;
	postList = pList;
}

void Topic::addPost(Post& post, PostList& postList)
{
	postList.add(post);
}

//void Topic::deletePost(Post& post, PostList& postList)
//{
//	postList.deletePost(post);
//}

void Topic::print()
{
	cout << "Title: " << topic << endl;
	cout << "Author: " << author << endl;
	cout << "Post List: " << endl;
	postList.display();
}

string Topic::getTopic()
{
	return topic;
}

string Topic::getAuthor()
{
	return author;
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