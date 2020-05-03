#pragma once
/*******************************************************************************************
* Programmer: Shutian Wang *
* Class: CptS 122, Spring, 2020; Lab Section 14 *
* Programming Assignment: PA9 *
* Date: Apr 27, 2020 *
* Description: PA9 LOGIN HEADER*
*******************************************************************************************/

class login
{
public:
	login() { islogin = false; correctInfo = true; }

	~login() {}

	void login_start();

	bool usernameCheck(char username[128]);
	bool passwordCheck(char password[128], char repassword[128]);

	void log_in();
	void signup();

	bool login_sendInfo(char username[128], char password[128]);
	bool signup_sendInfo(char username[128], char password[128]);

	bool isLogin();

	char* getName() { return name; }

private:
	//username
	char name[128];
	bool islogin;
	bool correctInfo;
};









