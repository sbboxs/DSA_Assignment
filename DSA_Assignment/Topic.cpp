#include "Topic.h"

Topic::Topic()
{
	title = "";
	author = "";
}

Topic::Topic(string topic, string auth, PostList pList)
{
	title = topic;
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
	cout << "Title: " << title << endl;
	cout << "Author: " << author << endl;
	cout << "Post List: " << endl;
	postList.display();
}

string Topic::getTopic()
{
	return title;
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
	title = topic;
}

void Topic::setAuthor(string author)
{
	this->author = author;
}