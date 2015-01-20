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
protected:
 
};
#endif /* defined(__HelloCpp__HXSDKController__) */
