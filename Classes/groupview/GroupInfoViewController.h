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
    GroupInfo(CAImage* _img, std::string _topic,std::string _introduce,std::string _owner,std::string _limit,bool _isON,int _total){
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
    std::string  topic; // 主题
    std::string introduce;   // 介绍
    std::string  owner;   // 群主
    int total;  // 群成员数
    std::string limit; // 权限
    std::string  totalStr ;
    bool noticeOn = false ;    // 新消息提醒

};

//用户登录或者注册事件

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
    void onButtonExit(CAControl* target,CCPoint point);
protected:
    GroupInfo m_info;
    bool m_joined; //已加入
    
    
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
