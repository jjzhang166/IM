//
//  IMMyController.h
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#ifndef __IMMY_CONTROLLER_H__
#define __IMMY_CONTROLLER_H__

#include "CrossApp.h"
#include <iostream>
#include "IMUserManager.h"
USING_NS_CC;
//用户信息控制页面
class IMMyController:public CAViewController
,public CATableViewDelegate
,public CATableViewDataSource
{
public:
	IMMyController();
	virtual ~IMMyController();
	virtual bool init(); //初始化
protected:
	void viewDidLoad();  //界面加载函数
	void viewDidUnload();
	void viewDidAppear();
	void onButtonAdd(CAControl* control, CCPoint point);//添加按钮回调
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
	CATableViewCell* initViewOfMe(const CCSize& cellsize); //用户账号栏
	CATableViewCell*  initViewOfContanct(const CCSize& cellsize);  //通讯录栏
	CATableViewCell*  initViewOfSetting(const CCSize& cellsize);   //设置栏
private:
	CCSize winSize;  //屏幕大小
	CATableView *m_pTableView;  
	CATableViewCell *cell;  //tableView中的cell
	User *user;
	CAImageView *phead;
	CALabel *pname;
	CALabel *pcontent;

};







#endif
