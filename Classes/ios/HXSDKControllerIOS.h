//
//  HXSDKControllerIOS.h
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-13.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#ifndef __HelloCpp__HXSDKControllerIOS__
#define __HelloCpp__HXSDKControllerIOS__

#include <iostream>
#include "CrossApp.h"


class HXSDKControllerIOS
{
    
public:
    
    HXSDKControllerIOS();
    
    virtual ~HXSDKControllerIOS();
    
    static bool init_ios();
    
    static bool Login_ios(const char* name, const char* passWord);
    
    static bool RegisTerAccount_ios(const char* name, const char* passWord);
    
    static void Logout_ios();
    
    static void sendMessage_ios(const char* messageText, const char* toUserName);
    
    static void sendMessageWithImage_ios(const char* messageImage, const char* toUserName);
    // 同意好友申请
    static void acceptContact(const char* toUserName);
    // 拒绝好友申请
    static void refuseContact(const char* toUserName,const char* reason);
    // 删除好友
    /**
     * 删除用户名 , 是否将自己从对方列表中删除.
     */
    static void deleteContact(const char* userName,BOOL removeSelf);
    // 查看公开群
    static void seePublicGroup();
    // 加入不需要验证的群
    static void joinNoNeedCheckGroup(const char* groupID);
    // 加入需要验证的群组
    static void joinNeedCheckGroup(const char* groupID, const char* groupName,const char* message);
    
protected:
    
};


#endif /* defined(__HelloCpp__HXSDKControllerIOS__) */
