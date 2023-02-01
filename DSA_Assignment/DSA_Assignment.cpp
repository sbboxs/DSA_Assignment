//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "User.h"
#include "Dictionary.h"
#include "Topic.h"
#include "TopicList.h"
#include "Post.h"
#include "PostList.h"


using namespace std;

void loadUserData();
void saveUserData(User& newUser);
void loadForumData();
void saveTopicData(Topic& newTopic);
void savePostData(Post& newPost);
void saveReplyData();
void displayHome();
void loginForm();
bool loginProcess();
void registerForm();
void registerProcess();
void userHome();
bool userHomeProcess();
void viewTopicNPost();
void viewTopicNPostProcess();
void createPostForm(Post& newPost);
void createPostFormProcess();
void topicSelector();
void topicSelectorProcess(string& topic);
void topicCreated();

//===
//Global variables
Dictionary userDictionary;
User currentUser;
TopicList topicList;
PostList postList;

//===
//File I/O, for data reading & writting with file
ifstream inFile;
ofstream outFile;
string str;

int main()
{
	//Initialize the program
	User newUser1("test", "test", false);
	userDictionary.add(newUser1.getUserName(),newUser1);
	userDictionary.print();

	//Load all needed data
	loadUserData();
	loadForumData();

	//Controlling of Login & Registration
	bool ifLogin = false;
	string option = "1";
	while (option != "0") {
		if (ifLogin)
			ifLogin = userHomeProcess();
		else {
			displayHome();
			cin >> option;
			//Login
			if (option == "1"){
				system("cls");
				ifLogin = loginProcess();
			}
			else if (option == "2") {
				system("cls");
				registerProcess();
			}
			else if (option == "0")
				cout << "Bye! " << endl;

			else {
				system("cls");
				cout << "Sorry. You have entered an invalid option." << endl;
			}
		}
		
	}
}

//=========
//This function is to load all the user data and store into the userDicionary. 
void loadUserData() {
	inFile.open("user.txt");
	if (inFile.fail()) {
		cout << "No user data exist!" << endl;
		cout << "Creating user data file..." << endl;
		ofstream outFile;
		outFile.open("user.txt");
		outFile.close();
	}
	else {
		string username, password;
		bool loginStatus;
		while (!inFile.eof()) {
			getline(inFile, str);
			stringstream ss(str);
			getline(ss, username, ';');
			getline(ss, password, ';');
			ss >> loginStatus;
			User loadUser(username, password, loginStatus);
			userDictionary.add(username, loadUser);
		}
		inFile.close();
		cout << "User data is loaded!" << endl;
	}
}

//=========
//This function is to save user data into the file. The newest user data will be appended to the end of the file.
//The user is the parameter.
void saveUserData(User& newUser) {
	string username = newUser.getUserName();
	string password = newUser.getPassword();
	bool loginStatus = newUser.getIsLogin();
	//Second flag 'ios::app' allows to open the file in append mode.
	//Therefore, there no need to overwritten the file everytime when save.
	//Newest data will just be appended at the end of the file.
	outFile.open("user.txt", ios::app);
	if (outFile.fail()) {
		cout << endl << "No user data file is found!" << endl;
		cout << endl << "Creating user data file..." << endl;
		ofstream outFile;
		outFile.open("user.txt");
		outFile << username << ";" << password << ";" << loginStatus << endl;
		outFile.close();
		cout << "User data is saved!" << endl;
	}
	else {
		outFile << username << ";" << password << ";" << loginStatus << endl;
		outFile.close();
		cout << "User data is saved!" << endl;
	}
}

void loadForumData() {
	//Loading topic data
	inFile.open("topic.txt");
	if (inFile.fail()) {
		cout << "No topic is exist!" << endl;
		cout << "Creating topic file..." << endl;
		ofstream outFile;
		outFile.open("topic.txt");
		outFile.close();
	}
	else {
		string title, author;
		PostList pList;
		while (!inFile.eof()) {
			getline(inFile, str);
			stringstream ss(str);
			getline(ss, title, ';');
			getline(ss, author, ';');
			Topic newTopic(title, author, pList);
			topicList.add(newTopic);
		}
		inFile.close();
		cout << "Topic data is loaded!" << endl;
	}
	//Load post data

	//load reply data
}
void saveTopicData() {

}

void savePostData() {

}

void saveReplyData() {

}

//=========
//This function is to print the layout of the homepage. Do not have any input parameters and return value.
void displayHome() {
	cout << endl;
	cout << "Welcome to Ngee Ann Discussion Forum!" << endl;
	cout << "-------------------------------------" << endl;
	cout << "[1] Have an account? Login!" << endl;
	cout << "[2] New to here? Register an account!" << endl;
	cout << "[0] Quit the application." << endl;
	cout << "Enter option: ";
}

//=========
//This function is to print the layout of login form. Do not have any input parameters and return value.
void loginForm() {
	cout << endl;
	cout << "Login Place!" << endl;
	cout << "-------------------------" << endl;
	cout << "[1] Key in login credentials. " << endl;
	cout << "[0] Back to login." << endl;
	cout << "Enter option: ";
}

//=========
//This function is to control the flow of login form & will return true if success login else return false 
//The user can perform logging in into their account by inputing the username and password.
//The user can also perform back to home page.
bool loginProcess() {
	string loginOption = "1";
	string promptUsername = "";
	string promptPwd = "";

	while (loginOption != "0") {
		loginForm();
		cin >> loginOption;
		//Key in login credentials
		if (loginOption == "1") {
			cout << "Your username: ";
			cin >> promptUsername;
			cout << "Your password: ";
			cin >> promptPwd;
			if (promptUsername != "" && promptPwd != "") {
				User loginUser = userDictionary.get(promptUsername);
				if (loginUser.checkPassword(promptPwd)) {
					currentUser = loginUser;
					cout << "Login Success!" << endl;
					system("pause");
					system("cls");
					return true;
				}
				else {
					cout << "Login credentials invalid!" << endl;
					system("pause");
				}
			}
			else
				cout << "Please fill in username and password" << endl;
		}
		else if (loginOption == "0") {
			system("cls");
			cout << "Has back to home. ";
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
	}
	return false;
}

//=========
//This function print the layout of the register form. Do not have any input parameters and return value.
void registerForm() {
	cout << endl;
	cout << "Registration Place!" << endl;
	cout << "-----------------------" << endl;
	cout << "[1] Key in registration credentials: " << endl;
	cout << "[0] Back to login." << endl;
	cout << "Enter option: ";
}

//=========
//This function control the flow of register form.
//The user can perform registering account by inputing the "Unique" username, password and confirm his password.
//The user can also perform back to home page.
void registerProcess() {
	string registerOption = "1";
	string newUsername;
	string newPassword;
	string checkPassword;
	User existUser;
	while (registerOption != "0") {
		registerForm();
		cin >> registerOption;
		if (registerOption == "1") {
			while (true) {
				cout << "Enter Username: ";
				cin >> newUsername;
				existUser = userDictionary.get(newUsername);
				if (existUser.getUserName() != newUsername)
					break;
				else
					cout << "Username is exist! Please enter another unique username." << endl;
			}
			
			while (true) {
				cout << "Enter Password: ";
				cin >> newPassword;
				cout << "Confirm your password: ";
				cin >> checkPassword;
				if (newPassword == checkPassword) {
					User newUser(newUsername, newPassword, false);
					if (userDictionary.add(newUsername, newUser)) {
						saveUserData(newUser);
						cout << "Account is created successfully! ";
						system("pause");
						system("cls");
						break;
					}
					else
						cout << "Save Error!." << endl;
				}
				else {
					cout << "Password is not matched." << endl;
				}
			}
		} 
		else if (registerOption == "0") {
			system("cls");
			cout << "Has back to home. ";
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
	}
}

//=========
//This function print the layout of the user home. Do not have any input parameters and return value.
void userHome() {
	cout << endl;
	cout << "Welcome back! Dear user: " << currentUser.getUserName() << endl;
	cout << "---------------------------" << endl;
	cout << "[1] View all topics and posts " << endl;
	cout << "[2] View my posts" << endl;
	cout << "[3] Create new posts" << endl;
	cout << "[0] Logout" << endl;
	cout << "Enter option: ";
}

//=========
//This function control the flow of user home, will return false if logout else true if login
//The user can perform view topics and posts, view his post and create new post.
//The user can also perform logout to main home page.
//bool userHomeProcess() {
//	string option = "1";
//	while (option != "0") {
//		userHome();
//		cin >> option;
//		if (option == "1"){
//			viewTopicNPostProcess();
//		}
//		else if (option == "2") {
//			cout << "My posts" << endl;
//		}
//		else if (option == "3") {
//			cout << "Create new posts" << endl;
//		}
//		else if (option == "0") {
//			system("cls");
//			cout << "Has logged out. ";
//			return false;
//		}
//		else {
//			system("cls");
//			cout << "Sorry. You have entered an invalid option." << endl;
//		}
//	}
//	return true;
//}

//void viewTopicNPost() {
//	cout << endl;
//	cout << "C++ Programming Forum" << endl;
//	cout << "---------------------------" << endl;
//	if (postList.isEmpty())
//		cout << "No post yet" << endl;
//	else
//		postList.display();
//
//	cout << "You are now viewing all topics and posts" << endl;
//	cout << "[1] Search by topics, posts or users " << endl;
//	cout << "[2] View a post" << endl;
//	cout << "[3] Next page" << endl;
//	cout << "[4] Create new posts" << endl;
//	cout << "[0] Back to user home" << endl;
//	cout << "Enter option: ";
//}
//
//void viewTopicNPostProcess() {
//	string option = "1";
//	while (option != "0") {
//		viewTopicNPost();
//		cin >> option;
//		if (option == "1") {
//			cout << "Search by topics, posts or users" << endl;
//		}
//		else if (option == "2") {
//			cout << "View a post" << endl;
//		}
//		else if (option == "3") {
//			cout << "Next page" << endl;
//		}
//		else if (option == "4") {
//			cout << "Create new posts" << endl;
//		}
//		else if (option == "0") {
//			system("cls");
//			cout << "Back to user home. ";
//		}
//		else {
//			system("cls");
//			cout << "Sorry. You have entered an invalid option." << endl;
//		}
//	}
//}

//void createPostForm(Post& newPost) {
//	cout << endl;
//	cout << "Creating new post!" << endl;
//	cout << "---------------------------" << endl;
//	cout << "[1] Select a topic: " << newPost.getTopic() << endl;
//	cout << "[2] Enter title of post: " << newPost.getTitle() << endl;
//	cout << "[3] Enter description of post: " <<newPost.getDescription() << endl;
//	cout << "[0] Back" << endl;
//	cout << "Enter option: ";
//}
//
//void createPostFormProcess() {
//	string postID, topic, title, description, author;
//	Post newPost(postID, topic, title, author ,description);
//	string option = "1";
//	while (option != "0") {
//		createPostForm(newPost);
//		cin >> option;
//		if (option == "1") {
//			cout << "Select a topic" << endl;
//		}
//		else if (option == "2") {
//			cout << "Enter title: ";
//			cin >> title;
//			system("cls");
//			cout << "Title has entered." << endl;
//		}
//		else if (option == "3") {
//			cout << "Enter description: " << endl;
//			cin >> description;
//			system("cls");
//			cout << "Description has entered" << endl;
//		}
//		else if (option == "4") {
//			cout << "Create new posts" << endl;
//			if (postList.add(newPost)) {
//				savePostData(newPost);
//				cout << "New post is created succesfully!" << endl;
//				break;
//			}
//			else
//				cout << "Saved Error!" << endl;
//		}
//		else if (option == "0") {
//			system("cls");
//			cout << "Back to user home. ";
//		}
//		else {
//			system("cls");
//			cout << "Sorry. You have entered an invalid option." << endl;
//		}
//	}
//}

//void topicSelector() {
//	topicList.display();
//	cout << endl;
//	cout << "[1]Select a topic" << endl;
//	cout << "[2]Create a new topic" << endl;
//	cout << "[0]Back" << endl;
//}
//
//void topicSelectorProcess(string& topic) {
//	string option = "1";
//	int index;
//	while (option != "0") {
//		topicSelector();
//		cin >> option;
//		if (option == "1") {
//			cout << "Enter topic index: " << endl;
//			cin >> index;
//			topic = topicList.get(index).getTopic();
//			system("cls");
//			cout << "Topic has selected." << endl;
//			break;
//		}
//		else if (option == "2") {
//			cout << "Create new topic. " << endl;
//		}
//		else if (option == "0") {
//			system("cls");
//			cout << "Back to create new post. ";
//		}
//		else {
//			system("cls");
//			cout << "Sorry. You have entered an invalid option." << endl;
//		}
//	}
//}