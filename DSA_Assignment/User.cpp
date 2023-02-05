//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include "User.h"
#include "Topic.h"
#include "TopicList.h"
User::User() {
    userName = "";
    password = "";
    isLogin = false;
}

User::User(string u, string p, bool islogin) {
    userName = u;
    password = p;
    isLogin = islogin;
}

//Getter
string User::getUserName() {
    return userName;
}

string User::getPassword() {
    return password;
}

bool User::getIsLogin() {
    return isLogin;
}

//Setter
void User::setUserName(string name)
{
    userName = name;
}
void User::setPassword(string pwd)
{
    password = pwd;
}
void User::setIsLogin(bool login)
{
    isLogin = login;
}

bool User::checkPassword(string keyPassword) {
    return (keyPassword == password);
}


void User::print() {
    cout << "User name: " << userName << endl;
    cout << "Password: " << password << endl;
    cout << "Is login: " << isLogin << endl;
}




