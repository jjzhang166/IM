//
//  IMUserManager.h
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#ifndef __IMUSER_MANAGER_H__
#define __IMUSER_MANAGER_H__
#include "CrossApp.h"
#include "CrossAppExt.h"
#include <vector>
#include <string>
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

typedef enum{
	offline = 0,
	online
}UserStatus;

class User
{
public:
	User();
	~User();
	bool init(std::string p_uid, std::string p_nickname, std::string p_sex, std::string p_photo, std::string p_signature, UserStatus p_status);
public:
	std::string uid;
	std::string nickname;
	std::string photo;
	std::string sex;
	std::string signature;
	UserStatus status;

};

#pragma IMUserManager

class IMUserManager :public CAObject
{
public:
	static IMUserManager* Instance();
	static void destroyInstance();
	IMUserManager();
	virtual ~IMUserManager();
public:
	void _delete(std::string uid);
	//用户登录
	bool userLogin(User user);
	//用户退出
	bool userLogout();
	//在线用户
	User* onLineUser();
protected:
	sqlite3_stmt *_sqlite_stmt_delete;
	sqlite3_stmt *_sqlite_stmt_login;
	sqlite3_stmt *_sqlite_stmt_logout;
	sqlite3_stmt *_sqlite_stmt_online;
};

#endif /*defined(__IMUSER_MANAGER_H__)*/