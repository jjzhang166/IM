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
        m_sUserName = "";
        m_eFollowState = eHXSDKEMBuddyFollowState_UnKnow;
        m_bIsPendingApproval = false;
    }
    ~HXSDKBuddy()
    {
        
    }
    
public:
    std::string             m_sUserName;
    HXSDKBuddyFollowState   m_eFollowState;
    bool                    m_bIsPendingApproval;
};


#endif /*defined(__IM__HXSDKBUDDY__)*/