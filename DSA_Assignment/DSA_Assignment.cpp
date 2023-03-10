//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include <string>
#include <iostream>
#include <time.h>  
#include <stdio.h> 
#include <algorithm> 
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
void loadTopicData();
void loadPostData();
void loadReplyData();

void saveUserData(User& newUser);
void saveTopicData(Topic& newTopic);
void savePostData(Post& newPost);
void saveReplyData(Reply& newReply);

void updateTopicData();
void updatePostData();
void updateReplyData();

void displayHome();
bool loginProcess();
void registerProcess();

bool userHomeProcess();
int choosePageNo(int target, int total, int current);
void displayTopics();
void displayUserTopics();
void displayUserPosts();
void displayATopic(int topicID);
void displayAPost(int postID, int topicID);
void replyProcess(Post post);
void createReply(Post post);
void createPost();
void editPost(int postID, Post currentPost);
bool checkTopic(string title);
void createTopic();

void deletePostsRecursive(PostList& postList, int index, Topic& topicDeleted);
void deleteRelavantPostData(Post& postDeleted);
void deleteReplyRecursive(ReplyList& replyList, int index, Post& postDeleted);

bool topicIDValidation(int topicID);
bool postIDValidation(int postID);

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
	//Load all needed data
	loadUserData();
	loadTopicData();
	loadPostData();
	loadReplyData();

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
			if (option == "1") {
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
				cout << "Sorry. You have entered an invalid option." << endl << endl;
			}
		}

	}
}

//=========
//This function is to load all the user data and store into the userDicionary. 
void loadUserData() {
	inFile.open("user.txt");
	if (inFile.fail()) {
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
	}
}

//=========
//This function is used to load all the topics data and store into the global topicList
void loadTopicData() {
	//Loading topic data
	//Check if file exist, if not create one.
	inFile.open("topic.txt");
	if (inFile.fail()) {
		ofstream outFile;
		outFile.open("topic.txt");
		outFile.close();
	}
	else {
		string topic, author;
		int totalPost;
		while (getline(inFile, str) && str != "") {
			stringstream ss(str);
			getline(ss, topic, ';');
			getline(ss, author, ';');
			ss >> totalPost;
			Topic loadTopic(topic, author, totalPost);
			topicList.add(loadTopic);
		}
		inFile.close();
	}
}

//=========
//This function is used to load the post data and store it into the global postList
void loadPostData() {
	//Load post data
	//Check if file exist if not create one
	string filename = "post.txt";
	inFile.open(filename);
	if (inFile.fail()) {
		ofstream outFile;
		outFile.open(filename);
		outFile.close();
	}
	else {
		string message, topic, title, author, description;
		while (getline(inFile, str) && str != "") {
			stringstream ss(str);
			getline(ss, title, ';');
			getline(ss, description, ';');
			getline(ss, message, ';');
			getline(ss, author, ';');
			getline(ss, topic, ';');
			Post loadPost(title, description, message, author, topic);
			postList.add(loadPost);
		}
		inFile.close();
	}
}
//=========
//This function is used to load the reply data and store it into the global replyList
void loadReplyData() {
	//Load post data
	//Check if file exist if not create one
	string filename = "reply.txt";
	inFile.open(filename);
	if (inFile.fail()) {
		ofstream outFile;
		outFile.open(filename);
		outFile.close();
	}
	else {
		string topic, title, author, date, reply;
		while (getline(inFile, str) && str != "") {
			stringstream ss(str);
			getline(ss, reply, ';');
			getline(ss, author, ';');
			getline(ss, topic, ';');
			getline(ss, title, ';');
			getline(ss, date, ';');
			Reply loadReply(reply, author, topic, title, date);
			replyList.add(loadReply);
		}
		inFile.close();
	}
}

//=========
//This function is to save user data into the file. The newest user data will be appended to the end of the file instead of overwritting the whole file.
//The user is the parameter.
void saveUserData(User& newUser) {
	//Second flag 'ios::app' allows to open the file in append mode.
	//Therefore, there no need to overwritten the file everytime when save.
	//Newest data will just be appended at the end of the file.
	outFile.open("user.txt", ios::app);
	if (outFile.fail()) {
		ofstream outFile;
		outFile.open("user.txt");
		outFile << newUser.getUserName() << ";" << newUser.getPassword() << ";" << newUser.getIsLogin() << endl;
		outFile.close();
	}
	else {
		outFile << newUser.getUserName() << ";" << newUser.getPassword() << ";" << newUser.getIsLogin() << endl;
		outFile.close();
	}
}

//=========
//This function will save topic data into the file by appending to the last line instead of overwritting.
void saveTopicData(Topic& newTopic) {
	outFile.open("topic.txt", ios::app);
	if (outFile.fail()) {
		cout << endl << "No topic data file is found!" << endl;
		cout << endl << "Creating topic data file..." << endl;
		ofstream outFile;
		outFile.open("topic.txt");
		outFile << newTopic.getTopic() << ";" << newTopic.getAuthor() << ";" << newTopic.getTotalPost() << endl;;
		outFile.close();
	}
	else {
		outFile << newTopic.getTopic() << ";" << newTopic.getAuthor() << ";" << newTopic.getTotalPost() << endl;;
		outFile.close();
	}
}

//=========
//This function will save the post data into the file by appending to the last line instead of overwritting.
void savePostData(Post& newPost) {
	//Second flag 'ios::app' allows to open the file in append mode.
	//Therefore, there no need to overwritten the file everytime when save.
	//Newest data will just be appended at the end of the file.
	string filename = "post.txt";
	outFile.open(filename, ios::app);
	if (outFile.fail()) {
		ofstream outFile;
		outFile.open(filename);
		outFile << newPost.getTitle() << ";" << newPost.getDescription() << ";" << newPost.getMessage() << ";" << newPost.getAuthor() << ";" << newPost.getTopic() << endl;
		outFile.close();
	}
	else {
		outFile << newPost.getTitle() << ";" << newPost.getDescription() << ";" << newPost.getMessage() << ";" << newPost.getAuthor() << ";" << newPost.getTopic() << endl;
		outFile.close();
	}
}

//=========
//This function will sasve the reply data into the file by appending to the last line instead of overwritting
void saveReplyData(Reply &newReply) {
	string filename = "reply.txt";
	outFile.open(filename, ios::app);
	if (outFile.fail()) {
		ofstream outFile;
		outFile.open(filename);
		outFile << newReply.getReply() << ";" << newReply.getAuthor() << ";" << newReply.getTopic() << ";" << newReply.getTitle() << ";" << newReply.getDate() << endl;
		outFile.close();
	}
	else {
		outFile << newReply.getReply() << ";" << newReply.getAuthor() << ";" << newReply.getTopic() << ";" << newReply.getTitle() << ";" << newReply.getDate() << endl;
		outFile.close();
	}
}

//=========
//This function is used to update the topic data by overwritting the whole data file. 
void updateTopicData() {
	Topic updateTopic;
	outFile.open("topic.txt");
	if (outFile.fail()) {
	}
	for (int i = 0; i < topicList.getLength(); i++) {
		updateTopic = topicList.get(i);
		outFile << updateTopic.getTopic() << ";" << updateTopic.getAuthor() << ";" << updateTopic.getTotalPost() << endl;;
	}
	outFile.close();
}

//=========
//This function is used to update the post data by overwritting the whole data file.
void updatePostData() {
	Post updatePost;
	outFile.open("post.txt");
	if (outFile.fail()) {
	}
	for (int i = 0; i < postList.getLength(); i++) {
		updatePost = postList.get(i);
		outFile <<updatePost.getTitle() << ";" << updatePost.getDescription() << ";" << updatePost.getMessage() << ";" << updatePost.getAuthor() << ";" << updatePost.getTopic() << endl;
	}
	outFile.close();
}

//=========
//This function is used to update the reply data by overwritting the whole data file.
void updateReplyData() {
	Reply updateReply;
	outFile.open("reply.txt");
	if (outFile.fail()) {
	}
	for (int i = 0; i < replyList.getLength(); i++) {
		updateReply = replyList.get(i);
		outFile << updateReply.getTopic() << ";" << updateReply.getTitle() << ";" << updateReply.getAuthor() << ";" << updateReply.getDate() << ";" << updateReply.getReply() << endl;
	}
	outFile.close();
}

//=========
//This function is to print the layout of the homepage. Do not have any input parameters and return value.
void displayHome() {
	cout << "Welcome to Ngee Ann Discussion Forum!" << endl;
	cout << "-------------------------------------" << endl;
	cout << "[1] Have an account? Login!" << endl;
	cout << "[2] New to here? Register an account!" << endl;
	cout << "[0] Quit the application." << endl;
	cout << "-------------------------------------" << endl;
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
		cout << "Login Place!" << endl;
		cout << "----------------------------" << endl;
		cout << "[1] Key in login credentials " << endl;
		cout << "[0] Back to home page" << endl;
		cout << "----------------------------" << endl;
		cout << "Enter option: ";
		cin >> loginOption;
		//Key in login credentials
		if (loginOption == "1") {
			system("cls");
			cout << "Login Page!" << endl;
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
					cout << "Login Success!" << endl << endl;
					system("pause");
					system("cls");
					return true;
				}
				else {
					system("cls");
					cout << "Login credentials invalid!" << endl << endl;
				}
			}
			else
				cout << "Please fill in username and password" << endl << endl;
		}
		else if (loginOption == "0") {
			system("cls");
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl << endl;
		}
	}
	return false;
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
		cout << "Registration Place!" << endl;
		cout << "-----------------------" << endl;
		cout << "[1] Key in registration credentials " << endl;
		cout << "[0] Back to login" << endl;
		cout << "-----------------------" << endl;
		cout << "Enter option: ";
		cin >> registerOption;
		if (registerOption == "1") {
			cout << "New Username: ";
			cin >> newUsername;
			existUser = userDictionary.get(newUsername);
			if (existUser.getUserName() != newUsername)
			{
				cout << "New Password: ";
				cin >> newPassword;
				cout << "Confirm your Password: ";
				cin >> checkPassword;
				if (newPassword == checkPassword) {
					User newUser(newUsername, newPassword, false);
					if (userDictionary.add(newUsername, newUser)) {
						saveUserData(newUser);
						cout << "-------------------------------- " << endl;
						cout << "Account is created successfully! ";
						system("pause");
						system("cls");
						break;
					}
					else
						cout << "Save Error!." << endl << endl;
				}
				else {
					system("cls");
					cout << "Password does not match." << endl << endl;
				}
			}
			else
			{
				system("cls");
				cout << "Username is taken! Please try again." << endl << endl;
			}



		}
		else if (registerOption == "0") {
			system("cls");
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl << endl;
		}
	}
}


//=========
//This function control the flow of user home, will return false if logout else true if login
//The user can perform view topics and posts, view his post and create new post.
//The user can also perform logout to main home page.
bool userHomeProcess() {
	string option = "1";
	while (option != "0") {
		cout << "Welcome back to C++ Programming Forum" << endl;
		cout << "-------------------------------------" << endl;
		cout << "[1] Dicussion Topics " << endl;
		cout << "[2] View my topics" << endl;
		cout << "[3] View my posts" << endl;
		cout << "[0] Logout" << endl;
		cout << "-------------------------------------" << endl;
		cout << "Enter option: ";
		cin >> option;
		if (option == "1") {
			system("cls");
			displayTopics();
		}
		else if (option == "2") {
			system("cls");
			displayUserTopics();
		}
		else if (option == "3") {
			system("cls");
			displayUserPosts();
		}
		else if (option == "0") {
			system("cls");
			return false;
		}
		else {
			system("cls");
			cout << "You have entered an invalid option. Please try again." << endl << endl;
		}
	}
	return true;
}

//=========
//This function is used to choose the page number to be viewed
//It will check if the target page number is not null and not higher than the total pages.
//If success it will return target pages else the current pages.
int choosePageNo(int target, int total, int current) {
	if (target <= total && target != 0)
	{
		system("cls");
		return target;
	}
	else {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("cls");
		cout << "Page is not found." << endl << endl;
		return current;
	}
}

//=========
//This function is used to display the layout of all topics with paging and control of the flow.
//The user is allow to do several action such as view a topic, view a specific page number or sort by popularity
void displayTopics() {
	string option = "1";
	int totalPages = 0;
	int currentPage = 1;
	int targetPage = 1;
	string sortingMethod = "Default";
	TopicList sortedList;
	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "---------------------" << endl;
		cout << "Viewing all the topics..." << endl;
		cout << endl <<  "----------------------------------------------------------------------------------------------------------------" << endl;
		if (sortingMethod == "Default")
			totalPages = topicList.displayPages(currentPage, "");
		else
			totalPages = sortedList.displayPages(currentPage, "");
		cout << "----------------------------------------------------------------------------------------------------------------" << endl;
		cout << "[1] View a Topic " << endl;
		cout << "[2] View page number" << endl;
		if (sortingMethod == "Default")
			cout << "[3] Sort by popularity" << endl;
		else
			cout << "[3] Sort by default" << endl;
		cout << "[4] Create new Topic" << endl;
		cout << "[0] Back to home page" << endl;
		cout << "---------------------------" << endl;
		cout << "Enter option: ";
		cin >> option;
		if (option == "1") {
			int topicID;
			cout << "Enter Topic ID: ";
			cin >> topicID;
			if (topicIDValidation(topicID)) {
				system("cls");
				displayATopic(topicID);
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
				cout << "Invalid Topic ID. Please try again." << endl << endl;
			}
		}
		//View a page
		else if (option == "2") {
			cout << "Enter page number: ";
			cin >> targetPage;
			currentPage = choosePageNo(targetPage, totalPages, currentPage);
		}
		//Sort by popularity
		else if (option == "3") {
			if (sortingMethod == "Default")
			{
				sortingMethod = "Popularity";
				topicList.sort(sortedList);
				system("cls");
				cout << "Sorted by Popularity." << endl;
			}
			else {
				sortingMethod = "Default";
				system("cls");
				cout << "Sorted by Default." << endl;
			}
		}

		else if (option == "4") {
			cout << "--------------------------------------------------------------" << endl;
			cout << "Creating a new Topic!" << endl;
			cout << "---------------------" << endl;
			createTopic();
		}

		else if (option == "0") {
			system("cls");
		}
		else {
			system("cls");
			cout << "You have entered an invalid option. Please try again." << endl << endl;
		}
	}
}

//=========
//This function is used to display the layouts of all topics with paging created by the user. 
//The action can peformed by the user is overall same as displayAll topics 
//just the user can do action such as delete a topic from here.
void displayUserTopics() {
	string option = "1";
	int totalPages = 0;
	int currentPage = 1;
	int targetPage = 1;
	TopicList sortedList;
	string sortingMethod = "Default";
	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "You are now viewing all your Topics" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl;
		if (sortingMethod == "Default")
			totalPages = topicList.displayPages(currentPage, "");
		else
			totalPages = sortedList.displayPages(currentPage, "");
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "[1] View a Topic " << endl;
		cout << "[2] View page number" << endl;
		cout << "[3] Sort by popularity" << endl;
		cout << "[4] Create new Topic" << endl;
		cout << "[5] Delete a Topic" << endl;
		cout << "[0] Back" << endl;
		cout << "---------------------" << endl;
		cout << "Enter option: ";
		cin >> option;
		//View Topic
		if (option == "1") {
			int topicID;
			cout << "Enter the Topic ID: ";
			cin >> topicID;
			Topic currentTopic = topicList.get(topicID - 1001);
			if (currentTopic.getAuthor()== currentUser.getUserName()) {
				if (topicIDValidation(topicID)) {
					system("cls");
					displayATopic(topicID);
				}
				else {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					system("cls");
					cout << "Invalid Topic ID. Please try again." << endl << endl;
				}

			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
				cout << "You have entered an invalid option. Please try again." << endl << endl;
			}
		
		}
		//View a page
		else if (option == "2") {
			cout << "Enter page number: ";
			cin >> targetPage;
			currentPage = choosePageNo(targetPage, totalPages, currentPage);
		}
		//Sort by popularity
		else if (option == "3") {
			if (sortingMethod == "Default")
			{
				sortingMethod = "Popularity";
				topicList.sort(sortedList);
				system("cls");
				cout << "Sorted by Popularity." << endl;
			}
			else {
				sortingMethod = "Default";
				system("cls");
				cout << "Sorted by Default." << endl;
			}
		}
		else if (option == "4") {
			cout << "Creating a new Topic!" << endl;
			cout << "---------------------" << endl;
			createTopic();
		}
		//Delete Topic
		else if (option == "5") {
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
						//Remove relavant post list
						deletePostsRecursive(postList, 0, topicDeleted);
						updateTopicData();
						updatePostData();

						updateReplyData();
						cout << topicDeleted.getTopic() << " is deleted." << endl << endl;
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
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
				cout << "Invalid Topic ID. Please try again." << endl << endl;
			}
		}


		else if (option == "0") {
			system("cls");
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl << endl;
		}
	}
}

//=========
//This function will display all the post with paging under the selected topics.
//The user can do action such as view a post and create new post from here.
void displayATopic(int topicID) {
	string option = "1";
	currentTopic = topicList.get(topicID - 1001);
	Post currentPost;
	int totalPages = 0;
	int currentPage = 1;
	int targetPage = 1;
	string sortingMethod = "Default";

	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "---------------------" << endl;
		cout << "Viewing " + currentTopic.getTopic() + "..." << endl;
		cout << endl << "-----------------------------------------------------------------------------------------------------------------"  << endl;
		totalPages = postList.displayPagesByTopics(currentPage, currentTopic.getTopic());
		cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
		cout << "[1] View a Post " << endl;
		cout << "[2] View page number" << endl;
		cout << "[3] Create new Post" << endl;
		cout << "[0] Back" << endl;
		cout << "---------------------" << endl;
		cout << "Enter option: ";
		cin >> option;
		if (option == "1") {
			int postID;
			cout << "Enter ID: ";
			cin >> postID;
			if (postIDValidation(postID)) {

				system("cls");
				displayAPost(postID, topicID);
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
				cout << "Invalid Post ID. Please try again." << endl << endl;
			}
		}
		//View a page
		else if (option == "2") {
			cout << "Enter page number: ";
			cin >> targetPage;
			currentPage = choosePageNo(targetPage, totalPages, currentPage);
		}
	
		else if (option == "3") {
			createPost();
			system("cls");

		}
		else if (option == "0") {
			system("cls");
		}
		else {
			system("cls");
			cout << " You have entered an invalid option. Please try again." << endl << endl;
		}
	}
}

//=========
//This function will display the details of a selected posts.
//The user will be able to delete or edit the post if they are the owner of the post 
//else they an only reply and view replies here.
void displayAPost(int postID, int topicID) {
	Post userPost = postList.get(postID - 1001);
	Topic currentTopic = topicList.get(topicID - 1001);
	string option = "1";
	bool success = userPost.getAuthor() == currentUser.getUserName();
	while (option != "0") {
		Post currentPost = postList.get(postID - 1001);
		if (currentPost.getTopic() == currentTopic.getTopic()) {
			cout << "C++ Programming Forum" << endl;
			cout << "---------------------" << endl;
			cout << "Viewing post..." << endl;
			cout << endl << "----------------------------------------------------------------------------------" << endl;
			currentPost.print();
			cout << "[1] Reply to post " << endl;
			cout << "[2] View replies" << endl;
			if (success) {
				cout << "[3] Delete post" << endl;
				cout << "[4] Edit post" << endl;
			}
			cout << "[0] Back" << endl;
			cout << "Enter option: ";

			cin >> option;
			if (option == "1") {
				createReply(currentPost);
			}
			else if (option == "2") {
				system("cls");
				replyProcess(currentPost);
			}
			else if (option == "3" && success) {
				string confirmDelete;
				Post postDeleted;
				postDeleted = postList.get(postID - 1001);
				cout << "Confirm delete? (Y/N): ";
				cin >> confirmDelete;
				if (confirmDelete == "Y" || confirmDelete == "y")
				{
					postList.remove(postID - 1001);
					deleteRelavantPostData(postDeleted);
					updatePostData();
					system("cls");
					cout << postDeleted.getTopic() << " is deleted." << endl << endl;
				}
				else {
					system("cls");
				}
			}
			else if (option == "4" && success) {
				system("cls");
				editPost(postID, currentPost);

			}
			else if (option == "0") {
				system("cls");
			}
			else {
				system("cls");
				cout << "You have entered an invalid option. Please try again." << endl << endl;
			}
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("cls");
			cout << "You have entered an invalid option. Please try again." << endl << endl;
			break;
		}
	}
}
//=========
//This function will display all the post with paging that belongs to the user.
//The user can view post and create post from here.
void displayUserPosts() {
	string option = "1";
	int totalPages = 0;
	int currentPage = 1;
	int targetPage = 1;
	string sortingMethod = "Default";
	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "---------------------" << endl;
		cout << "Viewing all your posts..." << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
		totalPages = postList.displayPages(currentPage, currentUser.getUserName());
		cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
		cout << "[1] View a Post " << endl;
		cout << "[2] View page number" << endl;
		cout << "[3] Create new post" << endl;
		cout << "[0] Back" << endl;
		cout << "---------------------" << endl;
		cout << "Enter option: ";
		cin >> option;
		if (option == "1") {
			int postID;
			cout << "Enter ID: ";
			cin >> postID;
			if (postIDValidation(postID)) {
				system("cls");
				Post currentPost = postList.get(postID-1001);
				int topicID = topicList.get(currentPost.getTopic().c_str());
				displayAPost(postID, topicID+1001);
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("cls");
				cout << "Invalid Post ID. Please try again." << endl << endl;
			} 
		}
		//View a page
		else if (option == "2") {
			cout << "Enter page number: ";
			cin >> targetPage;
			currentPage = choosePageNo(targetPage, totalPages, currentPage);

		}
		else if (option == "3") {
			cout << "Create new posts" << endl;
			createPost();
			system("cls");
		}
		else if (option == "0") {
			system("cls");
		}
		else {
			system("cls");
			cout << "You have entered an invalid option. Please try again." << endl << endl;
		}
	}
}

//=========
//This function display the replies and control the process of replies.
void replyProcess(Post currentPost) {
	string option = "1";
	string title = currentPost.getTitle();
	string topic = currentPost.getTopic();
	string author = currentPost.getAuthor();
	while (option != "0") {
		cout << "C++ Programming Forum" << endl;
		cout << "---------------------" << endl;
		cout << "Viewing replies..." << endl;
		cout << endl << "----------------------------------------------------------------------------------" << endl;
		cout << "Topic: " + topic << endl;
		cout << "----------------------------------------------------------------------------------" << endl;
		printf("@%s: %s",author.c_str(), currentPost.getMessage().c_str());
		cout << endl;
		cout << "----------------------------------------------------------------------------------" << endl;
		replyList.display(title, topic, author);
		cout << endl;
		cout << "[1] Reply post " << endl;
		cout << "[0] Back" << endl;
		cout << "---------------------" << endl;
		cout << "Enter option: ";

		cin >> option;
		if (option == "1") {
			createReply(currentPost);
		}
		else if (option == "0") {
			system("cls");
		}
		else {
			system("cls");
			cout << "You have entered an invalid option. Please try again." << endl << endl;
		}
	}
}

//=========
//This function is use to handle reply created of the post.
void createReply(Post post) {
	string message;
	Reply newReply;
	struct tm newtime;
	__time32_t aclock;
	char date[32];
	errno_t errNum;
	_time32(&aclock);
	_localtime32_s(&newtime, &aclock);
	errNum = asctime_s(date, 32, &newtime);
	date[strlen(date) - 1] = '\0';
	cout << "----------------------------------" << endl;
	cout << "Enter your reply here: " << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, message);
	newReply.setReply(message);
	newReply.setTopic(post.getTopic());
	newReply.setAuthor(currentUser.getUserName());
	newReply.setTitle(post.getTitle());
	newReply.setDate(date);
	if (replyList.add(newReply)) {
		saveReplyData(newReply);
		cout << "Reply has been added succesfully to the post!" << endl << endl;
		system("pause");
		system("cls");
	}
	else
		cout << "Saved Error!" << endl;
}

//=========
//This function is to check the uniqueness of the topic. This avoid duplicate topic to be created.
bool checkTopic(string title) {
	string topic;
	transform(title.begin(), title.end(), title.begin(), ::toupper);
	for (int i = 0; i < topicList.getLength(); i++) {
		topic = topicList.get(i).getTopic();
		transform(topic.begin(), topic.end(), topic.begin(), ::toupper);
		if (topic == title) {
			return false;
		}
	}
	return true;
}

//=========
//This function is used to control the flow of creating topic,
void createTopic() {
	string title;
	int totalTopic = 0;
	cout << "Naame of Topic: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, title);
	if (checkTopic(title)) {
		Topic newTopic(title, currentUser.getUserName(), totalTopic);
		if (topicList.add(newTopic)) {
			saveTopicData(newTopic);
			system("cls");
			cout << "New Topic is created succesfully!" << endl;
		}
		else
		{
			system("cls");
			cout << "Saved Error!" << endl;
		}
	}
	else {
		cout << "Name cannot be the same as existing topics! Please try again." << endl;
		cout << "--------------------------------------------------------------" << endl;
		createTopic();
	}
}


//=========
//This function is use to control the process of create post.
void createPost() {
	cout << endl;
	string message, title, description;
	Post newPost;
	cout << "Creating new Post!" << endl;
	cout << "----------------------" << endl;
	cout << "Title of Post: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, title);
	newPost.setTitle(title);
	cout << "----------------------" << endl;
	cout << "Description of Post: " << endl;;
	getline(cin, description);
	newPost.setDescription(description);
	cout << "----------------------" << endl;
	cout << "Post your message here: " << endl;;
	getline(cin, message);
	newPost.setMessage(message);
	newPost.setTopic(currentTopic.getTopic());
	newPost.setAuthor(currentUser.getUserName());
	if (currentTopic.addPost(newPost)) {
		currentTopic.updateTotalPost();
		savePostData(newPost);
		updateTopicData();
		cout << currentTopic.getTotalPost()<<endl;
		postList.add(newPost);
		cout << "New post is created succesfully!" << endl << endl;
	}
	else
		cout << "Saved Error!" << endl << endl;
}

//=========
//This function is use to control the process of user editing their post.
void editPost(int postID, Post currentPost) {
	string option = "1";
	Post newPost = currentPost;
	while (option != "0") {
		newPost.print();
		cout << "[1] Edit title " << endl;
		cout << "[2] Edit description" << endl;
		cout << "[3] Edit message" << endl;
		cout << "[0] Back " << endl;
		cout << "Enter option: ";
		cin >> option;
		if (option == "1") {
			string title;
			cout << "-----------------------" << endl;
			cout << "New title: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, title);
			newPost.setTitle(title);
			system("cls");
			cout << "Title has been updated successfuly." << endl << endl;
		}
		else if (option == "2") {
			string description;
			cout << "-----------------------" << endl;
			cout << "New description: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, description);
			newPost.setDescription(description);
			system("cls");
			cout << "Description has been updated successfuly." << endl << endl;
		}
		else if (option == "3") {
			string message;
			cout << "-----------------------" << endl;
			cout << "New message: " << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, message);
			newPost.setMessage(message);
			system("cls");
			cout << "Message has been updated successfuly." << endl << endl;
		}
		else if (option == "0") {
			system("cls");
		}
		else {
			system("cls");
			cout << "Sorry. You have entered an invalid option." << endl << endl;
		}
		postList.remove(postID - 1001);
		postList.add(postID - 1001, newPost);
		updatePostData();
	}
}

//This function is use to delete all the relavant post data such as the reply, if the post is to be deleted.
void deleteRelavantPostData(Post& postDeleted) {
	//look for relavant replies and delete
	deleteReplyRecursive(replyList, 0, postDeleted);
}

//This function is to recursivly to start delete the post when it reach the last post.
void deletePostsRecursive(PostList& postList, int index, Topic& topicDeleted) {
	if (index == postList.getLength()) {
		return;
	}
	deletePostsRecursive(postList, index + 1, topicDeleted);
	Post deletedPost = postList.get(index);
	if (deletedPost.getTopic() == topicDeleted.getTopic()) {
		deleteRelavantPostData(deletedPost);
		postList.remove(index);
	}
}
//This function is to recursivly start delete the reply when it reach the last reply.
void deleteReplyRecursive(ReplyList& replyList, int index, Post& postDeleted) {
	if (index == replyList.getLength()) {
		return;
	}
	deleteReplyRecursive(replyList, index + 1, postDeleted);
	Reply deletedReply = replyList.get(index);
	if (deletedReply.getTitle() == postDeleted.getTitle()) {
		replyList.remove(index);
	}
}
//=========
//This function is used to check if the topicID key in is a valid one.
bool topicIDValidation(int topicID) {
	if (topicID - 1001 < topicList.getLength() && topicID - 1001 >= 0) {
		return true;
	}
	return false;
}

//=========
//This function is used to check if the postID key in is a valid one.
bool postIDValidation(int postID) {
	if (postID - 1001 < postList.getLength() && postID - 1001 >= 0) {
		return true;
	}
	return false;
}

