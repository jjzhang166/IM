//
//  HXSDKController.h
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-13.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
                                                                                                                                                     
#ifndef __HelloCpp__HXSDKController__
#define __HelloCpp__HXSDKController__

#include <iostream>
#include "CrossApp.h"
#include "HXSDKBuddy.h"

USING_NS_CC;

class HXSDKController
{
public:

	HXSDKController();
    
	virtual ~HXSDKController();
    
    static HXSDKController* getInstance();
    
    bool initSDK();
    /*登陆前注册*/
    void LoginBefore(CrossApp::CAObject *target, SEL_CallFuncO selector, CrossApp::CAObject *obj);
    /*登陆*/
    void Login(const char* name, const char* passWord);
    /*注册*/
    void RegisterAccount(const char* name, const char* passWord);
    /*退出登陆*/
    void Logout();
    /*发送消息*/
    void sendMessage(const char* messageText, const char* toUserName);
    /*发送图片消息*/
    void sendMessageWithImage(const char* messageText, const char* toUserName);
    
    /*add friend*/
    void sendAddFriend(const char* accountName, const char* message);
    /*get friends list*/
    std::vector<HXSDKBuddy*> getFriendsList();
    
    bool isLogin();
    
    
public:
    /*CANotificationCenter*/
    void postNotification_isLogin(bool isLogin);
    
    void postNotification_isLogOut(bool isLogout);
    
    void postNotification_sendMessageResult(bool success);
    
public:
    /*Data*/
    void cleanFriendsLise();
    
    void pushFriendsDetail(std::string userName, HXSDKBuddyFollowState eHXSDKEMBuddyFollowState, bool isPendingApproval);
    
protected:
    std::string     m_sUserName;
    std::string     m_sUserPassword;
    bool            m_bIsLogin;
    
    std::vector<HXSDKBuddy*> m_vFriendList;
    
};
#endif /* defined(__HelloCpp__HXSDKController__) */
