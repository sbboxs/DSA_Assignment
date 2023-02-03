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
void loadTopicData();
void saveTopicData(Topic& newTopic);
void loadPostData();
void savePostData(Post& newPost);
void saveReplyData();
void displayHome();
void loginForm();
bool loginProcess();
void registerForm();
void registerProcess();
void userHome();
bool userHomeProcess();
bool displayTopics();
bool displayUserTopics();
bool displayUserPosts();
void displayATopic(int topicID);
void viewTopicNPost();
void viewTopicNPostProcess(Topic aTopic);
void createPost();
void createTopic();
void createPostFormProcess();
void topicSelector();
void topicSelectorProcess(string& topic);
void topicCreated();

//===
//Global variables
Dictionary userDictionary;
User currentUser;
TopicList topicList;
Topic currentTopic;

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
	loadTopicData();

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

void loadTopicData() {
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
	//load reply data
}

void loadPostData() {
	//Load post data
	string filename = "topic_" + currentTopic.getTopic() + "_Postdata.txt";
	inFile.open(filename);
	if (inFile.fail()) {
		cout << "No post is exist!" << endl;
		cout << "Creating post file..." << endl;
		ofstream outFile;
		outFile.open(filename);
		outFile.close();
	}
	else {
		string postID,topic,title, author, description;
		while (!inFile.eof()) {
			getline(inFile, str);
			stringstream ss(str);
			getline(ss, postID, ';');
			getline(ss, topic, ';');
			getline(ss, title, ';');
			getline(ss, author, ';');
			getline(ss, description, ';');
			Post newPost(postID, topic, title, author, description);
			currentTopic.addPost(newPost);
		}
		inFile.close();
		cout << "Post data is loaded!" << endl;
	}
}
void saveTopicData(Topic& newTopic) {
	string topic = newTopic.getTopic();
	string author = newTopic.getAuthor();
	outFile.open("topic.txt", ios::app);
	if (outFile.fail()) {
		cout << endl << "No topic data file is found!" << endl;
		cout << endl << "Creating topic data file..." << endl;
		ofstream outFile;
		outFile.open("topic.txt");
		outFile << topic << ";" << author << endl;
		outFile.close();
		cout << "Topic data is saved!" << endl;
	}
	else {
		outFile << topic << ";" << author << endl;
		outFile.close();
		cout << "Topic data is saved!" << endl;
	}
}

void savePostData(Post& newPost) {
	string postID = newPost.getPostID();
	string topic = newPost.getTopic();
	string postTitle = newPost.getTitle();
	string author = newPost.getAuthor();
	string postDescription = newPost.getDescription();
	//Second flag 'ios::app' allows to open the file in append mode.
	//Therefore, there no need to overwritten the file everytime when save.
	//Newest data will just be appended at the end of the file.
	string filename = "topic_" + currentTopic.getTopic() + "_PostData.txt";
	//string filename = "topic_" + currentTopic.getTopic() + "_post_" + newPost.getPostID() + ".txt";
	outFile.open(filename, ios::app);
	if (outFile.fail()) {
		cout << endl << "No post data file is found!" << endl;
		cout << endl << "Creating post data file..." << endl;
		ofstream outFile;
		outFile.open(filename);
		outFile << postID << ";" << topic << " " << postTitle << ";" << author << ";" << postDescription << endl;
		outFile.close();
		cout << "Post data is saved!" << endl;
	}
	else {
		outFile << postID << ";" << topic << " " << postTitle << ";" << author << ";" << postDescription << endl;
		outFile.close();
		cout << "Post data is saved!" << endl;
	}
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
	cout << "-------------------------------------" << endl;
	cout << "Enter option: ";
}

//=========
//This function is to print the layout of login form. Do not have any input parameters and return value.
void loginForm() {
	cout << endl;
	cout << "Login Place!" << endl;
	cout << "----------------------------" << endl;
	cout << "[1] Key in login credentials. " << endl;
	cout << "[0] Back to login." << endl;
	cout << "----------------------------" << endl;
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
			cout << "----------------------------" << endl;
			cout << "Username: ";
			cin >> promptUsername;
			cout << "Password: ";
			cin >> promptPwd;
			if (promptUsername != "" && promptPwd != "") {
				User loginUser = userDictionary.get(promptUsername);
				if (loginUser.checkPassword(promptPwd)) {
					currentUser = loginUser;
					cout << "----------------------------" << endl;
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
	cout << "-----------------------" << endl;
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
	cout << "[1] Dicussion Topics " << endl;
	cout << "[2] Create New Topic" << endl;
	cout << "[3] My Posts" << endl;
	cout << "[0] Logout" << endl;
	cout << "---------------------------" << endl;
	cout << "Enter option: ";
}
//=========
//This function control the flow of user home, will return false if logout else true if login
//The user can perform view topics and posts, view his post and create new post.
//The user can also perform logout to main home page.
bool userHomeProcess() {
	string option = "1";
	while (option != "0") {
		userHome();
		cin >> option;
		if (option == "1"){
			system("cls");
			displayTopics();
		}
		else if (option == "2") {
			system("cls");
			createTopic();
		}
		else if (option == "3") {
			system("cls");
			displayUserPosts();
		}
		else if (option == "0") {
			system("cls");
			cout << "Has logged out. ";
			return false;
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
	}
	return true;
}

bool displayTopics() {
	string option = "1";
	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "--------------------------------------------------------------" << endl;
		topicList.display("");
		cout << "--------------------------------------------------------------" << endl;

		cout << "[1] View a Topic " << endl;
		cout << "[2] My Topics" << endl;
		cout << "[0] Back to user home" << endl;
		cout << "---------------------" << endl;
		cout << "Enter option: ";
		cin >> option;
		if (option == "1") {
			int topicID;
			cout << "Enter ID: " ;
			cin >> topicID;
			system("cls");
			displayATopic(topicID);
		}
		else if (option == "2") {
			system("cls");
			displayUserTopics();
		}
		else if (option == "3") {
			system("cls");
		}
		else if (option == "0") {
			system("cls");
			cout << "Has logged out. ";
			return false;
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
	}
	return true;
}

void viewTopicNPost() {
	cout << endl;
	cout << "You are now viewing all topics and posts" << endl;
	cout << "[1] Search by topics, posts or users " << endl;
	cout << "[2] View a post" << endl;
	cout << "[3] Next page" << endl;
	cout << "[4] Create new posts" << endl;
	cout << "[0] Back to user home" << endl;
	cout << "Enter option: ";
}

bool displayUserTopics() {
	string option = "1";
	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "-------------------------------------------------------------" << endl;
		topicList.display(currentUser.getUserName());
		cout << "-------------------------------------------------------------" << endl;
		cout << "[1] Choose topic to view " << endl;
		cout << "[2] Delete a Topic" << endl;
		cout << "[0] Back to user home" << endl;
		cout << "Enter option: ";
		cin >> option;
		if (option == "1") {
			int topicID;
			cout << "Enter ID: ";
			cin >> topicID;
			system("cls");
			displayATopic(topicID);
		}
		else if (option == "2") {
			system("cls");
		}
		else if (option == "3") {
			cout << "Create new posts" << endl;
		}
		else if (option == "0") {
			system("cls");
			cout << "Has logged out. ";
			return false;
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
	}
	return true;
}

bool displayUserPosts() {
	string option = "1";
	TopicList userTList;
	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "--------------------------------------------------------" << endl;
		postList.userDisplay(currentUser.getUserName());

		cout << endl << "[1] View a Post " << endl;
		cout << "[2] Delete a Post" << endl;
		cout << "[0] Back to user home" << endl;
		cout << "Enter option: ";
		cin >> option;
		if (option == "1") {
			int topicID;
			cout << "Enter ID: ";
			cin >> topicID;
			system("cls");
			displayATopic(topicID);
		}
		else if (option == "2") {
			system("cls");
		}
		else if (option == "3") {
			cout << "Create new posts" << endl;
		}
		else if (option == "0") {
			system("cls");
			cout << "Has logged out. ";
			return false;
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
	}
	return true;
}

void displayATopic(int topicID) {
	string option = "1";
	currentTopic = topicList.get(topicID-1);
	loadPostData();

	while (option != "0") {
		cout << "Topic: " << currentTopic.getTopic() << endl;
		cout << "---------------------------" << endl;
		currentTopic.getPosts().display();
		cout << "----------------------------------------------------------" << endl;
		postList.display();
		viewTopicNPost();
		cin >> option;
		if (option == "1") {
			cout << "Search by topics, posts or users" << endl;
		}
		else if (option == "2") {
			cout << "View a post" << endl;
		}
		else if (option == "3") {
			cout << "Next page" << endl;
		}
		else if (option == "4") {
			cout << "Create new posts" << endl;
			createPost();
			system("cls");
			
		}
		else if (option == "0") {
			system("cls");
			cout << "Back to user home. ";
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
	}
}
//void createPostForm(Post& newPost) {
//	cout << endl;
//	cout << "Creating new post!" << endl;
//	cout << "---------------------------" << endl;
//	cout << "[1] Select a topic: " << newPost.getTopic() << endl;
//	cout << "[2] Enter title of post: " << newPost.getTitle() << endl;
//	cout << "[3] Enter description of post: " << newPost.getDescription() << endl;
//	cout << "[0] Back" << endl;
//	cout << "Enter option: ";
//}
void createPost() {
	cout << endl;
	string postID, title, description;
	postID = currentUser.getUserName() +"_" + to_string(currentTopic.getPosts().getLength());
	string message, title, description;
	Post newPost;
	cout << "Creating new post!" << endl;
	cout << "------------------" << endl;
	cout << "Title: ";
	cin >> title;
	cout << "Description: " << endl;
	cin >> description;
	Post newPost(postID, currentTopic.getTopic(), title, currentUser.getUserName(), description);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, title);
	newPost.setTitle(title);
	cout << "Description of Post: " << endl;
	getline(cin, description);
	newPost.setDescription(description);
	cout << "Post your message here: " << endl;
	getline(cin, message);
	newPost.setMessage(message);
	newPost.setTopic(currentTopic.getTopic());
	newPost.setAuthor(currentUser.getUserName());
	if (currentTopic.addPost(newPost)) {
		savePostData(newPost);
		cout << "New post is created succesfully!" << endl;
	}
	else
		cout << "Saved Error!" << endl;
}

void createTopic() {
	cout << endl;
	string title;
	PostList pList;
	cout << "Creating new Topic!" << endl;
	cout << "------------------" << endl;
	cout << "Naame of Topic: ";
	cin >> title;
	Topic newTopic(title, currentUser.getUserName(), pList);
	if (topicList.add(newTopic)) {
		saveTopicData(newTopic);
		cout << "New Topic is created succesfully!" << endl;
	}
	else
		cout << "Saved Error!" << endl;
}
//void createPostFormProcess() {
//	string postID, topic, title, description, author;
//	Post newPost(postID, topic, title, author ,description);
//	string option = "1";
//	createPostForm(newPost);
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