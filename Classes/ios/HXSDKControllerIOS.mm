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
        return true;
    }
    else
    {
        CCLog("HXSDK init failed...");
        return false;
    }
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
             HXSDKController::getInstance()->postNotification_isLogin(true);
             //[[NSNotificationCenter defaultCenter] postNotificationName:@KNOTIFICATION_LOGINCHANGE object:@YES];
             
             EMError *error = [easeMob.chatManager importDataToNewDatabase];
             if (!error) {
                 error = [easeMob.chatManager loadDataFromDatabase];
             }
         }else {
             //[[NSNotificationCenter defaultCenter] postNotificationName:@KNOTIFICATION_LOGINCHANGE object:@NO];
             HXSDKController::getInstance()->postNotification_isLogin(false);
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

bool HXSDKControllerIOS::RegisterAccount_ios(const char* name, const char* passWord)
{
    NSString *string_name = [[NSString alloc] initWithCString:(const char*)name encoding:NSASCIIStringEncoding];
    NSString *string_passWord = [[NSString alloc] initWithCString:(const char*)passWord encoding:NSASCIIStringEncoding];
    
    [easeMob.chatManager asyncRegisterNewAccount:string_name
                                                         password:string_passWord
                                                   withCompletion:
     ^(NSString *username, NSString *password, EMError *error) {
         
         if (!error) {
             HXSDKController::getInstance()->postNotification_isRegister(true);
             HXSDKController::getInstance()->Login(name, passWord);
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
    HXSDKController::getInstance()->postNotification_isLogOut(true);
    CCLog("LogOut is success !!!");
}

void HXSDKControllerIOS::sendMessage_ios(const char* messageText, const char* toUserName, bool isGroup)
{
    NSString *string_messageText = [[NSString alloc] initWithCString:(const char*)messageText encoding:NSASCIIStringEncoding];
    NSString *string_toUserName = [[NSString alloc] initWithCString:(const char*)toUserName encoding:NSASCIIStringEncoding];
    EMChatText *text = [[EMChatText alloc] initWithText:string_messageText];
    EMTextMessageBody *body = [[EMTextMessageBody alloc] initWithChatObject:text];
    EMMessage *msg = [[EMMessage alloc] initWithReceiver:string_toUserName
                                                  bodies:@[body]];
    msg.isGroup = isGroup;
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
    [easeMob.chatManager asyncSendMessage:retureMsg progress:nil];
    
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
    
    if (!error) {
        CCLog("get friends list success!!! %d",buddyList.count);
        HXSDKController::getInstance()->cleanFriendsLise();
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
    }
    else
    {
        CCLog("get friends list fail!!!");
    }
}


void HXSDKControllerIOS::acceptContact_ios(const char* toUserName)
{
    NSString *string_toUserName = [[NSString alloc]initWithCString:(const char *) toUserName encoding:NSASCIIStringEncoding];
    
    EMError *error = nil;
    BOOL isSuccess = [easeMob.chatManager acceptBuddyRequest:string_toUserName error:&error];
    if (isSuccess && !error) {
        NSLog(@"发送同意成功");
    }
}

void HXSDKControllerIOS::refuseContact_ios(const char*toUserName,const char* reason)
{
    NSString* str_user = [[NSString alloc]initWithCString:(const char *) toUserName encoding:NSASCIIStringEncoding];
    NSString * str_reason = [[NSString alloc]initWithCString:(const char *) toUserName encoding:NSASCIIStringEncoding];
    EMError *error = nil;
    BOOL isSuccess = [easeMob.chatManager rejectBuddyRequest:str_user reason:str_reason error:&error];
    if (isSuccess && !error) {
        NSLog(@"发送拒绝成功");
    }
}

void HXSDKControllerIOS::deleteContact_ios(const char *userName,bool removeSelf)
{
    NSString * str_name = [[NSString alloc]initWithCString:(const char *) userName encoding:NSASCIIStringEncoding];
    EMError *error = nil;
    // 删除好友
    BOOL isSuccess = [easeMob.chatManager removeBuddy:str_name removeFromRemote:removeSelf error:&error];
    if (isSuccess && !error) {
        NSLog(@"删除成功");
    }
}

void HXSDKControllerIOS:: joinNoNeedCheckGroup_ios(const char *groupID)
{
    NSString* str_gID = [[NSString alloc]initWithCString:(const char *) groupID encoding:NSASCIIStringEncoding];
    EMError * error = nil;
    [easeMob.chatManager asyncJoinPublicGroup:str_gID completion:^(EMGroup *group, EMError *error) {
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
    
    [easeMob.chatManager asyncApplyJoinPublicGroup:str_gID withGroupname:str_gName message:str_msg completion:^(EMGroup *group, EMError *error) {
        if (!error) {
            NSLog(@"申请成功");
        }
    } onQueue:nil];
}

void HXSDKControllerIOS:: exitGroup_ios(const char *groupID)
{
    NSString* str_gID = [[NSString alloc]initWithCString:(const char *) groupID encoding:NSASCIIStringEncoding];
    [easeMob.chatManager asyncLeaveGroup:str_gID completion:^(EMGroup *group, EMGroupLeaveReason reason, EMError *error) {
        if (!error) {
            NSLog(@"退出群组成功");
            HXSDKController::getInstance()->exitGroupResult(true);
        }
    } onQueue:nil];

}

void HXSDKControllerIOS:: destoryGroup_ios(const char *groupID)
{
    NSString * str_gID = [[NSString alloc]initWithCString:(const char *)groupID encoding:NSASCIIStringEncoding];
    [easeMob.chatManager asyncDestroyGroup:str_gID completion:^(EMGroup *group, EMGroupLeaveReason reason, EMError *error) {
        if (!error) {
            NSLog(@"解散成功");
        }
    } onQueue:nil];

}

void HXSDKControllerIOS:: getPublicGroup_ios()
{
    EMError *error = nil;
    NSArray *publicGroupList = [easeMob.chatManager fetchAllPublicGroupsWithError:&error];
    if (!error) {
        CCLog("get publicGroup List success!!! %d ", publicGroupList.count);
        HXSDKController::getInstance()->cleanGroupList();
        for (int i = 0; i<publicGroupList.count; i++) {

            EMGroup * emGroup = publicGroupList[i];
            std::string gID ;
            std::string gSub;
            std::string gDes;
            std::string gOwner;
            int gOccupantsCount = 0;
            int gGroupStyle = 0;
            bool gIsPushNotification = true;
            
            if (emGroup.groupId) {
               gID = [emGroup.groupId UTF8String];
            }
            if (emGroup.groupSubject) {
                gSub = [emGroup.groupSubject UTF8String];
            }
            
            //NSLog(@"sget public Group success!!! ---%s",[emGroup.groupId UTF8String]);
            //异步查询群详情
            [easeMob.chatManager asyncFetchGroupInfo:emGroup.groupId includesOccupantList:NO completion:^(EMGroup *groupInfo, EMError *error)
            {
                if(!error)
                {
//                    CCLog("get Group Info success!!! ---%s",[groupInfo.groupId UTF8String]);
//                    CCLog("11111111111 groupSub:%s  ",[groupInfo.groupSubject UTF8String]);
//                    CCLog("11111111111 des:%s ",[groupInfo.groupDescription UTF8String]);
//                    CCLog("11111111111 icount:%d ",groupInfo.groupOccupantsCount);
//                    CCLog("11111111111 ower:%s",[groupInfo.owner UTF8String]);
//                    CCLog("11111111111 groupStyle:%d  ",groupInfo.groupSetting.groupStyle);
//                    NSLog(@"get Group Info success!!! ---%s",[groupInfo.groupId UTF8String]);
//                    NSLog(@"group des: ---%s",[groupInfo.groupDescription UTF8String]);
                    
                    const char* des = [groupInfo.groupDescription UTF8String];
                    HXSDKController::getInstance()->setGroupsDetailByID([groupInfo.groupId UTF8String],
                                                                        [groupInfo.groupSubject UTF8String],
                                                                        des,
                                                                         groupInfo.groupOccupantsCount,
                                                                        [groupInfo.owner UTF8String],
                                                                         groupInfo.groupSetting.groupStyle,
                                                                         groupInfo.isPushNotificationEnabled);
                }
            }onQueue:nil];
            //同步查询
//            EMGroup * groupInfo = [easeMob.chatManager fetchGroupInfo:emGroup.groupId error:&error];
//            gDes = [groupInfo.groupDescription UTF8String];
//            gOwner = [groupInfo.owner UTF8String];
//            gOccupantsCount = groupInfo.groupOccupantsCount;
//            gGroupStyle = groupInfo.groupSetting.groupStyle;
//            gIsPushNotification = groupInfo.isPushNotificationEnabled;
            
            HXSDKController::getInstance()->pushGroupsDetail(gID, gSub, gDes, gOccupantsCount, gOwner, gGroupStyle, gIsPushNotification);
        }
    }
    // block 异步同样无法获取 群描述 属性,
//    [easeMob.chatManager asyncFetchAllPublicGroupsWithCompletion:^(NSArray *groups, EMError *error) {
//        if (!error) {
//            NSLog(@"获取成功 -- %@",groups);
//        }
//    } onQueue:nil];
}

void HXSDKControllerIOS:: createGroup_ios(HXSDKGroupStyle groupType,const char* gName,const char* gDescription)
{
    EMError *error = nil;
    EMGroupStyleSetting *groupStyleSetting = [[EMGroupStyleSetting alloc] init];
    
    switch (groupType) {
        case eGroupStyle_PrivateOnlyOwnerInvite:
            groupStyleSetting.groupStyle = eGroupStyle_PrivateOnlyOwnerInvite; // 创建不同类型的群组，这里需要才传入不同的类型
            break;
        case eGroupStyle_PublicAnonymous:
            groupStyleSetting.groupStyle = eGroupStyle_PublicAnonymous;
            break;
        case eGroupStyle_PublicOpenJoin:
            groupStyleSetting.groupStyle = eGroupStyle_PublicOpenJoin;
            break;
        case eGroupStyle_PublicJoinNeedApproval:
            groupStyleSetting.groupStyle = eGroupStyle_PublicJoinNeedApproval;
            break;
        case eGroupStyle_PrivateMemberCanInvite:
            groupStyleSetting.groupStyle = eGroupStyle_PrivateMemberCanInvite;
            break;

        default:
            break;
        }
   
    NSString*  str_gName = [[NSString alloc]initWithCString:(const char *) gName encoding:NSUTF8StringEncoding];
    NSString* str_gDes = [[NSString alloc]initWithCString:(const char *) gDescription encoding:NSUTF8StringEncoding];
    EMGroup *group = [easeMob.chatManager createGroupWithSubject:str_gName description:str_gDes invitees:nil initialWelcomeMessage:nil styleSetting:groupStyleSetting error:&error];
    if(!error){
        NSLog(@"创建成功 -- %@",group);
        HXSDKController::getInstance()->createGroupResult(true);
    }
    else
    {
        HXSDKController::getInstance()->createGroupResult(false);
    }
}


void HXSDKControllerIOS::getMyGroup_ios()
{
    //EMError *error = nil;
    NSArray *myGroups = [easeMob.chatManager groupList];;
    
//    if (!error) {
        CCLog("get MYGroup List success !!!  %d",myGroups.count);
        HXSDKController::getInstance()->cleanMyGroupList();
        for (int i = 0; i<myGroups.count; i++) {

            EMGroup * emGroup = myGroups[i];
            std::string gID ;
            std::string gSub;
            std::string gDes;
            if (emGroup.groupId) {
                gID = [emGroup.groupId UTF8String];
            }
            if (emGroup.groupSubject) {
                gSub = [emGroup.groupSubject UTF8String];
            }
            if (emGroup.groupDescription) {
                gDes = [emGroup.groupDescription UTF8String];
            }
            int gOccupantsCount = emGroup.groupOccupantsCount;
            
            HXSDKController::getInstance()->pushMyGroupsDetail(gID, gSub, gDes, gOccupantsCount);
        }
 //   }
}

void HXSDKControllerIOS::getGroupMenberListByID_ios(const char * groupID)
{
    NSString *string_groupID = [[NSString alloc]initWithCString:(const char *) groupID encoding:NSASCIIStringEncoding];
    
    EMError *error = nil;
    NSArray *myGroupMembers = [easeMob.chatManager fetchOccupantList:string_groupID error:&error];
    if(!error)
    {
        std::vector<HXSDKBuddy*> vec_menmbers;
        for (int i = 0; i<myGroupMembers.count; i++) {
            HXSDKBuddy* buddy = new HXSDKBuddy();
            NSString*   buddyName =[myGroupMembers objectAtIndex:i];
            buddy->m_sUserName = [buddyName UTF8String];
            vec_menmbers.push_back(buddy);
            HXSDKController::getInstance()->setGroupMembersByID(groupID, vec_menmbers);
        }
    }
}
//
//@interface HXSDKControllerIOS
//
// -(void)pushMessageDetail:(NSString *)pMessageType time:(long)pTime frome:(NSString*)name to:(NSString*)name chatStyle:(int)pCHatStyle message:(NSString*)pMessage
//{
//    
//}
//@end

//
//void HXSDKControllerIOS::pushMessageDetail(int pMessageType, long pTime, NSString* pSendName, NSString* pReceiveName, int pChatStyle, NSString* pMessage)
//{
//    
//}





