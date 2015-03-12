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
#include "AddFriendView.h"

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

	void onFriend(AddFriendView*, int index); //点击屏幕处理函数
    /*textFieldDelegate*/
    bool onTextFieldAttachWithIME(CATextField * sender);
    bool onTextFieldDetachWithIME(CATextField * sender);
    virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);
    
public:
    /*CATableViewDelegate*/
//    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
//    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
//    /*CATableViewDataSource*/
//    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& viewSize, unsigned int section, unsigned int row);
//    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& cellsize, unsigned int section);
//    virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
//    virtual unsigned int numberOfSections(CATableView *table);
//    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
//    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);

private:
	AddFriendView *friendview; //好友添加界面
protected:
    CATextField*            m_pSearchTextField;
    CADipSize               m_pWinSize;
    
};


#endif /* defined(__SECOND_VIEW_CONTROLLER__) */
