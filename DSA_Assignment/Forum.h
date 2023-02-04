//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#pragma once
// Customer.h - Definition of Customer class

#include<string>
#include<iostream>
#include "TopicList.h"

using namespace std;

class Forum
{
private:
	string title;
	TopicList topicList; // the i-th minute Customer joins queue.

public:
	Forum();
	Forum(string t, TopicList tList);
};


