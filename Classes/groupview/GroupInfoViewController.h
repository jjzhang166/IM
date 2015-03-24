//
//  GroupInfoViewController.h
//  IM
//
//  Created by chenq on 15-1-16.
//
//

#ifndef __IM__GroupInfoViewController__
#define __IM__GroupInfoViewController__

#include <iostream>
#include "crossApp.h"

USING_NS_CC;


struct GroupInfo
{
    std::string     m_sGroupID; // 群ID
    CAImage *       m_pFaceImg; // 群照片
    std::string     m_sTopic; // 主题
    std::string     m_sIntroduce;   // 介绍
    std::string     m_sOwner;   // 群主
    int             m_itotal;  // 群成员数
    std::string     m_sLimit; // 权限
    std::string     m_sTotalStr;
    bool            m_bIsNotice;    // 新消息提醒

};




class GroupInfoViewController : public CAViewController
{
    public :
    
    GroupInfoViewController();
    virtual ~GroupInfoViewController();
    static GroupInfoViewController* create(GroupInfo info,bool joined);
    virtual bool init(GroupInfo info,bool joined);
    
protected:
    void viewDidLoad();
    void viewDidUnLoad();
    
public :
    void onButtonBack(CAControl *pTarget, CCPoint point); // 返回按钮
    void onSwitchChanged(CAControl *target,CCPoint point); // 消息提醒开关
    void onButtonJoin(CAControl* target, CCPoint point); //加入群
    void onButtonExit(CAControl* target,CCPoint point);
    void onButtonGroupMenbers(CAControl* target, CCPoint point);//群成员列表
protected:
    GroupInfo m_info;
    bool m_joined; //已加入
    
    CAImageView*    m_imgViewHead; // 头像
    CALabel*        m_LabelTopic; // 主题
    CALabel*        m_LabelIntroduce; // 介绍
    CALabel*        m_LabelOwner; // 群主
    CALabel*        m_LabelMember;    // 群成员人数
    CALabel*        m_LabelLimit;  // 加入权限
    CASwitch*       m_SwitchNotice;   // 新消息提醒
    CAButton*       m_ExitButton;    // 退群按钮

    
    
};

#endif /* defined(__IM__GroupInfoViewController__) */
