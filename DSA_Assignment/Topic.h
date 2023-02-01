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
	Topic(string title, string author);
	void addPost(Post& post, PostList& postList);
	void deletePost(Post& post, PostList& postList);
	void print();

	//Getter
	string getTitle();
	string getUserName();
	PostList& getPosts();

	//Setter
	void setTitle(string title);
	void setAuthor(string author);

};

