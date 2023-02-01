
// Customer.cpp - Implementation of Customer class
#include "Topic.h"


Topic::Topic() {}

Topic::Topic(string topic, string auth, PostList pList)
{
	title = topic;
	author = auth;
	postList = pList;
}


