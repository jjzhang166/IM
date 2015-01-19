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

class GroupInfoViewController : public CAViewController
{
    public :
    
    GroupInfoViewController();
    virtual ~GroupInfoViewController();
    static GroupInfoViewController* create();
    virtual bool init();
    
protected:
    void viewDidLoad();
    void viewDidUnLoad();
    
    public :
    void onButtonBack(CAControl *pTarget, CCPoint point); // 返回按钮
    
protected:
    CAImageView * m_imgViewHead;
    CALabel * m_LabelTopic;
    CALabel * m_LabelIntroduce;
    CALabel * m_LabelOwner;
    CALabel * m_LabelMember;
    CALabel* m_LabelLimit;
    
    CAButton * m_ExitButton;
};

#endif /* defined(__IM__GroupInfoViewController__) */
