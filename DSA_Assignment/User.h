#pragma once
#include <string>
#include <iostream>
#include "Post.h"
#include "Reply.h"
#include "Topic.h"
#include "PostList.h"
#include "TopicList.h"
#include "ReplyList.h"
using namespace std;

class User
{
private:
	string userName;
	string password;
	bool isLogin;

public:
	//Methods
	User();
	User(string u, string p, bool islogin);
	bool checkPassword(string Keypassword);
	void print();

	//Getter
	string getUserName();
	string getPassword();
	bool getIsLogin();

	//Setter
	void setUserName(string name);
	void setPassword(string pwd);
	void setIsLogin(bool login);
	

};

