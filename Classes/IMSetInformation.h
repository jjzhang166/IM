//
//  IMSetInformation.h
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#ifndef __IM_SETINFORMATION_H__
#define __IM_SETINFORMATION_H__

#include "CrossApp.h"
#include <iostream>
#include <map>
USING_NS_CC;
using namespace std;
typedef enum{
	NAMESET,
	SEXSET,
	SIGNATURESET
}IMinfoset;

class IMSetInformation :public CAViewController
	, public CATextFieldDelegate
	, public CATableViewDelegate
	, public CATableViewDataSource
	, public CAScrollViewDelegate
{
public:
	IMSetInformation();
	virtual ~IMSetInformation();
	bool init();
	static IMSetInformation* create(IMinfoset p_infoset);
protected:
	void viewDidLoad();
	void viewDidUnload();
	void viewDidAppear();
	bool onTextFieldAttachWithIME(CATextField * sender);
	bool onTextFieldDetachWithIME(CATextField * sender);
	virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
	virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);

public:
	void onaddFinishBtn(CAControl *pTarget, CCPoint point);
	void onaddCancelBtn(CAControl *pTarget, CCPoint point);
	void setbutton1Visible(CAControl *pTarget, CCPoint point);
	void setbutton2Visible(CAControl *pTarget, CCPoint point);
	void loadBaseView();
	std::string findString();
	void initViewOfName();
	void initViewOfSex();
	void initViewOfSignature();
private:
	CANavigationBarItem *pNavigationitem;
	CCSize winSize;
	CALabel *m_pLabel;
	CATextField* m_pText;
	IMinfoset infoset;
	std::map<IMinfoset, std::string> list;
	std::string nagivation;
	CAImageView *pchoose;
	CAButton *pbutton1;
	CAButton *pbutton2;
};

#endif /*defined(__IM_SETINFORMATION_H__)*/