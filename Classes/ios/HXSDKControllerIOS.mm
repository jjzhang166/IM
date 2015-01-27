//
//  HXSDKControllerIOS.mm
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-13.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#import "HXSDKControllerIOS.h"
#import "EaseMob.h"
#include "IMDATA.h"
#include "HXSDKController.h"
#import "HXSDKHelper.h"


static EaseMob* easeMob = NULL;

//HXSDKControllerIOS* getInstance()
//{
//    if(!easeMob)
//    {
//        return EaseMob;
//    }
//}

bool HXSDKControllerIOS::init_ios()
{
    
    easeMob = [EaseMob sharedInstance];
    NSString *apnsCertName = @"9miao";
    [easeMob registerSDKWithAppKey:@"longtugame#crossappim" apnsCertName:apnsCertName];
    
    HXSDKHelper* helper = [[HXSDKHelper alloc]init];
    [helper registerEaseMobDelegate];
    

    if(easeMob)
    {
        CCLog("HXSDK init success!!!");
        return true;
    }
    
    return false;
}

bool HXSDKControllerIOS::Login_ios(const char* name, const char* passWord)
{
    NSString *string_name = [[NSString alloc] initWithCString:(const char*)name encoding:NSASCIIStringEncoding];
    NSString *string_passWord = [[NSString alloc] initWithCString:(const char*)passWord encoding:NSASCIIStringEncoding];
    
    [easeMob.chatManager asyncLoginWithUsername:string_name
                                                        password:string_passWord
                                                      completion:
     ^(NSDictionary *loginInfo, EMError *error) {

         if (loginInfo && !error) {
             CCLog("登录成功");
             [[NSNotificationCenter defaultCenter] postNotificationName:@KNOTIFICATION_LOGINCHANGE object:@YES];
             
             EMError *error = [easeMob.chatManager importDataToNewDatabase];
             if (!error) {
                 error = [easeMob.chatManager loadDataFromDatabase];
             }
         }else {
             switch (error.errorCode) {
                 case EMErrorServerNotReachable:
                     CCLog("连接服务器失败!");
                     break;
                 case EMErrorServerAuthenticationFailure:
                     CCLog("%s", [error.description cStringUsingEncoding:NSASCIIStringEncoding]);
                     break;
                 case EMErrorServerTimeout:
                     CCLog("连接服务器超时!");
                     break;
                 default:
                     CCLog("登录失败");
                     break;
             }
         }
     } onQueue:nil];
    
    return true;

}

bool HXSDKControllerIOS::RegisTerAccount_ios(const char* name, const char* passWord)
{
    NSString *string_name = [[NSString alloc] initWithCString:(const char*)name encoding:NSASCIIStringEncoding];
    NSString *string_passWord = [[NSString alloc] initWithCString:(const char*)passWord encoding:NSASCIIStringEncoding];
    
    [easeMob.chatManager asyncRegisterNewAccount:string_name
                                                         password:string_passWord
                                                   withCompletion:
     ^(NSString *username, NSString *password, EMError *error) {
         
         if (!error) {
             CCLog("注册成功,请登录");
         }else{
             switch (error.errorCode) {
                 case EMErrorServerNotReachable:
                     CCLog("连接服务器失败!");
                     break;
                 case EMErrorServerDuplicatedAccount:
                     CCLog("您注册的用户已存在!");
                     break;
                 case EMErrorServerTimeout:
                     CCLog("连接服务器超时!");
                     break;
                 default:
                     CCLog("注册失败");
                     break;
             }
         }
     } onQueue:nil];
     return true;
}

void HXSDKControllerIOS::Logout_ios()
{
    [easeMob.chatManager asyncLogoff];
}

void HXSDKControllerIOS::sendMessage_ios(const char* messageText, const char* toUserName)
{
    NSString *string_messageText = [[NSString alloc] initWithCString:(const char*)messageText encoding:NSASCIIStringEncoding];
    NSString *string_toUserName = [[NSString alloc] initWithCString:(const char*)toUserName encoding:NSASCIIStringEncoding];
    EMChatText *text = [[EMChatText alloc] initWithText:string_messageText];
    EMTextMessageBody *body = [[EMTextMessageBody alloc] initWithChatObject:text];
    EMMessage *msg = [[EMMessage alloc] initWithReceiver:string_toUserName
                                                  bodies:@[body]];
    [easeMob.chatManager sendMessage:msg progress:nil error:nil];
    
}

void HXSDKControllerIOS::sendMessageWithImage_ios(const char* messageImage, const char* toUserName)
{
    NSString *string_messageImage = [[NSString alloc] initWithCString:(const char*)messageImage encoding:NSASCIIStringEncoding];
    NSString *string_toUserName = [[NSString alloc] initWithCString:(const char*)toUserName encoding:NSASCIIStringEncoding];
    //将图片读取到内存
    UIImage *image = [UIImage imageNamed:string_messageImage];
    //初始化一个EMChatImage对象
    EMChatImage *chatImage = [[EMChatImage alloc] initWithUIImage:image displayName:@"image"];
    //初始化一个MessageBody对象
    //chatImage：大图
    //thumbnailImage：缩略图（可不传, 传nil系统会自动生成缩略图）
    EMImageMessageBody *body = [[EMImageMessageBody alloc] initWithImage:chatImage thumbnailImage:nil];
    //初始化一个MessageBody数组(目前暂时只支持一个body)
    NSArray *bodies = [NSArray arrayWithObject:body];
    //初始化一个EMMessage对象
    EMMessage *retureMsg = [[EMMessage alloc] initWithReceiver:string_toUserName bodies:bodies];
    //发送数据是否需要加密
    retureMsg.requireEncryption = false;
    //发送图片消息
    [[EaseMob sharedInstance].chatManager asyncSendMessage:retureMsg progress:nil];
    
}




void HXSDKControllerIOS::sendAddFriend_ios(const char* accountName, const char* message)
{
    EMError *error = nil;
    NSString *string_accountName = [[NSString alloc] initWithCString:(const char*)accountName encoding:NSASCIIStringEncoding];
    NSString *string_message = [[NSString alloc] initWithCString:(const char*)message encoding:NSASCIIStringEncoding];
    BOOL isSuccess = [easeMob.chatManager addBuddy:string_accountName message:string_message error:&error];
    if (isSuccess && !error) {
        CCLog("add friend success!!!");
    }
    else
    {
        CCLog("add friend fail!!!");
    }
}

void HXSDKControllerIOS::getFriendsList_ios()
{
    EMError *error = nil;
    NSArray *buddyList = [easeMob.chatManager fetchBuddyListWithError:&error];
    
    for(int i=0; i<buddyList.count; ++i)
    {
        EMBuddy* buddy = buddyList[i];
        std::string userName = [buddy.username UTF8String];
        bool isPendingApproval = buddy.isPendingApproval;
        HXSDKBuddyFollowState eHXSDKEMBuddyFollowState;
        if( eEMBuddyFollowState_NotFollowed == buddy.followState)
        {
            eHXSDKEMBuddyFollowState = eHXSDKEMBuddyFollowState_NotFollowed;
        }
        else if( eEMBuddyFollowState_Followed == buddy.followState)
        {
            eHXSDKEMBuddyFollowState = eHXSDKEMBuddyFollowState_Followed;
        }
        else if( eEMBuddyFollowState_BeFollowed == buddy.followState)
        {
            eHXSDKEMBuddyFollowState = eHXSDKEMBuddyFollowState_BeFollowed;
        }
        else if( eEMBuddyFollowState_FollowedBoth == buddy.followState)
        {
            eHXSDKEMBuddyFollowState = eHXSDKEMBuddyFollowState_FollowedBoth;
        }
        
        HXSDKController::getInstance()->pushFriendsDetail(userName, eHXSDKEMBuddyFollowState, isPendingApproval);
    }
//Log qiaoxin
    if (!error) {
       CCLog("get friends list success!!! %d",buddyList.count);
    }
    else{
        CCLog("get friends list fail!!!");
    }
}


void HXSDKControllerIOS::acceptContact_ios(const char* toUserName)
{
    NSString *string_toUserName = [[NSString alloc]initWithCString:(const char *) toUserName encoding:NSASCIIStringEncoding];
    
    EMError *error = nil;
    BOOL isSuccess = [[EaseMob sharedInstance].chatManager acceptBuddyRequest:string_toUserName error:&error];
    if (isSuccess && !error) {
        NSLog(@"发送同意成功");
    }
}



void HXSDKControllerIOS::refuseContact_ios(const char*toUserName,const char* reason)
{
    NSString* str_user = [[NSString alloc]initWithCString:(const char *) toUserName encoding:NSASCIIStringEncoding];
    NSString * str_reason = [[NSString alloc]initWithCString:(const char *) toUserName encoding:NSASCIIStringEncoding];
    EMError *error = nil;
    BOOL isSuccess = [[EaseMob sharedInstance].chatManager rejectBuddyRequest:str_user reason:str_reason error:&error];
    if (isSuccess && !error) {
        NSLog(@"发送拒绝成功");
    }
}



void HXSDKControllerIOS::deleteContact_ios(const char *userName,bool removeSelf)
{
    NSString * str_name = [[NSString alloc]initWithCString:(const char *) userName encoding:NSASCIIStringEncoding];
    EMError *error = nil;
    // 删除好友
    BOOL isSuccess = [[EaseMob sharedInstance].chatManager removeBuddy:str_name removeFromRemote:removeSelf error:&error];
    if (isSuccess && !error) {
        NSLog(@"删除成功");
    }
}

void HXSDKControllerIOS:: seePublicGroup_ios()
{

    
}

void HXSDKControllerIOS:: joinNoNeedCheckGroup_ios(const char *groupID)
{
    NSString* str_gID = [[NSString alloc]initWithCString:(const char *) groupID encoding:NSASCIIStringEncoding];
    EMError * error = nil;
    [[EaseMob sharedInstance].chatManager asyncJoinPublicGroup:str_gID completion:^(EMGroup *group, EMError *error) {
        if (!error) {
            NSLog(@"入群成功");
        }
    } onQueue:nil];
}

void HXSDKControllerIOS:: joinNeedCheckGroup_ios(const char *groupID,const char* groupName ,const char *message)
{
    NSString* str_gID = [[NSString alloc]initWithCString:(const char *)groupID encoding:NSASCIIStringEncoding];
    NSString* str_gName = [[NSString alloc]initWithCString:(const char *) groupName encoding:NSASCIIStringEncoding];
    NSString* str_msg = [[NSString alloc]initWithCString:(const char *) message encoding:NSASCIIStringEncoding];
    
    [[EaseMob sharedInstance].chatManager asyncApplyJoinPublicGroup:str_gID withGroupname:str_gName message:str_msg completion:^(EMGroup *group, EMError *error) {
        if (!error) {
            NSLog(@"申请成功");
        }
    } onQueue:nil];
}

void HXSDKControllerIOS:: exitGroup_ios(const char *groupID)
{
    NSString* str_gID = [[NSString alloc]initWithCString:(const char *) groupID encoding:NSASCIIStringEncoding];
    [[EaseMob sharedInstance].chatManager asyncLeaveGroup:str_gID completion:^(EMGroup *group, EMGroupLeaveReason reason, EMError *error) {
        if (!error) {
            NSLog(@"退出群组成功");
        }
    } onQueue:nil];

}

void HXSDKControllerIOS:: destoryGroup_ios(const char *groupID)
{
    NSString * str_gID = [[NSString alloc]initWithCString:(const char *)groupID encoding:NSASCIIStringEncoding];
    [[EaseMob sharedInstance].chatManager asyncDestroyGroup:str_gID completion:^(EMGroup *group, EMGroupLeaveReason reason, EMError *error) {
        if (!error) {
            NSLog(@"解散成功");
        }
    } onQueue:nil];

}














