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
, m_bIsRegister(false)
,m_sUserName("")
,m_sUserPassword("")
{
    
}

HXSDKController::~HXSDKController()
{
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
    HXSDKControllerIOS::RegisTerAccount_ios(name, passWord);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::registerAccount_android(name,passWord);
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



 bool HXSDKController::isRegister()
 {
	 return m_bIsRegister;
 }


std::vector<HXSDKGroup*> HXSDKController::getPublicGroupList()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::getPublicGroup_ios();

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
#endif
    
    CCLog("获取公开群.%lu 个",m_vPublicGroupList.size());
    return m_vPublicGroupList;
}
void HXSDKController:: createGroup(HXSDKGroupStyle groupType,const char* gName,const char* gDescription)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::createGroup_ios(groupType, gName, gDescription);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif

}

std::vector<HXSDKGroup*> HXSDKController:: getMyGroupList()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::getMyGroup_ios();

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
    
    CCLog("获取我的群.%lu 个",m_vMyGroupList.size());
    return m_vMyGroupList;
}

bool HXSDKController::isLogin()
{
    return m_bIsLogin;
}

/**********************************************************************************/


void HXSDKController::cleanGroupList()
{
    std::vector<HXSDKGroup*>::iterator itr = m_vPublicGroupList.begin();
    for(; itr != m_vPublicGroupList.end(); ++itr)
    {
        CC_SAFE_DELETE(*itr);
    }
}

void HXSDKController::pushGroupsDetail(std::string groupID,std::string groupSub, std::string groupDes,int groupOccupantsCount)
{
    HXSDKGroup* sdkGroup = new HXSDKGroup();
    sdkGroup->m_sGroupId = groupID;
    sdkGroup->m_sGroupSubject = groupSub;
    sdkGroup->m_sGroupDescription = groupDes;
    sdkGroup->m_iGroupOccupantsCount = groupOccupantsCount;
    
    m_vPublicGroupList.push_back(sdkGroup);
}

void HXSDKController::cleanMyGroupList()
{
    std::vector<HXSDKGroup*>::iterator itr = m_vMyGroupList.begin();
    for(; itr != m_vMyGroupList.end(); ++itr)
    {
        CC_SAFE_DELETE(*itr);
    }
}

void HXSDKController::pushMyGroupsDetail(std::string groupID, std::string groupSub, std::string groupDes, int groupOccupantsCount)
{
    HXSDKGroup* sdkGroup = new HXSDKGroup();
    sdkGroup->m_sGroupId = groupID;
    sdkGroup->m_sGroupSubject = groupSub;
    sdkGroup->m_sGroupDescription = groupDes;
    sdkGroup->m_iGroupOccupantsCount = groupOccupantsCount;
    
    m_vMyGroupList.push_back(sdkGroup);
}

/***************************************NotificationCenter*******************************************/
void HXSDKController::postNotification_isRegister(bool isRegister)
{
	m_bIsRegister = isRegister;
	CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_REGISTER, (CAObject*)isRegister);
}

void HXSDKController::postNotification_isLogin(bool isLogin)
{
    m_bIsLogin = isLogin;
    CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_LOGIN, (CAObject*)isLogin);
}

void HXSDKController::postNotification_isLogOut(bool isLogout)
{
    m_bIsLogin = !isLogout;
	CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_LOGOUT, (CAObject*)isLogout);
}

void HXSDKController::postNotification_sendMessageResult(bool success)
{
    CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_SENDMESSAGE_RESULT, (CAObject*)success);
}


























