//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include <string>
#include <iostream>
#include <time.h>  
#include <stdio.h> 
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
void updateTopicData();
void loadPostData();
void savePostData(Post& newPost);
void updatePostData();
void saveReplyData();
void displayHome();
void loginForm();
bool loginProcess();
void registerForm();
void registerProcess();
void userHome();
bool userHomeProcess();
void userTopicMenu();
bool userTopicMenuProcess();
void forumMenu();
bool forumMenuProcess();;
void userPostMenu();
bool userPostMenuProcess();
void displayAPost(int postID);
void displayATopic(int topicID);
void topicMenu();
bool topicMenuProcess(Topic currentTopic);
bool postMenuProcess(Post currentPost);
void postMenu();
bool replyMenuProcess(Post currentPost);
void createReply(Post post);
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
PostList postList;
ReplyList replyList;
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
	loadPostData();

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
	//Second flag 'ios::app' allows to open the file in append mode.
	//Therefore, there no need to overwritten the file everytime when save.
	//Newest data will just be appended at the end of the file.
	outFile.open("user.txt", ios::app);
	if (outFile.fail()) {
		cout << endl << "No user data file is found!" << endl;
		cout << endl << "Creating user data file..." << endl;
		ofstream outFile;
		outFile.open("user.txt");
		outFile << newUser.getUserName() << ";" << newUser.getPassword() << ";" << newUser.getIsLogin() << endl;
		outFile.close();
		cout << "User data is saved!" << endl;
	}
	else {
		outFile << newUser.getUserName() << ";" << newUser.getPassword() << ";" << newUser.getIsLogin() << endl;
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
		string topic, author;
		while (getline(inFile, str) && str != "") {
			stringstream ss(str);
			getline(ss, topic, ';');
			getline(ss, author, ';');
			Topic currentTopic(topic, author);
			topicList.add(currentTopic);
		}
		inFile.close();
		cout << "Topic data is loaded!" << endl;
	}
}

void loadPostData() {
	//Load post data
	/*string filename = "topic_" + currentTopic.getTopic() + "_Postdata.txt";*/
	string filename = "post.txt"; 
	inFile.open(filename);
	if (inFile.fail()) {
		cout << "No post is exist!" << endl;
		cout << "Creating post file..." << endl;
		ofstream outFile;
		outFile.open(filename);
		outFile.close();
	}
	else {
		string message,topic,title, author, description;
		while (getline(inFile, str) && str != "") {
			stringstream ss(str);
			getline(ss, title, ';');
			getline(ss, description, ';');
			getline(ss, message, ';');
			getline(ss, author, ';');
			getline(ss, topic, ';');
			Post currentPost(title, description, message, author, topic);
			postList.add(currentPost);
		}
		inFile.close();
		cout << "Post data is loaded!" << endl;
	}
}

void saveTopicData(Topic& newTopic) {
	outFile.open("topic.txt", ios::app);
	if (outFile.fail()) {
		cout << endl << "No topic data file is found!" << endl;
		cout << endl << "Creating topic data file..." << endl;
		ofstream outFile;
		outFile.open("topic.txt");
		outFile << newTopic.getTopic() << ";" << newTopic.getAuthor() << endl;
		outFile.close();
		cout << "Topic data is saved!" << endl;
	}
	else {
		outFile << newTopic.getTopic() << ";" << newTopic.getAuthor() << endl;
		outFile.close();
		cout << "Topic data is saved!" << endl;
	}
}

void savePostData(Post& newPost) {
	//Second flag 'ios::app' allows to open the file in append mode.
	//Therefore, there no need to overwritten the file everytime when save.
	//Newest data will just be appended at the end of the file.
	string filename = "post.txt";
	//string filename = "topic_" + currentTopic.getTopic() + "_post_" + newPost.getPostID() + ".txt";
	outFile.open(filename, ios::app);
	if (outFile.fail()) {
		cout << endl << "No post data file is found!" << endl;
		cout << endl << "Creating post data file..." << endl;
		ofstream outFile;
		outFile.open(filename);
		outFile << newPost.getTitle() << ";" << newPost.getDescription() << ";" << newPost.getMessage() << ";" << newPost.getAuthor() << ";" << newPost.getTopic() << endl;
		outFile.close();
		cout << "Post data is saved!" << endl;
	}
	else {
		outFile << newPost.getTitle() << ";" << newPost.getDescription() << ";" << newPost.getMessage() << ";" << newPost.getAuthor() << ";" << newPost.getTopic() << endl;
		outFile.close();
		cout << "Post data is saved!" << endl;
	}
}

void saveReplyData() {

}

void updateTopicData() {
	Topic currentTopic;
	outFile.open("topic.txt");
	if (outFile.fail()) {
		cout << endl << "No topic data file is found!" << endl;
		cout << endl << "Creating topic data file..." << endl;
	}
	for (int i = 0; i < topicList.getLength(); i++) {
		currentTopic = topicList.get(i);
		outFile << currentTopic.getTopic() << ";" << currentTopic.getAuthor() << endl;
	}
	outFile.close();
	cout << "Topic data is updated!" << endl;
}
void updatePostData() {
	Post currentPost;
	outFile.open("post.txt");
	if (outFile.fail()) {
		cout << endl << "No post data file is found!" << endl;
		cout << endl << "Creating post data file..." << endl;
	}
	for (int i = 0; i < postList.getLength(); i++) {
		currentPost = postList.get(i);
		outFile << currentPost.getTitle() << ";" << currentPost.getDescription() << ";" << currentPost.getMessage() << ";" << currentPost.getAuthor() << ";" << currentPost.getTopic() << endl;
	}
	outFile.close();
	cout << "Post data is updated!" << endl;
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
	cout << "[2] View my topics" << endl;
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
			forumMenuProcess();;
		}
		else if (option == "2") {
			system("cls");
			userTopicMenuProcess();
		}
		else if (option == "0") {
			system("cls");
			cout << "Has logged out. ";
			return false;
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl << endl;;
		}
	}
	return true;
}
void userTopicMenu() {
	cout << "C++ Programming Forum" << endl;
	cout << "--------------------------------" << endl;
	topicList.userDisplay(currentUser.getUserName());
	cout << "--------------------------------" << endl;
	cout << "[1] Choose topic to view " << endl;
	cout << "[2] Create New Topic" << endl;
	cout << "[3] Delete a Topic" << endl;
	cout << "[0] Back to user home" << endl;
	cout << "Enter option: ";
}
bool userTopicMenuProcess() {
	string option = "1";
	userTopicMenu();
	while (option != "0") {
		cin >> option;
		if (option == "1") {
			int topicID;
			cout << "Enter ID: ";
			cin >> topicID;
			system("cls");
			displayATopic(topicID);
		}
		else if (option == "2") {
			createTopic();
		}
		else if (option == "3") {
			int topicID;
			string confirmDelete;
			Topic topicDeleted;
			cout << "Enter Topic ID to be deleted: ";
			cin >> topicID;
			if (topicID - 1001 < topicList.getLength() && topicID - 1001 >= 0) {
				topicDeleted = topicList.get(topicID - 1001);
				if (topicDeleted.getAuthor() == currentUser.getUserName()) {
					cout << "Do you sure want to remove topic index of " << topicID << "? (Y/N): ";
					cin >> confirmDelete;
					if (confirmDelete == "Y" || confirmDelete == "y")
					{
						topicList.remove(topicID - 1001);

						for (int i = 0; i < postList.getLength(); i++) {
							Post currentPost = postList.get(i);
							if (currentPost.getTopic() == topicDeleted.getTopic())
								postList.remove(i);
						}
						updateTopicData();
						updatePostData();
						system("cls");
						cout << topicDeleted.getTopic() << " is deleted." << endl;
					}
				}
				else {
					system("cls");
					cout << "You do not have the permission to delete other user' topic" << endl;
				}

			}
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
void forumMenu() {
	cout << "[1] View a Topic " << endl;
	cout << "[2] Create New Topic" << endl;
	cout << "[3] View my posts" << endl;
	cout << "[0] Back to user home" << endl;
	cout << "---------------------" << endl;
	cout << "Enter option: ";
}
bool forumMenuProcess() {
	string option = "1";
	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "--------------------------------------------------------------" << endl;
		topicList.display();
		cout << "--------------------------------------------------------------" << endl;
		forumMenu();
		cin >> option;
		if (option == "1") {
			int topicID;
			cout << "Enter ID: " ;
			cin >> topicID;
			system("cls");
			if (topicID - 1001 < topicList.getLength() && topicID - 1001 >= 0)
				displayATopic(topicID);
			else
			{
				system("cls");
				cout << "Invalid Topic ID." << endl;
			}
		}
		else if (option == "2") {
			createTopic();
		}
		else if (option == "3") {
			system("cls");
			userPostMenuProcess();
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

void topicMenu() {
	cout << endl;
	cout << "[1] Search by topics, posts or users " << endl;
	cout << "[2] View a post" << endl;
	cout << "[3] Next page" << endl;
	cout << "[4] Create new posts" << endl;
	cout << "[4] My replies" << endl;
	cout << "[0] Back to user home" << endl;
	cout << "Enter option: ";
}

bool topicMenuProcess(Topic currentTopic) {
	string option = "1";

	while (option != "0") {
		cout << "Topic: " << currentTopic.getTopic() << endl;
		cout << "---------------------------" << endl;
		postList.topicDisplay(currentTopic.getTopic());
		cout << "----------------------------------------------------------" << endl;
		topicMenu();
		cin >> option;
		if (option == "1") {
			cout << "Search by topics, posts or users" << endl;
		}
		else if (option == "2") {
			int postID;
			cout << "Enter ID: ";
			cin >> postID;
			system("cls");
			displayAPost(postID);
		}
		else if (option == "3") {
			cout << "Next page" << endl;
		}
		else if (option == "4") {
			createPost();

		}
		else if (option == "0") {
			system("cls");
			cout << "Back to user home. ";
			return false;
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
		return true;
	}
}

void displayATopic(int topicID) {
	currentTopic = topicList.get(topicID - 1001);
	topicMenuProcess(currentTopic);
}

void postMenu() {
	cout << endl;
	cout << "[1] Reply to post " << endl;
	cout << "[2] View replies" << endl;
	cout << "[0] Back to user home" << endl;
	cout << "Enter option: ";
}

bool postMenuProcess(Post currentPost) {
	string option = "1";

	while (option != "0") {
		currentPost.print();
		postMenu();

		cin >> option;
		if (option == "1") {
			createReply(currentPost);
		}
		else if (option == "2") {
			system("cls");
			replyMenuProcess(currentPost);
		}
		else if (option == "3") {
			cout << "Next page" << endl;
		}
		else if (option == "4") {
			createPost();
			system("cls");

		}
		else if (option == "0") {
			system("cls");
			cout << "Back to user home. ";
			return false;
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
	}
	return true;
}

void createReply(Post post) {
	string message;
	Reply newReply;
	struct tm newtime;
	__time32_t aclock;
	char buffer[32];
	errno_t errNum;
	_time32(&aclock);
	_localtime32_s(&newtime, &aclock);
	errNum = asctime_s(buffer, 32, &newtime);
	cout << "----------------------------------" << endl;
	cout << "Enter your reply here: " << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, message);
	newReply.setReply(message);
	newReply.setTopic(post.getTopic());
	newReply.setAuthor(currentUser.getUserName());
	newReply.setTitle(post.getTitle());
	newReply.setDate(buffer);
	if (replyList.add(newReply)) {
		/*saveReplyData(newReply);*/
		cout << "Reply has been added succesfully to the post!" << endl << endl;
		system("pause");
		system("cls");
	}
	else
		cout << "Saved Error!" << endl;
}

void replyMenu() {
	cout << endl;
	cout << "[1] Reply to post " << endl;
	cout << "[0] Back to user home" << endl;
	cout << "Enter option: ";
}
bool replyMenuProcess(Post currentPost) {
	string option = "1";
	string title = currentPost.getTitle();
	string topic = currentPost.getTopic();
	string author = currentPost.getAuthor();
	while (option != "0") {
		replyList.display(title, topic, author);
		replyMenu();

		cin >> option;
		if (option == "1") {
			createReply(currentPost);
		}
		else if (option == "2") {
			cout << "View a post" << endl;
		}
		else if (option == "3") {
			cout << "Next page" << endl;
		}
		else if (option == "4") {
			createPost();
			system("cls");

		}
		else if (option == "0") {
			system("cls");
			cout << "Back to user home. ";
			return false;
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
	}
	return true;
}
void displayAPost(int postID) {
	Post currentPost = postList.get(postID - 1001);
	postMenuProcess(currentPost);
}

void userPostMenu() {
	cout << "C++ Programming Forum" << endl;
	cout << "--------------------------------------------------------" << endl;
	postList.userDisplay(currentUser.getUserName());

	cout << endl << "[1] View a Post " << endl;
	cout << "[2] Delete a Post" << endl;
	cout << "[0] Back to user home" << endl;
	cout << "Enter option: ";
}
bool userPostMenuProcess() {
	string option = "1";
	while (option != "0") {
		userPostMenu();
		cin >> option;
		if (option == "1") {
			int postID;
			cout << "Enter ID: ";
			cin >> postID;
			system("cls");
			displayAPost(postID);
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
	string message, title, description;
	Post newPost;
	cout << "------------------" << endl;
	cout << "Title of Post: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, title);
	newPost.setTitle(title);
	cout << "Description of Post: " << endl;;
	getline(cin, description);
	newPost.setDescription(description);
	cout << "Post your message here: " << endl;;
	getline(cin, message);
	newPost.setMessage(message);
	newPost.setTopic(currentTopic.getTopic());
	newPost.setAuthor(currentUser.getUserName());
	if (postList.add(newPost)) {
		savePostData(newPost);
		cout << "New post is created succesfully!" << endl << endl;
		system("pause");
		system("cls");
	}
	else
		cout << "Saved Error!" << endl;
}

void createTopic() {
	string title;
	PostList pList;
	cout << "------------------" << endl;
	cout << "Naame of Topic: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, title);
	Topic newTopic(title, currentUser.getUserName());
	if (topicList.add(newTopic)) {
		saveTopicData(newTopic);
		cout << "New Topic is created succesfully!" << endl << endl;
		system("pause");
		system("cls");
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