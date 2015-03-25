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
    /*自动登录*/
    void autoLogin();
	/*注册*/
	void RegisterAccount(const char* name, const char* passWord);
	/*退出登陆*/
	void Logout();

	/*发送消息*/
	void sendMessage(const char* messageText, const char* toUserName);
	void receiveMessage();
	/*发送图片消息*/
	void sendMessageWithImage(const char* messageText, const char* toUserName);

	/*获取消息-chinahypo-2015-3-19*/
	std::vector<HXSDKMessage*> loadMessage(const char* generalname);

	/*add friend*/
	void sendAddFriend(const char* accountName, const char* message);
	/*get friends list*/
	std::vector<HXSDKBuddy*> getFriendsList();

	/*获取公开群*/
	std::vector<HXSDKGroup*>& getPublicGroupList();
	/*创建群*/
	void createGroup(HXSDKGroupStyle groupType, const char* gName, const char* gDescription);
	/*获取已加入的群*/
	std::vector<HXSDKGroup*> getMyGroupList();
    /*请求群组成员信息*/
    std::vector<HXSDKBuddy*> getGroupMemberListByID(std::string groupID);

    std::string getMyName();



	/*群删除成员******************************************************/
	void joinNoNeedCheckGroup(const char* groupId);
	void joinNeedCheckGroup(const char* groupId, const char* groupName, const char* message);
	void exitGroup(const char* groupId);
	void destroyGroup(const char* groupId);
	void addUserToGroup(const char* groupId, std::vector<char*> usernames);
	void inviteUser(const char* groupId, std::vector<char*> usernames, const char* message);
	void deleteUserFromGroup(const char* groupId, const char* userName);
	void blockGroupMessage(const char* groupId);
	void unblockGroupMessage(const char* groupId);
	void changeGroupName(const char* groupId, const char* newgroupName);
	void setReceiveNotNoifyGroup(std::vector<char*> groupIds);
	void blockUser(const char* groupId, const char* username);
	void unblockUser(const char* groupId, const char* username);
	//获取群组黑名单void getBlockedUsers(const char* groupId);
	/********************************************************************/

	bool isLogin();
	bool isRegister();
public:
	/*CANotificationCenter*/
	void postNotification_isRegister(bool isRegister);
	void postNotification_isLogin(bool isLogin);
	void postNotification_isLogOut(bool isLogout);
	void postNotification_sendMessageResult(bool success);
    
    void createGroupResult(bool result);
    void exitGroupResult(bool result);

public:
	/*Data*/
	void cleanFriendsLise();

	void pushFriendsDetail(std::string userName, HXSDKBuddyFollowState eHXSDKEMBuddyFollowState, bool isPendingApproval);

	void cleanGroupList();
	// id, 群主题(名称) ,群描述 , 群成员,
	void pushGroupsDetail(std::string groupID, std::string groupSub, std::string groupDes, int groupOccupantsCount, std::string ower, int groupStyle, bool isNotificationEnable);
    void setGroupsDetailByID(const char* groupID, const char* groupSub, const char* groupDes, int groupOccupantsCount, const char* ower, int groupStyle, bool isNotificationEnable);

	void cleanMyGroupList();
	void pushMyGroupsDetail(std::string groupID, std::string groupSub, std::string groupDes, int groupOccupantsCount);

    void setGroupMembersByID(std::string groupID, std::vector<HXSDKBuddy*> members);
    std::vector<HXSDKBuddy*> groupMenberListByID(std::string groupID);
	//Message chinahypo-2015-3-19
	void pushMessageDetail(int pMessageType, long pTime, std::string pSendName, std::string pReceiveName, int pChatStyle,std::string pMessage);
	void cleanMessageList();
    
protected:
	std::string     m_sUserName;
	std::string     m_sUserPassword;
	bool            m_bIsLogin;
	bool			m_bIsRegister;
	std::vector<HXSDKBuddy*> m_vFriendList;
	std::vector<HXSDKGroup*> m_vPublicGroupList;
	std::vector<HXSDKGroup*> m_vMyGroupList;
	std::vector<HXSDKMessage*> m_vMessageList;
	
    
};
#endif /* defined(__HelloCpp__HXSDKController__) */
