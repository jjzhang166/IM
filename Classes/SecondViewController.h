//
//  SecondViewController.h
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-9.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#ifndef __SECOND_VIEW_CONTROLLER__
#define __SECOND_VIEW_CONTROLLER__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class SecondViewController : public CAViewController, public CATextFieldDelegate
{
    
public:
    
    SecondViewController();
    
    virtual ~SecondViewController();
    
    virtual bool init();
protected:
    
    virtual void viewDidLoad();
    
    virtual void viewDidUnload();
    
    virtual void viewDidAppear();
    
    void init_searchBar();
    
    void onButtonAdd(CAControl* control, CCPoint point);//添加按钮回调
    
    /*textFieldDelegate*/
    bool onTextFieldAttachWithIME(CATextField * sender);
    bool onTextFieldDetachWithIME(CATextField * sender);
    virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);
    
protected:
    CANavigationBarItem* m_pNavigationBarItem;
    
    CASegmentedControl* m_pTitleView;
    
    CATextField* m_pSearchTextField;
};


#endif /* defined(__SECOND_VIEW_CONTROLLER__) */