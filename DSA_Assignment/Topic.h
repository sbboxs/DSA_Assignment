
#pragma once
// Topic.h - Definition of Topic class

#include<string>
#include<iostream>
#include "PostList.h"


using namespace std;


class Topic
{
private:
	string title;
	PostList postList;

public:
	Topic();
	Topic(string t, PostList pList);
};

