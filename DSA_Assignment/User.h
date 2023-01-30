#pragma once
#include <string>
#include <iostream>
using namespace std;
class User
{
private:
	string userName;
	string password;
	bool isLogin;
public:
	User();
	User(string u, string p, bool islogin);
	string getUserName();
	string getPassword();
	void setUserName(string name);
	void setPassword(string pwd);
	void setIsLogin(bool login);
	bool getIsLogin();
	void print();
};

