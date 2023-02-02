#include "Reply.h"

Reply::Reply()
{
	replyMessage = "";
	author = "";
	replyDate = "";
}

Reply::Reply(string message, string auth, string date)
{
	replyMessage = message;
	author = auth;
	replyDate = date;
}

void Reply::print()
{
	cout << "Reply Message: " << replyMessage << endl;
	cout << "Author: " << author << endl;
	cout << "Reply Date: " << replyDate << endl;
}

string Reply::getReplyMessage()
{
	return replyMessage;
}

string Reply::getAuthor()
{
	return author;
}

string Reply::getReplyDate()
{
	return replyDate;
}