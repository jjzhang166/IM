//
//  IMMyInfo.h
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#ifndef __IM__MyInfo__
#define __IM__MyInfo__

#include "CrossApp.h"
#include "CrossAppExt.h"
#include <iostream>
USING_NS_CC;
USING_NS_CC_EXT;
//用户详细信息
class IMMyInfo :public CAViewController, public CATableViewDelegate, public CATableViewDataSource
	, public CAMediaDelegate
{
public:
	IMMyInfo();
	virtual ~IMMyInfo();
	virtual bool init();
	static IMMyInfo* create();
	virtual void getSelectedImage(CAImage *image);
	void onHeadClick();
	void onCameraBtnClick(CAControl* pTarget, CCPoint point);
	void onAlbumBtnClick(CAControl* pTarget, CCPoint point);
	void onCancelBtnClick(CAControl* pTarget, CCPoint point);
	void onStartBtnClick(CAControl* pTarget, CCPoint point);
	void addPicChoserLayer();
	void addRightArrow(CATableViewCell *m_pCell,const CCSize& pcellsize);
protected:
	void viewDidLoad();
	void viewDidUnload();
	void viewDidAppear();
public:
	/*这些是tableview的相关函数*/
	virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& viewSize, unsigned int section, unsigned int row);
	virtual CAView* tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& cellsize, unsigned int section);
	virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
	virtual unsigned int numberOfSections(CATableView *table);
	virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	virtual unsigned int tableViewHeightForFooterInSection(CATableView* table, unsigned int section);
protected:
	CATableViewCell* initHeadImage(const CCSize& cellsize);
	CATableViewCell* initName(const CCSize& cellsize);
	CATableViewCell* initSex(const CCSize& cellsize);
	CATableViewCell* initSignature(const CCSize& cellsize);
	//void 进入不同界面

private:
	CANavigationBarItem *pNagivationitem;
	CADipSize winSize;
	CATableView *m_pTableView;
	CATableViewCell *cell;
	CAButton *m_pStart;
	CAImageView *m_pUserHead;
	CALabel *m_pUserName;
	CALabel *m_pUserSex;
	CALabel *m_pUserSignature;
	CAView *m_pPicChoserLayer;
};

#endif /*defined(__IM__MyInfo__)*/