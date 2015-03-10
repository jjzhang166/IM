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
    
	void onButtonSearch(CAControl* control, CCPoint point);//搜索按钮回调

	void onButtonAdd(CAControl* control, CCPoint point);//添加按钮回调

    /*textFieldDelegate*/
    bool onTextFieldAttachWithIME(CATextField * sender);
    bool onTextFieldDetachWithIME(CATextField * sender);
    virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);

	// testIM
	void onButtonLogin(CAControl* control, CCPoint point);
	void onButtonLogOff(CAControl* control, CCPoint point);
	void onButtonSendText(CAControl* control, CCPoint point);
	void onButtonGetFriends(CAControl *control, CCPoint point);
	void onButtonGetGroups(CAControl *control, CCPoint point);
	void onButtonCreateGroup(CAControl *control, CCPoint point);
	void onButtonGetMyGroups(CAControl *control, CCPoint point);


	void friendAdd(); //添加朋友界面函数
	void picview();//覆盖处理函数
	void onDissmiss(CAControl* pTarget, CCPoint point); //添加朋友dismiss函数
private:
	CAView *addFriendView;  //添加朋友界面
	CAView *m_pPicChoserLayer; //覆盖处理界面

    
protected:
    CANavigationBarItem* m_pNavigationBarItem;
    
    CATextField* m_pSearchTextField;

};


#endif /* defined(__SECOND_VIEW_CONTROLLER__) */
