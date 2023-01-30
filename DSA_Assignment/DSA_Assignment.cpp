// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include "User.h"
#include "Dictionary.h"

using namespace std;

void displayHome();
void loginForm();
void loginProcess(Dictionary& userDictionary);
void registerForm();
void registerProcess(Dictionary& userDictionary);

int main()
{
	Dictionary userDictionary;
	User newUser1("test", "test", false);
	userDictionary.add(newUser1.getUserName(),newUser1);
	userDictionary.print();

	string option = "1";	

	//Login & Registration
	while (option != "0") {
		//system("cls");
		displayHome();
		cin >> option;
		//Login
		if (option == "1") {
			loginProcess(userDictionary);
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

void displayHome() {
	cout << endl;
	cout << "Welcome to Ngee Ann Discussion Forum!" << endl;
	cout << "-------------------------------------" << endl;
	cout << "[1] Have an account? Login!" << endl;
	cout << "[2] New to here? Register an account!" << endl;
	cout << "[0] Quit the application." << endl;
	cout << "Enter option: ";
}

void loginForm() {
	cout << endl;
	cout << "Login Place!" << endl;
	cout << "-------------------------" << endl;
	cout << "[1] Key in login credentials: " << endl;
	cout << "[0] Back to login." << endl;
	cout << "Enter option: ";
}

void loginProcess(Dictionary &userDictionary) {
	string loginOption = "1";
	string promptUsername = "";
	string promptPwd = "";
	bool loginSuccess = false;

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
				if (loginUser.getPassword() == promptPwd) {
					loginSuccess == true;
					cout << "Login Success!" << endl;
					system("pause");
					system("cls");
				}
				else {
					loginSuccess == false;
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
}

void registerForm() {
	cout << endl;
	cout << "Registration Place!" << endl;
	cout << "-----------------------" << endl;
	cout << "[1] Key in registration credentials: " << endl;
	cout << "[0] Back to login." << endl;
	cout << "Enter option: ";
}

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
void forumMenu() {
	cout << endl;
}