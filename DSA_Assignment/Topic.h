#pragma once
// Topic.h - Definition of Topic class

#include<string>
#include<iostream>
#include "Post.h"
#include "PostList.h"

using namespace std;

class Topic
{
private:
	string title;
	string author;
	PostList postList;

public:

	//Methods 
	Topic();
	Topic(string topic, string author);
	void addPost(Post& post, PostList& postList);
	void deletePost(Post& post, PostList& postList);
	void print();

	//Getter
	string getTopic();
	string getAuthor();
	PostList& getPosts();

	//Setter
	void setTopic(string topic);
	void setAuthor(string author);

};

