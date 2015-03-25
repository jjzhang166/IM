//
//  AddGroupController.h
//  IM
//
//  Created by qiaoxin on 15-3-25.
//
//

#ifndef __IM__AddGroupController__
#define __IM__AddGroupController__

#include <iostream>
#include "crossApp.h"
#include <stdio.h>

USING_NS_CC;

class AddGroupController : public CAViewController
,public CATableViewDelegate
,public CATableViewDataSource
,public CATextFieldDelegate
{
public :
    
    AddGroupController();
    virtual ~AddGroupController();
    static AddGroupController* create();
    virtual bool init();
    
    void onButtonBack(CAControl *pTarget, CCPoint point); // 返回按钮
    void onButtonAddGroup(CAControl* target, CCPoint point);
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

#endif /* defined(__IM__AddGroupController__) */
