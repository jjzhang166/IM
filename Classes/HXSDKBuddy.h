//
//  HXSDKBuddy.h
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-27.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#ifndef __IM__HXSDKBUDDY__
#define __IM__HXSDKBUDDY__

#include "CrossApp.h"
#include "CrossAppExt.h"
#include <iostream>

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum{
	eHXSDKEMBuddyFollowState_NotFollowed = 0,    //双方不是好友
	eHXSDKEMBuddyFollowState_Followed,           //对方已接受好友请求.
	eHXSDKEMBuddyFollowState_BeFollowed,         //登录用户已接受了该用户的好友请求
	eHXSDKEMBuddyFollowState_FollowedBoth,        //"登录用户"和"小伙伴"都互相在好友列表中
	eHXSDKEMBuddyFollowState_UnKnow              //不知道
} HXSDKBuddyFollowState;

class HXSDKBuddy
{
public:
	HXSDKBuddy()
	{
        m_iUserID = 0;
		m_sUserName = "";
		m_eFollowState = eHXSDKEMBuddyFollowState_UnKnow;
		m_bIsPendingApproval = false;
	}
	~HXSDKBuddy()
	{

	}

public:
    int                     m_iUserID;
	std::string             m_sUserName;
	HXSDKBuddyFollowState   m_eFollowState;
	bool                    m_bIsPendingApproval;
};


//群组分为两大类，四小类
/*!
@enum
@brief 群组类型
@constant eGroupStyle_PrivateOnlyOwnerInvite 私有群组，只能owner权限的人邀请人加入
@constant eGroupStyle_PrivateMemberCanInvite 私有群组，owner和member权限的人可以邀请人加入
@constant eGroupStyle_PublicJoinNeedApproval 公开群组，允许非群组成员申请加入，需要管理员同意才能真正加入该群组
@constant eGroupStyle_PublicOpenJoin         公开群组，允许非群组成员加入，不需要管理员同意
@constant eGroupStyle_PublicAnonymous        公开匿名群组，允许非群组成员加入，不需要管理员同意
@constant eGroupStyle_Default                默认群组类型
@discussion
eGroupStyle_Private：私有群组，只允许群组成员邀请人进入
eGroupStyle_Public： 公有群组，允许非群组成员加入
*/

typedef enum {
	eHXSDKGroupStyle_PrivateOnlyOwnerInvite = 0, //私有群组，只能owner权限的人邀请人加入
	eHXSDKGroupStyle_PrivateMemberCanInvite,    //私有群组，owner和member权限的人可以邀请人加入
	eHXSDKGroupStyle_PublicJoinNeedApproval,    //公开群组，允许非群组成员申请加入，需要管理员同意才能真正加入该群组
	eHXSDKGroupStyle_PublicOpenJoin,            //公开群组，允许非群组成员加入，不需要管理员同意
	eHXSDKGroupStyle_PublicAnonymous,           //公开匿名群组，允许非群组成员加入，不需要管理员同意
	eHXSDKGroupStyle_Default = eHXSDKGroupStyle_PrivateOnlyOwnerInvite,
}HXSDKGroupStyle;
class HXSDKGroup
{
public:
	HXSDKGroup()
	{
        m_sGroupId = "";
		m_sGroupSubject = "";
		m_sGroupDescription = "";
		m_iGroupOccupantsCount = 200;
		m_eGroupType = eHXSDKGroupStyle_Default;
        m_sGroupOwer = "";
        m_bIsPushNotificationEnable = true;
        m_bIsJoined = false;
	}
	~HXSDKGroup()
    {
        m_vMenbers.clear();
	}

public:
	//    目前群组支持的属性有:
	//    群组id
	std::string  m_sGroupId;
	//    群名称
	std::string  m_sGroupSubject;
	//    群描述
	std::string  m_sGroupDescription;
	//    群人数（不支持修改，目前上限为2000人）
	int         m_iGroupOccupantsCount;
	//    群类型（即上面提到的四种群组类型）
	HXSDKGroupStyle   m_eGroupType;
    //    群主
    std::string m_sGroupOwer;
    //    是否推动消息
    bool        m_bIsPushNotificationEnable;
    //    群成员
    std::vector<HXSDKBuddy*> m_vMenbers;
    // 是否已经加入该群
    bool        m_bIsJoined;
    
    virtual bool isEqual(HXSDKGroup*pObject)
    {

        if (m_sGroupId == pObject->m_sGroupId) {
            return true;
        }
        
        return false;
    };

};

//消息体
typedef enum{
	TXTMESSAGE = 0,
	IMAGEMESSAGE = 1,
	VOICEMESSAGE = 2
}HXSDKMsgType;
typedef enum{
	CHATSTYLE_CHAT = 0,
	CHATSTYLE_GROUP =1
}HXSDKChatStyle;
class HXSDKMessage
{
public:
	HXSDKMessage()
	{
		m_vType = TXTMESSAGE;
		m_vTime = 0.0;
		m_vSend = "";
		m_vReceive = "";
		m_vChatStyle = CHATSTYLE_CHAT;
		m_vMessage = "";
	}
	~HXSDKMessage()
	{

	}

public:
	HXSDKMsgType m_vType;  //消息类型
	long m_vTime;  //消息发送时间
	std::string m_vSend; //消息发送者
	std::string m_vReceive;  //消息接收者
	HXSDKChatStyle m_vChatStyle;
	std::string m_vMessage;
};


#endif /*defined(__IM__HXSDKBUDDY__)*/