//
//  AddFriendView.h
//  CrossApp
//
//  Created by chinahypo.
//  Copyright (c) 2015Äê CrossApp. All rights reserved.
//

#ifndef __ADDFRIEND_VIEW_H__
#define __ADDFRIEND_VIEW_H__
#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class AddFriendView;
typedef void (CAObject::*SEL_AddFriendView)(AddFriendView*, int index);
#define AddFriendView_selector(_SELECTOR) (SEL_AddFriendView)(&_SELECTOR)
#define WIDTH _px(240)
#define HEIGHT _px(85)

class AddFriendView :public CAView
{
public:
	AddFriendView();
	virtual ~AddFriendView();
	static AddFriendView* create(int numbers,const CCRect& rect,const CCRect& winRect);
	bool init(int numbers, const CCRect& rect,const CCRect& winRect);
	void setItemNameAtIndex(string name, int index);
	void addTarget(CAObject* target, SEL_AddFriendView selector);

public:
	void callFunc(CAObject* object, int index);
	virtual bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);
	void onButtonCallBack(CAControl *pTarget, CCPoint point);
	virtual void ccTouchMoved(CATouch *pTouch, CAEvent *pEvent);
	virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
private:
	CAObject*                   m_pTarget;
	SEL_AddFriendView           m_pCallFunc;
	CCRect m_rect;
	vector<CAButton*> m_pButtons;
	int count;
	CAView *background;
};

#endif /*defined(__ADDFRIEND_VIEW_H__)*/