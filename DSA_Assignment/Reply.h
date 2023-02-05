//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
// Reply.h - Definition of Reply class
#pragma once
#include<string>
#include<iostream>

using namespace std;

class Reply
{
private:
	string replyMessage;
	string author;
	string topic;
	string postTitle;
	string date;

public:
	//Methods
	Reply();
	Reply(string message,string auth, string top, string title, string dateTime);
	void print();

	//Getter
	string getReply();
	string getAuthor();
	string getTopic();
	string getTitle();
	string getDate();


	void setReply(string reply);
	void setAuthor(string author);
	void setTopic(string topic);
	void setTitle(string title);
	void setDate(string date);
};


