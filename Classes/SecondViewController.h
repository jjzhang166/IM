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

class SecondViewController: public CAViewController
{
    
public:

	SecondViewController();
    
	virtual ~SecondViewController();
    
    virtual bool init();
protected:
    
    virtual void viewDidLoad();
    
    virtual void viewDidUnload();
    
    virtual void viewDidAppear();
        
    void onButtonSearch(CAControl* control, CCPoint point);//搜索按钮回调
    
    void onButtonAdd(CAControl* control, CCPoint point);//添加按钮回调
    
    // testIM
    void onButtonLogin(CAControl* control, CCPoint point);
    void onButtonLogOff(CAControl* control, CCPoint point);
    void onButtonSendText(CAControl* control, CCPoint point);
};


#endif /* defined(__SECOND_VIEW_CONTROLLER__) */
