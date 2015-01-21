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


class GroupInfo
{
public:

    GroupInfo() {}
    GroupInfo(CAImage* _img, CCString* _topic,CCString* _introduce,CCString*_owner,CCString*_limit,bool _isON,int _total){
        faceImg = _img;
        topic = _topic;
        introduce = _introduce;
        owner = _owner;
        limit = _limit;
        total = _total;
        
        noticeOn = _isON;
    }

    
    string  groupID; // 群ID
     CAImage * faceImg; // 群照片
   CCString  *topic; // 主题
    CCString *introduce;   // 介绍
    CCString  *owner;   // 群主
    int total;  // 群成员数
    CCString *limit; // 权限
    CCString * totalStr ;
    bool noticeOn = false ;    // 新消息提醒

};


class GroupInfoViewController : public CAViewController
{
    public :
    
    GroupInfoViewController();
    virtual ~GroupInfoViewController();
    static GroupInfoViewController* create(GroupInfo info);
    virtual bool init(GroupInfo info);
    
protected:
    void viewDidLoad();
    void viewDidUnLoad();
    
    public :
    void onButtonBack(CAControl *pTarget, CCPoint point); // 返回按钮
    void onSwitchChanged(CAControl *target,CCPoint point); // 消息提醒开关
    void onButtonExit(CAControl* target,CCPoint point);
protected:
    GroupInfo m_info;
    
    CAImageView * m_imgViewHead; // 头像
    CALabel * m_LabelTopic; // 主题
    CALabel * m_LabelIntroduce; // 介绍
    CALabel * m_LabelOwner; // 群主
    CALabel * m_LabelMember;    // 群成员人数
    CALabel* m_LabelLimit;  // 加入权限
    CASwitch* m_SwitchNotice;   // 新消息提醒

    CAButton * m_ExitButton;    // 退群按钮
};

#endif /* defined(__IM__GroupInfoViewController__) */
