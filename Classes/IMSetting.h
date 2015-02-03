//
//  IMSetting.h
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#ifndef __IM_SETTING_H__
#define __IM_SETTING_H__
#endif /*__IM_SETTING_H__*/

#include "CrossApp.h"
#include "CrossAppExt.h"
#include <iostream>
USING_NS_CC;
USING_NS_CC_EXT;

class IMSetting :public CAViewController
	, public CATableViewDelegate
	, CATableViewDataSource
{
public:
	IMSetting();
	virtual ~IMSetting();
	virtual bool init();
	static IMSetting* create();
protected:
	void viewDidLoad();
	void viewDidUnload();
	void viewDidAppear();

public:
	/*这些是tableview的相关函数*/
	virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& viewSize, unsigned int section, unsigned int row);
	virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& cellsize, unsigned int section);
	virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
	virtual unsigned int numberOfSections(CATableView *table);
	virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
protected:
	CATableViewCell* initMessage(const CCSize& cellsize);
	CATableViewCell* initChangePwd(const CCSize& cellsize);
	CATableViewCell* initSuggestion(const CCSize& cellsize);
	CATableViewCell* initScore(const CCSize& cellsize);
	CATableViewCell* initLogout(const CCSize& cellsize);
private:
	CANavigationBarItem *pNagivationitem;
	CCSize winSize;
	CATableView *m_pTableView;
	CATableViewCell *cell;
	CALabel *newMessage;
	CALabel *changePwd;
	CALabel *suggestion;
	CALabel *score;
	CALabel *logout;

};