//
//  HXSDKController.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-13.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "HXSDKController.h"
#include "IMDATA.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "HXSDKControllerIOS.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/com_CrossApp_IM_IM.h"
#include <android/log.h>
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"",__VA_ARGS__)
#endif

static HXSDKController* HXsdkController = NULL;

HXSDKController::HXSDKController()
:m_bIsLogin(false)
,m_sUserName("")
,m_sUserPassword("")
{
    
}

HXSDKController::~HXSDKController()
{
    cleanFriendsLise();
    CC_SAFE_DELETE(HXsdkController);
}

HXSDKController* HXSDKController::getInstance()
{
    if(!HXsdkController)
    {
        HXsdkController = new HXSDKController();
        if(HXsdkController->initSDK())
        {
            CCLog("HXSDK init success!!!");
            return HXsdkController;
        }
    }

    return HXsdkController;
}

/*初始化sdk*/
bool HXSDKController::initSDK()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return (HXSDKControllerIOS::init_ios());
    
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    com_CrossApp_IM_IM::init_android();
    return true;
#endif
    
    return true;
}

void HXSDKController::LoginBefore(CrossApp::CAObject *target, SEL_CallFuncO selector,CrossApp::CAObject *obj)
{
    CANotificationCenter::sharedNotificationCenter()->addObserver(target, selector, KNOTIFICATION_LOGIN, obj);
}

void HXSDKController::Login(const char* name, const char* passWord)
{
    m_sUserName = name;
    m_sUserPassword = passWord;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::Login_ios(name, passWord);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::login_android(name,passWord);
#endif
}

void HXSDKController::RegisterAccount(const char* name, const char* passWord)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::RegisterAccount_ios(name, passWord);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
}

void HXSDKController::Logout()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::Logout_ios();
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::logout_android();
    
#endif
}

void HXSDKController::sendMessage(const char *messageText, const char *toUserName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //HXSDKControllerIOS::sendMessage_ios(messageText, toUserName);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
#endif
}
 
void HXSDKController::sendMessageWithImage(const char *messageText, const char *toUserName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//HXSDKControllerIOS::sendMessageWithImage_ios(messageText, toUserName);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


#endif
}

void HXSDKController::sendAddFriend(const char* accountName, const char* message)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::sendAddFriend_ios(accountName, message);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
#endif
}

std::vector<HXSDKBuddy*> HXSDKController::getFriendsList()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::getFriendsList_ios();
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
#endif
    return m_vFriendList;
}

bool HXSDKController::isLogin()
{
    return m_bIsLogin;
}

/****************************************Data******************************************/
void HXSDKController::cleanFriendsLise()
{
    std::vector<HXSDKBuddy*>::iterator itr = m_vFriendList.begin();
    for(; itr != m_vFriendList.end(); ++itr)
    {
        CC_SAFE_DELETE(*itr);
    }
}

void HXSDKController::pushFriendsDetail(std::string userName, HXSDKBuddyFollowState eHXSDKEMBuddyFollowState, bool isPendingApproval)
{
    HXSDKBuddy* sdkBuddy = new HXSDKBuddy();
    sdkBuddy->m_sUserName = userName;
    sdkBuddy->m_eFollowState = eHXSDKEMBuddyFollowState;
    sdkBuddy->m_bIsPendingApproval = isPendingApproval;
    
    m_vFriendList.push_back(sdkBuddy);
}

/***************************************NotificationCenter*******************************************/

void HXSDKController::postNotification_isLogin(bool isLogin)
{
    m_bIsLogin = isLogin;
    CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_LOGIN, (CAObject*)isLogin);
}

void HXSDKController::postNotification_isLogOut(bool isLogout)
{
    m_bIsLogin = !isLogout;
    CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_LOGIN, (CAObject*)isLogout);
}

void HXSDKController::postNotification_sendMessageResult(bool success)
{
    CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_SENDMESSAGE_RESULT, (CAObject*)success);
}


























