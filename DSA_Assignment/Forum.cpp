// Customer.cpp - Implementation of Customer class
#include "Forum.h"
#include "Topic.h"

Forum::Forum() {}

Forum::Forum(string t, TopicList tList)
{
	title = t;
	topicList = tList;
}


