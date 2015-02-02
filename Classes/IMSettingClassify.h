//
//  IMSettingClassify.h
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#ifndef __IMSETTING_CLASSIFY_H__
#define __IMSETTING_CLASSIFY_H__
#include <iostream>
#include "CrossApp.h"
#include "CrossAppExt.h"
USING_NS_CC;
USING_NS_CC_EXT;

#pragma NewMessageSet
class IMSettingClassifyNewMessage :public CAViewController
	, public CATableViewDelegate
	, public CATableViewDataSource
{
public:
	IMSettingClassifyNewMessage();
	virtual ~IMSettingClassifyNewMessage();
	bool init();
protected:
	void viewDidLoad();
	void viewDidUnload();
	void viewDidAppear();
public:
	/*这些是tableview的相关函数*/
	virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& viewSize, unsigned int section, unsigned int row);
	virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
	virtual unsigned int numberOfSections(CATableView *table);
	virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
private:
	CATableView *m_pTableView;
	CATableViewCell *cell;
	CCSize winSize;
	CANavigationBarItem *pNavigationBarItem;
	CALabel *label1;
	CASwitch *m_pSwitch;

};

#pragma changePwd
class IMSettingClassifyPwd :public CAViewController
	, public CATextFieldDelegate
{
public:
	IMSettingClassifyPwd();
	virtual ~IMSettingClassifyPwd();
	bool init();
	void onFinish(CAControl *ptarget, CCPoint point);
protected:
	void viewDidLoad();
	void viewDidUnload();
	
private:
	CCSize winSize;
	CANavigationBarItem *pNavigationBarItem;
	CALabel *plabel1;
	CALabel *plabel2;
	CATextField *ptextpwd;
	CATextField *ptextpwdNew;
	CATextField *ptextpwdNewAgain;
};

#pragma SUGGESTION
class IMSettingClassifySuggestion :public CAViewController
	, public CATextFieldDelegate
{
public:
	IMSettingClassifySuggestion();
	virtual ~IMSettingClassifySuggestion();
	bool init();
	void onFinish(CAControl *ptarget, CCPoint point);
protected:
	void viewDidLoad();
	void viewDidUnload();

private:
	CCSize winSize;
	CANavigationBarItem *pNavigationBarItem;
	CATextField *content;
	CAButton *result;
};




class IMSettingClassify:public CAViewController
{
public:
	IMSettingClassify();
	virtual ~IMSettingClassify();
	static IMSettingClassify* getInstance();
public:
	IMSettingClassifyNewMessage* messageCreate();
	IMSettingClassifyPwd* pwdChangeCreate();
	IMSettingClassifySuggestion* suggestionCreate();

};


#endif /*__IMSETTING_CLASSIFY_H__*/