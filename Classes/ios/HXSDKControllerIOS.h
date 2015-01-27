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
    
    static void sendAddFriend_ios(const char* accountName, const char* message);
    
    static void getFriendsList_ios();

    // 同意好友申请
    static void acceptContact(const char* toUserName);
    // 拒绝好友申请
    static void refuseContact(const char* toUserName,const char* reason);
    // 删除好友

    //删除用户名 , 是否将自己从对方列表中删除.
    static void deleteContact(const char* userName,bool removeSelf);
    // 查看公开群
    static void seePublicGroup();
    // 加入不需要验证的群
    static void joinNoNeedCheckGroup(const char* groupID);
    // 加入需要验证的群组
    static void joinNeedCheckGroup(const char* groupID, const char* groupName,const char* message);
    // 退出群 退出群组，如果是群成员调用，则为成员离开，如果是创建者离开，则视为群组解散
    static void exitGroup(const char* groupID);
    //解散群组（需要有群主权限）
    static void destoryGroup(const char* groupID);
    

    
protected:
    
};


#endif /* defined(__HelloCpp__HXSDKControllerIOS__) */
