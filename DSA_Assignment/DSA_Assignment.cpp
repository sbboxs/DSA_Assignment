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
void displayTopics();
void displayUserTopics();
void displayUserPosts();
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
PostList postList;
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
		PostList pList;
		while (getline(inFile, str) && str != "") {
			stringstream ss(str);
			getline(ss, topic, ';');
			getline(ss, author, ';');
			Topic currentTopic(topic, author, pList);
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
					system("cls");
					cout << "Login credentials invalid!";
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
			cout << "Sorry. You have entered an invalid option.";
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
			cout << "Enter Username: ";
			cin >> newUsername;
			existUser = userDictionary.get(newUsername);
			if (existUser.getUserName() != newUsername)
			{
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
					system("cls");
					cout << "Password is not matched.";
				}
			}
			else
			{
				system("cls");
				cout << "Username is exist! Please enter another unique username.";
			}

			
			
		} 
		else if (registerOption == "0") {
			system("cls");
			cout << "Has back to home. ";
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option.";
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
	cout << "[3] My Own Topics" << endl;
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
			displayUserTopics();
		}
		else if (option == "0") {
			system("cls");
			cout << "Has logged out. ";
			return false;
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option.";
		}
	}
	return true;
}

void displayTopics() {
	string option = "1";
	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "--------------------------------------------------------------" << endl;
		topicList.display("");
		cout << "--------------------------------------------------------------" << endl;

		cout << "[1] View a Topic " << endl;
		cout << "[2] My Own Posts" << endl;
		cout << "[0] Back to discussion topics" << endl;
		cout << "---------------------" << endl;
		cout << "Enter option: ";
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
			system("cls");
			displayUserPosts();
		}
		else if (option == "3") {
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

void displayUserTopics() {
	string option = "1";
	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "--------------------------------" << endl;
		topicList.userDisplay(currentUser.getUserName());
		cout << "--------------------------------" << endl;
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
			int topicID;
			string confirmDelete;
			Topic topicDeleted;
			cout << "Enter Topic ID to be deleted: ";
			cin >> topicID;
			if (topicID - 1001 < topicList.getLength() && topicID-1001 >= 0) {
				topicDeleted = topicList.get(topicID - 1001);
				if (topicDeleted.getAuthor() == currentUser.getUserName()) {
					cout << "Do you sure want to remove topic index of " << topicID << "? (Y/N): ";
					cin >> confirmDelete;
					if (confirmDelete == "Y" || confirmDelete == "y")
					{
						topicList.remove(topicID - 1001);
						//Remove relavant post list
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
					else {
						system("cls");
					}
				}
				else {
					system("cls");
					cout << "You do not have the permission to delete other user' topic" << endl;
				}

			}
			else {
				system("cls");
				cout << "Invalid Topic ID." << endl;
			}
		}
		else if (option == "3") {
			cout << "Create new posts" << endl;
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

void displayUserPosts() {
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
			int postID;
			string confirmDelete;
			Post postDeleted;
			cout << "Enter Post ID to be deleted: ";
			cin >> postID;
			if (postID - 1001 < postList.getLength() && postID - 1001 >= 0) {
				postDeleted = postList.get(postID - 1001);
				if (postDeleted.getAuthor() == currentUser.getUserName()) {
					cout << "Do you sure want to remove post index of " << postID << "? (Y/N): ";
					cin >> confirmDelete;
					if (confirmDelete == "Y" || confirmDelete == "y")
					{
						postList.remove(postID - 1001);
						//Should look for relavant replies and delete
						/*for (int i = 0; i < postList.getLength(); i++) {
							Post currentPost = postList.get(i);
							if (currentPost.getTopic() == postDeleted.getTopic())
								postList.remove(i);
						}*/
						updatePostData();
						system("cls");
						cout << postDeleted.getTopic() << " is deleted." << endl;
					}
					else {
						system("cls");
					}
				}
				else {
					system("cls");
					cout << "You do not have the permission to delete other user' post" << endl;
				}

			}
			else {
				system("cls");
				cout << "Invalid Post ID." << endl;
			}
		}
		else if (option == "3") {
			cout << "Create new posts" << endl;
		}
		else if (option == "0") {
			system("cls");
			cout << "Back to all topics. ";
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl;
		}
	}
 }

void displayATopic(int topicID) {
	string option = "1";
	currentTopic = topicList.get(topicID-1001);

	while (option != "0") {
		cout << "Topic: " << currentTopic.getTopic() << endl;
		cout << "---------------------------" << endl;
		postList.topicDisplay(currentTopic.getTopic());
		cout << "----------------------------------------------------------" << endl;
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
			cout << "Back to discussion topic. ";
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
	string message, title, description;
	Post newPost;
	cout << "Creating new post!" << endl;
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
	if (currentTopic.addPost(newPost)) {
		savePostData(newPost);
		postList.add(newPost);
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