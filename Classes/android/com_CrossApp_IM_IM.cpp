//
//  com_CrossApp_IM_IM.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-15.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#include"com_CrossApp_IM_IM.h"
#include "HXSDKController.h"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"",__VA_ARGS__)
USING_NS_CC;

#ifdef __cplusplus
extern "C" {
#endif
	//判断是否已经登录成功
	JNIEXPORT void JNICALL Java_com_CrossApp_IM_IMINIT_isLogin(JNIEnv *env, jclass thiz, jboolean login)
	{	
		bool result = login;
		HXSDKController::getInstance()->postNotification_isLogin(result);
	}
	//判断是否注册成功
	JNIEXPORT void JNICALL Java_com_CrossApp_IM_IMINIT_isRegister(JNIEnv *env, jclass thiz, jboolean Register)
	{
		bool registerresult = Register;
		HXSDKController::getInstance()->postNotification_isRegister(registerresult);
	}
	//判断是否退出成功
	JNIEXPORT void JNICALL Java_com_CrossApp_IM_IMINIT_isLogout(JNIEnv *env, jclass thiz, jboolean logout)
	{
		bool logoutresult = logout;
		HXSDKController::getInstance()->postNotification_isLogOut(logoutresult);
	}
#ifdef __cplusplus
}
#endif

/*初始化，登录注册相关类*/
void com_CrossApp_IM_IM::init_android()
{
	LOGD("hxsdk init");
}

void com_CrossApp_IM_IM::registerAccount_android(const char* userName, const char* passWord)
{
	
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/IMINIT", "registerAccount_android", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave)
	{
		jstring p_name;
		jstring p_passWord;
		p_name = info.env->NewStringUTF(userName);
		p_passWord = info.env->NewStringUTF(passWord);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, p_name, p_passWord);

		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(p_name);
		info.env->DeleteLocalRef(p_passWord);
	}
	
}

void com_CrossApp_IM_IM::login_android(const char* userName, const char* passWord)
{
	
	LOGD("IM jni call login_android");
	
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/IMINIT", "login_android", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave)
	{
		jstring p_name;
		jstring p_passWord;
		p_name = info.env->NewStringUTF(userName);
		p_passWord = info.env->NewStringUTF(passWord);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, p_name, p_passWord);

		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(p_name);
		info.env->DeleteLocalRef(p_passWord);
	}
	
}

void com_CrossApp_IM_IM::logout_android()
{
	LOGD("qiaoxin jni call logout_android");
	
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "com/CrossApp/IM/IMINIT", "logout_android", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
	
}

/*好友列表相关管理*/

/*好友管理*/

//获取好友列表
std::vector<std::string> com_CrossApp_IM_IM::getContactUserNames_android()
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/IMINIT", "getContactUserNames", "()[Ljava/lang/String;");
	if (ishave)
	{
		std::vector<std::string> usernameVector;
		jobjectArray usernameList = (jobjectArray)info.env->CallStaticObjectMethod(info.classID, info.methodID);
		int length = info.env->GetArrayLength(usernameList);
		jstring tmp;
		for (int i = 0; i < length; i++)
		{
			tmp = (jstring)info.env->GetObjectArrayElement(usernameList, i);
			const char* result = (char*)info.env->GetStringUTFChars(tmp, 0);

			string pp = result;
			usernameVector.push_back(pp);
		}
		return usernameVector;
		info.env->DeleteLocalRef(tmp);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteGlobalRef(usernameList);
	}

}
//查找好友，SDK不提供好友查找的服务, 如需要查找好友, 需要调用开发者自己服务器的用户查询接口
//为了保证查找到的好友可以添加, 需要将用户自己服务器的用户数据库, 通过SDK的后台接口导入到SDK服务器中
bool com_CrossApp_IM_IM::findFriends_android(const char* friendsname)
{
	//向自己的服务器实现好友查找
	return true;
}
//添加好友
void com_CrossApp_IM_IM::addContact_anroid(const char* toAddUsername, const char* reason)
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/FRIENDMANAGENT", "addContact", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (ishave)
	{
		jstring username = info.env->NewStringUTF(toAddUsername);
		jstring p_reason = info.env->NewStringUTF(reason);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, username, p_reason);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(username);
		info.env->DeleteLocalRef(p_reason);
	}
}
//删除好友
void com_CrossApp_IM_IM::deleteContact_android(const char* username)
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/FRIENDMANAGENT", "deleteContact", "(Ljava/lang/String;)V");
	if (ishave)
	{
		jstring p_username = info.env->NewStringUTF(username);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, p_username);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(p_username);
	}
}
//同意好友请求
void com_CrossApp_IM_IM::acceptInvitation_android(const char* username)
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/FRIENDMANAGENT", "acceptInvitation", "(Ljava/lang/String;)V");
	if (ishave)
	{
		jstring p_username = info.env->NewStringUTF(username);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, p_username);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(p_username);
	}
}
//拒绝好友请求
void com_CrossApp_IM_IM::refuseInvitation_android(const char* username)
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/FRIENDMANAGENT", "refuseInvitation", "(Ljava/lang/String;)V");
	if (ishave)
	{
		jstring p_username = info.env->NewStringUTF(username);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, p_username);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(p_username);
	}
}
//监听好友请求
void com_CrossApp_IM_IM::setContactListener_android()
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/FRIENDMANAGENT", "setContactListener", "()V");
	if (ishave)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
		info.env->DeleteLocalRef(info.classID);
	}
}
//监听好友状态事件
void com_CrossApp_IM_IM::setContactStatus_android()
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/FRIENDMANAGENT", "setContactStatus", "()V");
	if (ishave)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
		info.env->DeleteLocalRef(info.classID);
	}
}
//获取黑名单
std::vector<std::string> com_CrossApp_IM_IM::getBlackListUsernames_android()
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/FRIENDMANAGENT", "getBlackListUsernames", "()[Ljava/lang/String;");
	if (ishave)
	{
		std::vector<std::string> usernameVector;
		jobjectArray usernameList = (jobjectArray)info.env->CallStaticObjectMethod(info.classID, info.methodID);
		int length = info.env->GetArrayLength(usernameList);
		jstring tmp;
		for (int i = 0; i < length; i++)
		{
			tmp = (jstring)info.env->GetObjectArrayElement(usernameList, i);
			const char* result = (char*)info.env->GetStringUTFChars(tmp, 0);
			string pp = result;
			usernameVector.push_back(pp);
			info.env->DeleteLocalRef(tmp);
		}

		return usernameVector;
		info.env->DeleteLocalRef(tmp);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(usernameList);
	}
}
//把用户添加到黑名单
void com_CrossApp_IM_IM::addUserToBlackList_android(const char* username, bool isboth)
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/FRIENDMANAGENT", "addUserToBlackList", "(Ljava/lang/String;Z)V");
	if (ishave)
	{
		jstring p_username = info.env->NewStringUTF(username);
		jboolean p_isboth = isboth;
		info.env->CallStaticVoidMethod(info.classID, info.methodID, p_username, p_isboth);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(p_username);
	}
}
//把用户从黑名单移除
void com_CrossApp_IM_IM::deleteUserFromBlackList_android(const char* username)
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/FRIENDMANAGENT", "deleteUserFromBlackList", "(Ljava/lang/String;)V");
	if (ishave)
	{
		jstring p_username = info.env->NewStringUTF(username);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, p_username);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(p_username);
	}
}
