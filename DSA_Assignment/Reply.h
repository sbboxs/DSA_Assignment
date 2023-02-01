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


