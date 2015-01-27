//
//  com_CrossApp_IM_IM.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-15.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#include"com_CrossApp_IM_IM.h"
#include "HXSDKController.h"
//#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"",__VA_ARGS__)
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
	JNIEXPORT void JNICALL Java_coom_CrossApp_IM_IMINIT_isRegister(JNIEnv *env, jclass thiz, jboolean Register)
	{
		bool registerresult = Register;
		HXSDKController::getInstance()->postNotification_isRegister(registerresult);
	}
#ifdef __cplusplus
}
#endif


void com_CrossApp_IM_IM::init_android()
{
	//LOGD("qiaoxin jni call init_android");
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
	
	//LOGD("IM jni call login_android");
	/*
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
	*/
}

void com_CrossApp_IM_IM::logout_android()
{
	//LOGD("qiaoxin jni call logout_android");
	/*
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "com/CrossApp/IM/IMINIT", "logout_android", "()V")) {

		//LOGD("qiaoxin jni getStaticMethodInfo logout_android");
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
	*/
}


