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
	string replyDate;

public:
	//Methods
	Reply();
	Reply(string message,string auth, string date);
	void print();

	//Getter
	string getReplyMessage();
	string getAuthor();
	string getReplyDate();
};


