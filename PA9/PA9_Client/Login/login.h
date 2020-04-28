#pragma once
/*******************************************************************************************
* Programmer: Shutian Wang *
* Class: CptS 122, Spring, 2020; Lab Section 14 *
* Programming Assignment: PA9 *
* Date: Apr 27, 2020 *
* Description: PA9 LOGIN HEADER*
*******************************************************************************************/

void login_start();
void login_sendInfo(char username[128], char password[128]);
void signup_sendInfo(char username[128], char password[128]);

bool isLogin();
bool islogin;
