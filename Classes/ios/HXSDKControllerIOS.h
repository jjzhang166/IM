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
#include "HXSDKBuddy.h"


class HXSDKControllerIOS
{
    
public:
    
    HXSDKControllerIOS();
    
    virtual ~HXSDKControllerIOS();
    
    static bool init_ios();
    
    static bool Login_ios(const char* name, const char* passWord);
    
    static bool RegisterAccount_ios(const char* name, const char* passWord);
    
    static void Logout_ios();
    
    static void sendMessage_ios(const char* messageText, const char* toUserName);
    
    static void sendMessageWithImage_ios(const char* messageImage, const char* toUserName);
    
    static void sendAddFriend_ios(const char* accountName, const char* message);
    
    static void getFriendsList_ios();

    // 同意好友申请
    static void acceptContact_ios(const char* toUserName);
    // 拒绝好友申请
    static void refuseContact_ios(const char* toUserName,const char* reason);

    //删除 用户名 , 是否将自己从对方列表中删除.
    static void deleteContact_ios(const char* userName,bool removeSelf);
 
    // 加入不需要验证的群
    static void joinNoNeedCheckGroup_ios(const char* groupID);
    // 加入需要验证的群组
    static void joinNeedCheckGroup_ios(const char* groupID, const char* groupName,const char* message);
    // 退出群 退出群组，如果是群成员调用，则为成员离开，如果是创建者离开，则视为群组解散
    static void exitGroup_ios(const char* groupID);
    //解散群组（需要有群主权限）
    static void destoryGroup_ios(const char* groupID);
    
    // 查看公开群
    static void getPublicGroup_ios();
    // 创建群
    static void createGroup_ios(HXSDKGroupStyle groupType,const char* gName,const char* gDescription);
    // 查看我加入的群
    static void getMyGroup_ios();
    //查找群成员
    static void getGroupMenberListByID_ios(const char * groupID);
    //接收消息
//    
//    -(void)didReceiveMessage:int pMessageType (EMMessage *)message
//    static void pushMessageDetail(int pMessageType, long pTime, NSString* pSendName, NSString* pReceiveName, int pChatStyle, NSString* pMessage);
protected:
    
};


#endif /* defined(__HelloCpp__HXSDKControllerIOS__) */

//
//
//@interface HXSDKControllerIOS : NSObject
//
//-(void)pushMessageDetail:(NSString *)pMessageType time:(long)pTime frome:(NSString*)name to:(NSString*)name chatStyle:(int)pCHatStyle message:(NSString*)pMessage
//@end
