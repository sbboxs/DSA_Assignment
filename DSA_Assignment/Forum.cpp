//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
// Customer.cpp - Implementation of Customer class
#include "Forum.h"
#include "Topic.h"

Forum::Forum() {}

Forum::Forum(string t, TopicList tList)
{
	title = t;
	topicList = tList;
}


