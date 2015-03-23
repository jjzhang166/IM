//
//  AddFriendController.h
//  IM
//
//  Created by qiaoxin on 15-3-23.
//
//

#ifndef __IM__AddFriendController__
#define __IM__AddFriendController__

#include <iostream>
#include "crossApp.h"
#include <stdio.h>

USING_NS_CC;

class AddFriendController : public CAViewController
,public CATableViewDelegate
,public CATableViewDataSource
,public CATextFieldDelegate
{
public :
    
    AddFriendController();
    virtual ~AddFriendController();
    static AddFriendController* create();
    virtual bool init();
    
    void onButtonBack(CAControl *pTarget, CCPoint point); // 返回按钮
    void onButtonAddFriend(CAControl* target, CCPoint point);
protected:
    void viewDidLoad();
    void viewDidUnLoad();

    /*textFieldDelegate*/
    bool onTextFieldAttachWithIME(CATextField * sender);
    bool onTextFieldDetachWithIME(CATextField * sender);
    virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);

protected:
    CATextField*        m_pNameTextField;
    CATextField*        m_pMessageTextField;
    CCSize              m_winSize;
};

#endif /* defined(__IM__AddFriendController__) */
