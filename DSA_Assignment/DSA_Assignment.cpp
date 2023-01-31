//======================================================
//Student Number :S10222651F, S10223421D
//Student Name   :Chia Jiun Hong, Syahmi Mirhan Bin Zulkiflee
//Module  Group  :P02       
//======================================================
#include <string>
#include <iostream>
#include "User.h"
#include "Dictionary.h"
#include "LinkedList.h"

using namespace std;

void saveUserData();
void loadUserData();
void loadForumData();
void saveForumData();
void displayHome();
void loginForm();
bool loginProcess(Dictionary& userDictionary, User& currentUser);
void registerForm();
void registerProcess(Dictionary& userDictionary);
void userHome(string userName);
bool userHomeProcess(Dictionary& userDictionary, User currentUser);

int main()
{
	//Defining variables.
	Dictionary userDictionary;
	User currentUser;
	User newUser1("test", "test", false);
	userDictionary.add(newUser1.getUserName(),newUser1);
	userDictionary.print();
	bool ifLogin = false;
	string option = "1";	

	//Controlling of Login & Registration
	while (option != "0") {
		if (ifLogin)
			ifLogin = userHomeProcess(userDictionary, currentUser);
		else {
			displayHome();
			cin >> option;
			//Login
			if (option == "1") {
				ifLogin = loginProcess(userDictionary, currentUser);
			}
			else if (option == "2") {
				registerProcess(userDictionary);
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

void saveUserData() {}
void loadUserData() {}
void loadForumData() {}
void saveForumData() {}

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
//This function is to control the flow of login form. 
//The user can perform logging in into their account by inputing the username and password.
//The user can also perform back to home page.
bool loginProcess(Dictionary &userDictionary, User &currentUser) {
	string loginOption = "1";
	string promptUsername = "";
	string promptPwd = "";

	while (loginOption != "0") {
		system("cls");
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
				if (loginUser.getPassword() == promptPwd) {
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
void registerProcess(Dictionary& userDictionary) {
	string registerOption = "1";
	string newUsername;
	string newPassword;
	string checkPassword;
	User existUser;
	while (registerOption != "0") {
		system("cls");
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
					userDictionary.add(newUsername, newUser);
					cout << "Account is created successfully! ";
					system("pause");
					system("cls");
					break;
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
void userHome(string userName) {
	cout << endl;
	cout << "Welcome back! Dear user: " << userName << endl;
	cout << "---------------------------" << endl;
	cout << "[1] View all topics and posts " << endl;
	cout << "[2] View my posts" << endl;
	cout << "[3] Create new posts" << endl;
	cout << "[0] Logout" << endl;
	cout << "Enter option: ";
}

//=========
//This function control the flow of user home.
//The user can perform view topics and posts, view his post and create new post.
//The user can also perform logout to main home page.
bool userHomeProcess(Dictionary& userDictionary, User currentUser) {
	string userHomeOption = "1";
	string userName = currentUser.getUserName();
	while (userHomeOption != "0") {
		userHome(userName);
		cin >> userHomeOption;
		if (userHomeOption == "1"){
			cout << "All topics and posts" << endl;
		}
		else if (userHomeOption == "2") {
			cout << "My posts" << endl;
		}
		else if (userHomeOption == "3") {
			cout << "Create new posts" << endl;
		}
		else if (userHomeOption == "0") {
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