

// Customer.cpp - Implementation of Customer class
#include "Reply.h"

Reply::Reply() {}

Reply::Reply(string message, string auth, string date)
{
	replyMessage = message;
	author = auth;
	replyDate = date;
}


