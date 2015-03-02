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
	//LOGD("hxsdk init");
}

void com_CrossApp_IM_IM::registerAccount_android(const char* userName, const char* passWord)
{
	CallStaticMethod_void("com/CrossApp/IM/IMINIT", "registerAccount_android", userName, passWord);
}

void com_CrossApp_IM_IM::login_android(const char* userName, const char* passWord)
{
	
	//LOGD("IM jni call login_android");
	CallStaticMethod_void("com/CrossApp/IM/IMINIT", "login_android", userName, passWord);
	
}

void com_CrossApp_IM_IM::logout_android()
{
	//LOGD("qiaoxin jni call logout_android");
	CallStaticMethod_void("com/CrossApp/IM/IMINIT", "logout_android");
	
}

/*好友列表相关管理*/

/*好友管理*/

//获取好友列表
void com_CrossApp_IM_IM::getContactUserNames_android()
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/FRIENDMANAGENT", "getContactUserNames", "()[Ljava/lang/String;");
	std::vector<std::string> usernameVector;
	if (ishave)
	{
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
		info.env->DeleteLocalRef(tmp);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteGlobalRef(usernameList);
	}
	stringnameToList(usernameVector);
}
//从服务器获取的用户名同本地数据进行比较加载
void com_CrossApp_IM_IM::stringnameToList(std::vector<std::string> pvector)
{
	std::vector<std::string>::iterator itr = pvector.begin();
	for (; itr != pvector.end(); itr++)
	{
		HXSDKController::getInstance()->pushFriendsDetail(*itr, eHXSDKEMBuddyFollowState_UnKnow, false);
	}
}

//添加好友
void com_CrossApp_IM_IM::addContact_anroid(const char* toAddUsername, const char* reason)
{
	bool result = CallStaticMethod_bool("com/CrossApp/IM/FRIENDMANAGENT", "addContact", toAddUsername, reason);
	if (result){
		HXSDKController::getInstance()->pushFriendsDetail(toAddUsername, eHXSDKEMBuddyFollowState_NotFollowed, true);
		//列表刷新
	}
	else{
		//LOGD("add friend fail");
	}
}

/****************群组管理**************************/
//获取公开群
void com_CrossApp_IM_IM::getPublicGroup_android()
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/GROUP", "getPublicGroup_android", "()[Ljava/lang/Object;");
	if (isHave)
	{
		jobject jobj;
		jclass class_EMGroupInfo;
		jmethodID EMGroupInfo_getid;
		jstring id;
		jmethodID EMGroupInfo_getname;
		jstring name;

		jobjectArray publicgrouplist = (jobjectArray)info.env->CallStaticObjectMethod(info.classID, info.methodID);
		int length = info.env->GetArrayLength(publicgrouplist);
		for (int i = 0; i < length; i++)
		{
			jobj = info.env->GetObjectArrayElement(publicgrouplist,i);
			class_EMGroupInfo = info.env->GetObjectClass(jobj);
			//id
			EMGroupInfo_getid = info.env->GetMethodID(class_EMGroupInfo, "getGroupId", "()Ljava/lang/String;");
			id = (jstring)info.env->CallObjectMethod(jobj, EMGroupInfo_getid);
			const char* result_id = (char*)info.env->GetStringUTFChars(id,false);
			string pp_id = result_id;
			//name
			EMGroupInfo_getname = info.env->GetMethodID(class_EMGroupInfo, "getGroupName", "()Ljava/lang/String;");
			name = (jstring)info.env->CallObjectMethod(jobj, EMGroupInfo_getname);
			const char* result_name = (char*)info.env->GetStringUTFChars(name, false);
			string pp_name = result_name;
			//数据加载到列表
			HXSDKController::getInstance()->pushGroupsDetail(pp_id, pp_name, "no",0);
		}
		//释放资源
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(jobj);
		info.env->DeleteLocalRef(id);
		info.env->DeleteLocalRef(name);
	}
}

//创建群
void com_CrossApp_IM_IM::createGroup_android(HXSDKGroupStyle groupType, const char* gName, const char* gDescription)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/GROUP", "createGroup_android", "(Ljava/lang/String;Ljava/lang/String;ZZ)V");
	if (isHave)
	{
		jstring groupName = info.env->NewStringUTF(gName);
		jstring groupDescription = info.env->NewStringUTF(gDescription);
		jboolean isPublic;
		jboolean isAllow;
		switch (groupType)
		{
		case eHXSDKGroupStyle_PrivateOnlyOwnerInvite:
			{
				isPublic = false; isAllow = false;break;
			}
		case eHXSDKGroupStyle_PrivateMemberCanInvite:
			{
				isPublic = false; isAllow = true; break;
			}
		case eHXSDKGroupStyle_PublicJoinNeedApproval:
			{
				isPublic = true; isAllow = true; break;
			}
		case eHXSDKGroupStyle_PublicOpenJoin:
			{
				isPublic = true; isAllow = false; break;
			}
		}
		info.env->CallStaticVoidMethod(info.classID, info.methodID, groupName, groupDescription, isPublic, isAllow);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(groupName);
		info.env->DeleteLocalRef(groupDescription);
	}
}

//获取自己创建的群
void com_CrossApp_IM_IM::getMyGroupList_android()
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/GROUP", "getMyGroupList_android", "()[Ljava/lang/Object;");
	if (isHave)
	{
		jobject jobj;
		jclass class_EMGroup;

		jmethodID id_EMGroup_getGroupId;
		jstring id;

		jmethodID EMGroup_getgroupname;
		jstring groupname;

		jmethodID EMGroup_getdescription;
		jstring groupdescription;

		jmethodID EMGroup_getnumbers;
		jint groupnumbers;
		
		jobjectArray grouplist = (jobjectArray)info.env->CallStaticObjectMethod(info.classID, info.methodID);
		int length = info.env->GetArrayLength(grouplist);
		
		for (int i = 0; i < length; i++)
		{
			jobj = info.env->GetObjectArrayElement(grouplist, i);
			class_EMGroup = info.env->GetObjectClass(jobj);
			//id
			id_EMGroup_getGroupId = info.env->GetMethodID(class_EMGroup, "getGroupId", "()Ljava/lang/String;");
			id = (jstring)info.env->CallObjectMethod(jobj, id_EMGroup_getGroupId);
			const char* result_id = (char*)info.env->GetStringUTFChars(id,false);
			string pp_id = result_id;
			//groupname
			EMGroup_getgroupname = info.env->GetMethodID(class_EMGroup, "getGroupName", "()Ljava/lang/String;");
			groupname = (jstring)info.env->CallObjectMethod(jobj, EMGroup_getgroupname);
			const char* result_name = (char*)info.env->GetStringUTFChars(groupname, false);
			string pp_name = result_name;
			//groupdescription
			EMGroup_getdescription = info.env->GetMethodID(class_EMGroup, "getDescription", "()Ljava/lang/String;");
			groupdescription = (jstring)info.env->CallObjectMethod(jobj, EMGroup_getdescription);
			const char* result_des = (char*)info.env->GetStringUTFChars(groupdescription, false);
			string pp_res = result_des;
			//groupnumbers
			EMGroup_getnumbers = info.env->GetMethodID(class_EMGroup, "getAffiliationsCount", "()I");
			groupnumbers = info.env->CallIntMethod(jobj, EMGroup_getnumbers);
			int pp_numbers = groupnumbers;
			//获取的数据加载到List中
			HXSDKController::getInstance()->pushMyGroupsDetail(pp_id,pp_name,pp_res,pp_numbers);
		}
		//释放资源
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(id);
		info.env->DeleteLocalRef(groupname);
		info.env->DeleteLocalRef(groupdescription);
		info.env->DeleteLocalRef(grouplist);
	}
}

//加入不需要验证的群
bool com_CrossApp_IM_IM::joinNoNeedCheckGroup_android(const char* groupId)
{
	return CallStaticMethod_bool("com/CrossApp/IM/GROUP", "joinNoNeedCheckGroup_android", groupId);
}

bool com_CrossApp_IM_IM::joinNeedCheckGroup_android(const char* groupId, const char* groupName, const char* message)
{
	return CallStaticMethod_bool("com/CrossApp/IM/GROUP", "joinNeedCheckGroup_android", groupId, message);
}


//退出群
bool com_CrossApp_IM_IM::exitGroup_android(const char* groupId)
{
	return CallStaticMethod_bool("com/CrossApp/IM/GROUP", "exitGroup_android", groupId);
}
//解散该群
bool com_CrossApp_IM_IM::destroyGroup_android(const char* groupId)
{
	return CallStaticMethod_bool("com/CrossApp/IM/GROUP", "destroyGroup_android", groupId);
}


//群主加人
bool com_CrossApp_IM_IM::addUserToGroup_android(const char* groupId, std::vector<char*> usernames)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/GROUP", "addUserToGroup_android", "(Ljava/lang/String;[Ljava/lang/String;)Z");
	if (isHave)
	{
		int i = 0;
		jstring name;
		jsize length = usernames.size();
		jclass myclass = info.env->FindClass("java/lang/String");
		jobjectArray usernameList = info.env->NewObjectArray(length,myclass,NULL);
		std::vector<char*>::iterator itr = usernames.begin();
		for (; itr != usernames.end(); itr++)
		{
			name = info.env->NewStringUTF(*itr);
			info.env->SetObjectArrayElement(usernameList, i, name);
			i++;
		}
		jstring groupid = info.env->NewStringUTF(groupId);
		jboolean result_android = info.env->CallStaticBooleanMethod(info.classID, info.methodID, groupid, usernameList);
		bool result = result_android;
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(name);
		info.env->DeleteLocalRef(groupid);
		info.env->DeleteLocalRef(myclass);
		info.env->DeleteLocalRef(usernameList);
		return result;
	}
}

//私有群加人
bool com_CrossApp_IM_IM::inviteUser_android(const char* groupId, std::vector<char*> usernames, const char* message)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/GROUP", "inviteUser_android", "(Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;)Z");
	if (isHave)
	{
		int i = 0;
		jsize length = usernames.size();
		jstring name;
		jclass myclass = info.env->FindClass("java/lang/String");
		jobjectArray usernameList = info.env->NewObjectArray(length, myclass, NULL);
		std::vector<char*>::iterator itr = usernames.begin();
		for (; itr != usernames.end(); itr++)
		{
			name = info.env->NewStringUTF(*itr);
			info.env->SetObjectArrayElement(usernameList, i, name);
			i++;
		}
		jstring groupid = info.env->NewStringUTF(groupId);
		jstring Message = info.env->NewStringUTF(message);
		jboolean result_android = info.env->CallStaticBooleanMethod(info.classID, info.methodID, groupid, usernameList,Message);
		bool result = result_android;
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(name);
		info.env->DeleteLocalRef(groupid);
		info.env->DeleteLocalRef(Message);
		info.env->DeleteLocalRef(myclass);
		info.env->DeleteLocalRef(usernameList);
		return result;
	}
}


//群聊减人
bool com_CrossApp_IM_IM::deleteUserFromGroup_android(const char* groupId, const char* userName)
{
	return CallStaticMethod_bool("com/CrossApp/IM/GROUP", "deleteUserFromGroup_android", groupId, userName);
}

//屏蔽群消息，群主不能屏蔽
bool com_CrossApp_IM_IM::blockGroupMessage_android(const char* groupId)
{
	return CallStaticMethod_bool("com/CrossApp/IM/GROUP", "blockGroupMessage_android", groupId);
}
//解除屏蔽群消息
bool com_CrossApp_IM_IM::unblockGroupMessage_android(const char* groupId)
{
	return CallStaticMethod_bool("com/CrossApp/IM/GROUP", "unblockGroupMessage_android", groupId);
}
//修改群组名称
bool com_CrossApp_IM_IM::changeGroupName_android(const char* groupId, const char* newgroupName)
{
	return CallStaticMethod_bool("com/CrossApp/IM/GROUP", "changeGroupName_android", groupId, newgroupName);
}
//设置接收消息不提醒
bool com_CrossApp_IM_IM::setReceiveNotNoifyGroup_android(std::vector<char*> groupIds)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/GROUP", "setReceiveNotNoifyGroup_android", "([Ljava/lang/String;)Z");
	if (isHave)
	{
		int i = 0;
		jstring name;
		jsize length = groupIds.size();
		jclass myclass = info.env->FindClass("java/lang/String");
		jobjectArray usernameList = info.env->NewObjectArray(length, myclass, NULL);
		std::vector<char*>::iterator itr = groupIds.begin();
		for (; itr != groupIds.end(); itr++)
		{
			name = info.env->NewStringUTF(*itr);
			info.env->SetObjectArrayElement(usernameList, i, name);
			i++;
		}
		jboolean result_android = info.env->CallStaticBooleanMethod(info.classID, info.methodID, usernameList);
		bool result = result_android;
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(name);
		info.env->DeleteLocalRef(myclass);
		info.env->DeleteLocalRef(usernameList);
		return result;
	}
}
//群用户被加入到黑名单
bool com_CrossApp_IM_IM::blockUser_android(const char* groupId, const char* username)
{
	return CallStaticMethod_bool("com/CrossApp/IM/GROUP", "blockUser_android", groupId, username);
}
//群用户被移除黑名单
bool com_CrossApp_IM_IM::unblockUser_android(const char* groupId, const char* username)
{
	return CallStaticMethod_bool("com/CrossApp/IM/GROUP", "unblockUser_android", groupId, username);
}
//获取群组黑名单
void com_CrossApp_IM_IM::getBlockedUsers_android(const char* groupId)
{
	JniMethodInfo info;
	bool ishave = JniHelper::getStaticMethodInfo(info, "com/CrossApp/IM/GROUP", "getBlockedUsers_android", "(Ljava/lang/String;)[Ljava/lang/String;");
	std::vector<std::string> usernameVector;
	if (ishave)
	{
		jstring groupid = info.env->NewStringUTF(groupId);
		jobjectArray usernameList = (jobjectArray)info.env->CallStaticObjectMethod(info.classID, info.methodID, groupid);
		int length = info.env->GetArrayLength(usernameList);
		jstring tmp;
		for (int i = 0; i < length; i++)
		{
			tmp = (jstring)info.env->GetObjectArrayElement(usernameList, i);
			const char* result = (char*)info.env->GetStringUTFChars(tmp, 0);

			string pp = result;
			usernameVector.push_back(pp);  //加入到黑名单列表当中
		}
		info.env->DeleteLocalRef(tmp);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteGlobalRef(usernameList);
	}
}
//黑名单转换


/*消息管理*/
void com_CrossApp_IM_IM::sendMessage_android(const char* messageText, const char* toUserName)
{
	CallStaticMethod_void("com/CrossApp/IM/MESSAGE", "sendMessage_android", messageText, toUserName);
}

void com_CrossApp_IM_IM::receiveMessage_android()
{
	CallStaticMethod_void("com/CrossApp/IM/MESSAGE","receiveMessage_android");
}











//转换函数-1，返回void，没有参数
void com_CrossApp_IM_IM::CallStaticMethod_void(const char* classname, const char* methodname)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, classname, methodname, "()V");
	if (isHave)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
		info.env->DeleteLocalRef(info.classID);
	}
}
//转换函数0：返回bool，没有参数
bool com_CrossApp_IM_IM::CallStaticMethod_bool(const char* classname, const char* methodname)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, classname, methodname, "()Z");
	if (isHave)
	{
		jboolean result_android = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
		bool result = result_android;
		info.env->DeleteLocalRef(info.classID);
		return result;
	}
}
//转换函数一：返回void，一个string参数
void com_CrossApp_IM_IM::CallStaticMethod_void(const char* classname, const char* methodname, const char* paragrmone)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, classname, methodname, "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring parameter;
		parameter = info.env->NewStringUTF(paragrmone);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, parameter);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(parameter);
	}
}
// 转换函数二：返回bool，一个string参数
bool com_CrossApp_IM_IM::CallStaticMethod_bool(const char* classname, const char* methodname, const char* paragrmone)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, classname, methodname, "(Ljava/lang/String;)Z");
	if (isHave)
	{
		jstring parameter = info.env->NewStringUTF(paragrmone);
		jboolean result_android = info.env->CallStaticBooleanMethod(info.classID, info.methodID, parameter);
		bool result = result_android;
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(parameter);
		return result;
	}
}
//转换函数三：返回void，俩个string参数
void com_CrossApp_IM_IM::CallStaticMethod_void(const char* classname, const char* methodname, const char* paragrmone,const char* paragrmtwo)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, classname, methodname, "(Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave)
	{
		jstring parameter;
		jstring parametersecond;
		parameter = info.env->NewStringUTF(paragrmone);
		parametersecond = info.env->NewStringUTF(paragrmtwo);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, parameter, parametersecond);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(parameter);
		info.env->DeleteLocalRef(parametersecond);
	}
}
//转换函数四：返回bool，俩个string参数
bool com_CrossApp_IM_IM::CallStaticMethod_bool(const char* classname, const char* methodname, const char* paragrmone, const char* paragrmtwo)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, classname, methodname, "(Ljava/lang/String;Ljava/lang/String;)Z");
	if (isHave)
	{
		jstring parameter;
		jstring parametersecond;
		parameter = info.env->NewStringUTF(paragrmone);
		parametersecond = info.env->NewStringUTF(paragrmtwo);
		jboolean result_android = info.env->CallStaticBooleanMethod(info.classID, info.methodID, parameter, parametersecond);
		bool result = result_android;
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(parameter);
		info.env->DeleteLocalRef(parametersecond);
		return result;
	}
}
//转换函数五：返回void，三个string参数
void com_CrossApp_IM_IM::CallStaticMethod_void(const char* classname, const char* methodname, const char* paragrmone, const char* paragrmtwo, const char* paragrmthree)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, classname, methodname, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave)
	{
		jstring parameter;
		jstring parametersecond;
		jstring parameterthird;
		parameter = info.env->NewStringUTF(paragrmone);
		parametersecond = info.env->NewStringUTF(paragrmtwo);
		parameterthird = info.env->NewStringUTF(paragrmthree);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, parameter, parametersecond, parameterthird);
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(parameter);
		info.env->DeleteLocalRef(parametersecond);
		info.env->DeleteLocalRef(parameterthird);
	}
}
//转换函数六，返回bool，三个string参数
bool com_CrossApp_IM_IM::CallStaticMethod_bool(const char* classname, const char* methodname, const char* paragrmone, const char* paragrmtwo,const char* paragrmthree)
{
	JniMethodInfo info;
	bool isHave = JniHelper::getStaticMethodInfo(info, classname, methodname, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z");
	if (isHave)
	{
		jstring parameter;
		jstring parametersecond;
		jstring parameterthird;
		parameter = info.env->NewStringUTF(paragrmone);
		parametersecond = info.env->NewStringUTF(paragrmtwo);
		parameterthird = info.env->NewStringUTF(paragrmthree);
		jboolean result_android = info.env->CallStaticBooleanMethod(info.classID, info.methodID, parameter, parametersecond, parameterthird);
		bool result = result_android;
		info.env->DeleteLocalRef(info.classID);
		info.env->DeleteLocalRef(parameter);
		info.env->DeleteLocalRef(parametersecond);
		info.env->DeleteLocalRef(parameterthird);
		return result;
	}
}