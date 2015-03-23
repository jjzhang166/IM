//
//  GroupCreateViewController.h
//  IM
//
//  Created by lhj on 15/3/23.
//
//

#ifndef __IM__GroupCreateViewController__
#define __IM__GroupCreateViewController__

#include <stdio.h>
#include <iostream>
#include "crossApp.h"

USING_NS_CC;

class GroupCreateViewController : public CAViewController
{
public:
    GroupCreateViewController();
    virtual ~GroupCreateViewController();
    static GroupCreateViewController* create();
    virtual bool init();

protected:
    void viewDidLoad();
    void viewDidUnLoad();
    
    void onCreateBtn(CAControl *pTarget, CCPoint point);
    void onButtonBack(CAControl* control, CCPoint point);
    
protected:
    CAImageView*    m_imgViewHead; // 头像
    CATextField*        m_LabelTopic; // 主题
    CATextField*        m_LabelIntroduce; // 介绍
    CALabel*        m_LabelOwner; // 群主
    CALabel*        m_LabelMember;    // 群成员人数
    CALabel*        m_LabelLimit;  // 加入权限
    CASwitch*       m_SwitchNotice;   // 新消息提醒
    CAButton*       m_ExitButton;    // 退群按钮
};







#endif /* defined(__IM__GroupCreateViewController__) */
