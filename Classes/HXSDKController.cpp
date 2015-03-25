//
//  HXSDKController.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-13.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "HXSDKController.h"
#include "IMDATA.h"
#include "LocalStorageUserData.h"
#include "RootWindow.h"
#include "FirstViewController.h"

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
, m_sUserName("")
, m_sUserPassword("")
{

}

HXSDKController::~HXSDKController()
{
	cleanFriendsLise();
	cleanGroupList();
	cleanMyGroupList();
	//chinahypo-2015-3-19
	cleanMessageList();
	CC_SAFE_DELETE(HXsdkController);
}

HXSDKController* HXSDKController::getInstance()
{
	if (!HXsdkController)
	{
		HXsdkController = new HXSDKController();
		if (HXsdkController->initSDK())
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

void HXSDKController::LoginBefore(CrossApp::CAObject *target, SEL_CallFuncO selector, CrossApp::CAObject *obj)
{
	CANotificationCenter::sharedNotificationCenter()->addObserver(target, selector, KNOTIFICATION_LOGIN, obj);
}

void HXSDKController::Login(const char* name, const char* passWord)
{
    CCLog("login user is: %s --- %s", name, passWord);
	m_sUserName = name;
    m_sUserPassword = passWord;
    if(DEBUG_SQLITE3)
    {
        localStorageUserDataSetItem("userName", name);
        localStorageUserDataSetItem("userPassword", passWord);
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	HXSDKControllerIOS::Login_ios(name, passWord);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::login_android(name, passWord);
#endif
}

void HXSDKController::autoLogin()
{
    std::string sName = (char*)localStorageUserDataGetItem("userName");
    std::string sPassword = (char*)localStorageUserDataGetItem("userPassword");
    Login(sName.c_str(), sPassword.c_str());
}

void HXSDKController::RegisterAccount(const char* name, const char* passWord)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	HXSDKControllerIOS::RegisterAccount_ios(name, passWord);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::registerAccount_android(name, passWord);
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
	HXSDKControllerIOS::sendMessage_ios(messageText, toUserName);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::sendMessage_android(messageText,toUserName);
#endif
}

void HXSDKController::receiveMessage()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//HXSDKControllerIOS::sendMessage_ios(messageText, toUserName);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::receiveMessage_android();
#endif
}

void HXSDKController::sendMessageWithImage(const char *messageText, const char *toUserName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//HXSDKControllerIOS::sendMessageWithImage_ios(messageText, toUserName);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //
#endif
}

//chinahypo-2015-3-19
std::vector<HXSDKMessage*> HXSDKController::loadMessage(const char* generalname)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::loadMessage_android(generalname);
#endif
	return m_vMessageList;
}

void HXSDKController::sendAddFriend(const char* accountName, const char* message)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	HXSDKControllerIOS::sendAddFriend_ios(accountName, message);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::addContact_anroid(accountName, message);
#endif
}

std::vector<HXSDKBuddy*> HXSDKController::getFriendsList()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	HXSDKControllerIOS::getFriendsList_ios();

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::getContactUserNames_android();
#endif
	return m_vFriendList;
}

std::vector<HXSDKGroup*>& HXSDKController::getPublicGroupList()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	HXSDKControllerIOS::getPublicGroup_ios();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::getPublicGroup_android();
#endif
	//CCLog("accept group numbers.%lu 个", m_vPublicGroupList.size());
	return m_vPublicGroupList;
}

void HXSDKController::createGroup(HXSDKGroupStyle groupType, const char* gName, const char* gDescription)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	HXSDKControllerIOS::createGroup_ios(groupType, gName, gDescription);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::createGroup_android(groupType,gName,gDescription);
#endif
}

std::vector<HXSDKGroup*> HXSDKController::getMyGroupList()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	HXSDKControllerIOS::getMyGroup_ios();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::getMyGroupList_android();
#endif

	//CCLog("accept my group.%lu 个", m_vMyGroupList.size());
	return m_vMyGroupList;
}

std::vector<HXSDKBuddy*> HXSDKController::getGroupMemberListByID(std::string groupID)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::getGroupMenberListByID_ios(groupID.c_str());
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //
#endif
    return HXSDKController::getInstance()->groupMenberListByID(groupID);
}

void HXSDKController::joinNoNeedCheckGroup(const char* groupId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::joinNoNeedCheckGroup_ios(groupId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::joinNoNeedCheckGroup_android(groupId);
#endif
}

void HXSDKController::joinNeedCheckGroup(const char* groupId, const char* groupName, const char* message)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::joinNeedCheckGroup_android(groupId, groupName,message);
#endif
}

void HXSDKController::exitGroup(const char* groupId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::exitGroup_ios(groupId);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::exitGroup_android(groupId);
#endif
}

void HXSDKController::destroyGroup(const char* groupId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::destroyGroup_android(groupId);
#endif
}

void HXSDKController::addUserToGroup(const char* groupId, std::vector<char*> usernames)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::addUserToGroup_android(groupId, usernames);
#endif
}

void HXSDKController::inviteUser(const char* groupId, std::vector<char*> usernames, const char* message)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::inviteUser_android(groupId, usernames, message);
#endif
}

void HXSDKController::deleteUserFromGroup(const char* groupId, const char* userName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::deleteUserFromGroup_android(groupId, userName);
#endif
}

void HXSDKController::blockGroupMessage(const char* groupId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::blockGroupMessage_android(groupId);
#endif
}

void HXSDKController::unblockGroupMessage(const char* groupId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::unblockGroupMessage_android(groupId);
#endif
}

void HXSDKController::changeGroupName(const char* groupId, const char* newgroupName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::changeGroupName_android(groupId,newgroupName);
#endif
}

void HXSDKController::setReceiveNotNoifyGroup(std::vector<char*> groupIds)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::setReceiveNotNoifyGroup_android(groupIds);
#endif
}

void HXSDKController::blockUser(const char* groupId, const char* username)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::blockUser_android(groupId,username);
#endif
}

void HXSDKController::unblockUser(const char* groupId, const char* username)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	com_CrossApp_IM_IM::unblockUser_android(groupId, username);
#endif
}

/***********************************************************************/
bool HXSDKController::isLogin()
{
	return m_bIsLogin;
}

bool HXSDKController::isRegister()
{
	return m_bIsRegister;
}

std::string HXSDKController::getMyName()
{
    return m_sUserName;
}

/****************************************Data******************************************/
void HXSDKController::cleanFriendsLise()
{
	std::vector<HXSDKBuddy*>::iterator itr = m_vFriendList.begin();
	for (; itr != m_vFriendList.end(); ++itr)
	{
		CC_SAFE_DELETE(*itr);
	}
    m_vFriendList.clear();
}

void HXSDKController::pushFriendsDetail(std::string userName, HXSDKBuddyFollowState eHXSDKEMBuddyFollowState, bool isPendingApproval)
{
	HXSDKBuddy* sdkBuddy = new HXSDKBuddy();
	sdkBuddy->m_sUserName = userName;
	sdkBuddy->m_eFollowState = eHXSDKEMBuddyFollowState;
	sdkBuddy->m_bIsPendingApproval = isPendingApproval;

	m_vFriendList.push_back(sdkBuddy);
}

void HXSDKController::cleanGroupList()
{
	std::vector<HXSDKGroup*>::iterator itr = m_vPublicGroupList.begin();
	for (; itr != m_vPublicGroupList.end(); ++itr)
	{
		CC_SAFE_DELETE(*itr);
	}
    m_vPublicGroupList.clear();
}

void HXSDKController::pushGroupsDetail(std::string groupID, std::string groupSub, std::string groupDes, int groupOccupantsCount, std::string ower, int groupStyle, bool isNotificationEnable)
{
	HXSDKGroup* sdkGroup = new HXSDKGroup();
	sdkGroup->m_sGroupId = groupID;
	sdkGroup->m_sGroupSubject = groupSub;
	sdkGroup->m_sGroupDescription = groupDes;
    sdkGroup->m_iGroupOccupantsCount = groupOccupantsCount;
    sdkGroup->m_sGroupOwer = ower;
    sdkGroup->m_eGroupType = (HXSDKGroupStyle)groupStyle;
    sdkGroup->m_bIsPushNotificationEnable = isNotificationEnable;
	m_vPublicGroupList.push_back(sdkGroup);
}

void HXSDKController::setGroupsDetailByID(const char* groupID, const char* groupSub, const char* groupDes, int groupOccupantsCount, const char* ower, int groupStyle, bool isNotificationEnable)
{
    std::vector<HXSDKGroup*>::iterator itr = m_vPublicGroupList.begin();
    for(; itr!= m_vPublicGroupList.end(); itr++)
    {
        if ( !(*itr)->m_sGroupId.compare(groupID) )
        {
            (*itr)->m_sGroupSubject = groupSub;
            if(groupDes == NULL)
            {
                (*itr)->m_sGroupDescription = "";
            }
            else
            {
                (*itr)->m_sGroupDescription = groupDes;
            }
            (*itr)->m_iGroupOccupantsCount = groupOccupantsCount;
            if(ower == NULL)
            {
                (*itr)->m_sGroupOwer = "";
            }
            else
            {
                (*itr)->m_sGroupOwer = ower;
            }
            (*itr)->m_eGroupType = (HXSDKGroupStyle)groupStyle;
            (*itr)->m_bIsPushNotificationEnable = isNotificationEnable;
            break;
        }
    }
    if(((CATabBarController*)(RootWindow::getInstance()->getNavigationController()->getViewControllerAtIndex(0)))->getSelectedViewControllerAtIndex() == 0)
    {
        ((FirstViewController*)((CATabBarController*)(RootWindow::getInstance()->getNavigationController()->getViewControllerAtIndex(0)))->getViewControllerAtIndex(0))->refreshTableView();
    }
}

void HXSDKController::setGroupMembersByID(std::string groupID, std::vector<HXSDKBuddy *> members)
{
    std::vector<HXSDKGroup*>::iterator itr = m_vPublicGroupList.begin();
    for(; itr!= m_vPublicGroupList.end(); itr++)
    {
        if ( !(*itr)->m_sGroupId.compare(groupID) )
        {
            (*itr)->m_vMenbers.clear();
            for(int i=0; i<members.size(); i++)
            {
                (*itr)->m_vMenbers.push_back(members.at(i));
            }
            break;
        }
    }
}

void HXSDKController::cleanMyGroupList()
{
	std::vector<HXSDKGroup*>::iterator itr = m_vMyGroupList.begin();
	for (; itr != m_vMyGroupList.end(); ++itr)
	{
		CC_SAFE_DELETE(*itr);
	}
    m_vMyGroupList.clear();
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

std::vector<HXSDKBuddy*> HXSDKController::groupMenberListByID(std::string groupID)
{
    std::vector<HXSDKGroup*>::iterator itr = m_vPublicGroupList.begin();
    for(; itr!= m_vPublicGroupList.end(); itr++)
    {
        if ( !(*itr)->m_sGroupId.compare(groupID) )
        {
            return(*itr)->m_vMenbers;
        }
    }
}

void HXSDKController::createGroupResult(bool result)
{
    if(result)
    {
        RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(true);
    }
}

void HXSDKController::exitGroupResult(bool result)
{
    if(result)
    {
        RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(true);
    }
}

//chinahypo - 2015 - 3 - 19
void HXSDKController::pushMessageDetail(int pMessageType, long pTime, std::string pSendName, std::string pReceiveName, int pChatStyle, std::string pMessage)
{
	HXSDKMessage* chatMessage = new HXSDKMessage();
	chatMessage->m_vType = (HXSDKMsgType)pMessageType;
	chatMessage->m_vTime = pTime;
	chatMessage->m_vSend = pSendName;
	chatMessage->m_vReceive = pReceiveName;
	chatMessage->m_vChatStyle = (HXSDKChatStyle)pChatStyle;
	chatMessage->m_vMessage = pMessage;
	m_vMessageList.push_back(chatMessage);
}

void HXSDKController::cleanMessageList()
{
	std::vector<HXSDKMessage*>::iterator itr = m_vMessageList.begin();
	for (; itr != m_vMessageList.end(); itr++)
	{
		CC_SAFE_DELETE(*itr);
	}
	m_vMessageList.clear();
}

/**********************NotificationCenter*************************/
void HXSDKController::postNotification_isRegister(bool isRegister)
{
	m_bIsRegister = isRegister;
	CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_REGISTER, (CAObject*)isRegister);
}

void HXSDKController::postNotification_isLogin(bool isLogin)
{
	m_bIsLogin = isLogin;
	CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_LOGIN, (CAObject*)isLogin);
    if(m_bIsLogin)
    {
        RootWindow::getInstance()->init_ViewController();
    }
}

void HXSDKController::postNotification_isLogOut(bool isLogout)
{
	m_bIsLogin = !isLogout;
    localStorageUserDataSetItem("userName", "");
    localStorageUserDataSetItem("userPassword", "");
	CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_LOGOUT, (CAObject*)isLogout);
    RootWindow::getInstance()->init_LoginController();
}

void HXSDKController::postNotification_sendMessageResult(bool success)
{
	CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_SENDMESSAGE_RESULT, (CAObject*)success);
}


























