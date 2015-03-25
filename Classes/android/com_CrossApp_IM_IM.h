﻿/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"",__VA_ARGS__)
#endif
#include <stdio.h>
#include <stdlib.h>
//#include <android/log.h>
#include <vector>
#include "HXSDKBuddy.h"
/* Header for class com_CrossApp_IM_IM */

#ifndef _Included_com_CrossApp_IM_IM
#define _Included_com_CrossApp_IM_IM
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"",__VA_ARGS__)
USING_NS_CC;
using namespace std;
class com_CrossApp_IM_IM
{
public:
	/****************登录注册类************************/
	static void init_android();
	static void login_android(const char* userName, const char* passWord);
	static void registerAccount_android(const char* userName, const char* passWord);
	static void logout_android();

	/**************好友管理*************************/
	//获取好友列表
	static void getContactUserNames_android();
	static void stringnameToList(std::vector<std::string> pvector);
	//添加好友
	static void addContact_anroid(const char* toAddUsername, const char* reason);
	
	/****************群管理********************/
	//获取公开群
	static void getPublicGroup_android();
	//创建自己的群
	static void createGroup_android(HXSDKGroupStyle groupType, const char* gName, const char* gDescription);
	//获取自己的群
	static void getMyGroupList_android();
	//加入不需要验证的群
	static bool joinNoNeedCheckGroup_android(const char* groupId);
	//加入需要验证的群
	static bool joinNeedCheckGroup_android(const char* groupId, const char* groupName, const char* message);
	//退出群
	static bool exitGroup_android(const char* groupId);
	//解散该群
	static bool destroyGroup_android(const char* groupId);
	//群主加人,只有群主才能添加用户
	static bool addUserToGroup_android(const char* groupId, std::vector<char*> usernames);
	//私有群加人，只有开放了成员能邀请人才可以
	static bool inviteUser_android(const char* groupId, std::vector<char*> usernames, const char* message);
	//群聊减人，只有群主才可以
	static bool deleteUserFromGroup_android(const char* groupId, const char* userName);
	//屏蔽群消息，群主不能屏蔽
	  static bool blockGroupMessage_android(const char* groupId);
	//解除屏蔽群消息
	  static bool unblockGroupMessage_android(const char* groupId);
	//修改群组名称
	  static bool changeGroupName_android(const char* groupId, const char* newgroupName);
	//群聊不提醒只显示数目
	  static bool setReceiveNotNoifyGroup_android(std::vector<char*> groupIds);
	//将用户加到群组的黑名单,只能群主能用
	  static bool blockUser_android(const char* groupId, const char* username);
	//将用户从群组的黑名单移除,群主能用
	  static bool unblockUser_android(const char* groupId, const char* username);
	//获取黑名单列表
	  static void getBlockedUsers_android(const char* groupId);

	  /*消息管理*/
	  static void sendMessage_android(const char* messageText, const char* toUserName);
	  static void receiveMessage_android();

	  //chinahypo-2015-3-19
	  static void loadMessage_android(const char* generalname);



	//转换函数
	  static void CallStaticMethod_void(const char* classname, const char* methodname);
	  static bool CallStaticMethod_bool(const char* classname, const char* methodname);
	  static void CallStaticMethod_void(const char* classname, const char* methodname, const char* paragrmone);
	  static bool CallStaticMethod_bool(const char* classname, const char* methodname, const char* paragrmone);
	  static void CallStaticMethod_void(const char* classname, const char* methodname, const char* paragrmone,const char* paragrmtwo);
	  static bool CallStaticMethod_bool(const char* classname, const char* methodname, const char* paragrmone, const char* paragrmtwo);
	  static void CallStaticMethod_void(const char* classname, const char* methodname, const char* paragrmone, const char* paragrmtwo,const char* paragrmthree);
	  static bool CallStaticMethod_bool(const char* classname, const char* methodname, const char* paragrmone, const char* paragrmtwo, const char* paragrmthree);
};

#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT void JNICALL Java_com_CrossApp_IM_IMINIT_isLogin(JNIEnv *env, jclass thiz, jboolean login);
	JNIEXPORT void JNICALL Java_com_CrossApp_IM_IMINIT_isRegister(JNIEnv *env, jclass thiz, jboolean Register);
	JNIEXPORT void JNICALL Java_com_CrossApp_IM_IMINIT_isLogout(JNIEnv *env, jclass thiz, jboolean logout);
#ifdef __cplusplus
}
#endif
#endif
