//
//  FirstViewController.h
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-9.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#ifndef __HelloCpp__ViewController__
#define __HelloCpp__ViewController__

#include <iostream>
#include "CrossApp.h"
#include "HXSDKBuddy.h"

USING_NS_CC;
class HXSDKGroup;
class AddFriendView;

class FirstViewController: public CAViewController,
public CATextFieldDelegate,
public CATableViewDelegate,
public CATableViewDataSource
{
    
public:

	FirstViewController();
    
	virtual ~FirstViewController();
    
    virtual bool init();
    
    void refreshTableView();
protected:
    
    virtual void viewDidLoad();
    
    virtual void viewDidUnload();
    
    virtual void viewDidAppear();
    
    void init_searchBar();
    
    void init_tableView();
    
    
    void onButtonSegmented(CASegmentedControl*, int index);
    /*
    void onButtonPopular(CAControl* control, CCPoint point);//热门按钮回调
    
    void onButtonNew(CAControl* control, CCPoint point);//最新按钮回调
    */
    void onButtonSearch(CAControl* control, CCPoint point);//搜索按钮回调
    
    void onButtonAdd(CAControl* control, CCPoint point);//添加按钮回调
    
    void addViewButtonCallBack(AddFriendView* controller, int index);//加好小窗口按钮回调
    
    void isLoginCallBack(CAObject* obj);//登录成功回调
    
protected:
    /*CATableViewDelegate*/
    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    /*CATableViewDataSource*/
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& viewSize, unsigned int section, unsigned int row);
    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& cellsize, unsigned int section);
    virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
    virtual unsigned int numberOfSections(CATableView *table);
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
    
    /*textFieldDelegate*/
    bool onTextFieldAttachWithIME(CATextField * sender);
    bool onTextFieldDetachWithIME(CATextField * sender);
    virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);
    
protected:
    CANavigationBarItem*    m_pNavigationBarItem;
    
    CASegmentedControl*     m_pTitleView;
    
    CATextField*            m_pSearchTextField;
    
    CATableView*            m_pTableView;
    
    CADipSize               m_pWinSize;
    
    CATableViewCell*        cell;  //tableView中的cell
    
    std::vector<HXSDKGroup*> m_vGroups;
    std:: vector<HXSDKGroup*> m_vMyGroups;
    
    AddFriendView*          addView;
    
    /*搜索关键字*/
    std::string m_sKeyWord;
    /*带有搜索关键字的群组*/
    std::vector<HXSDKGroup*> m_vGroupsWithKeyWords;
    
    void getGroupsWithKeyWords(const char* keywords);
    /*设置这个群我是否加入*/
    void setGroupsDidIJoined();
};


#endif /* defined(__HelloCpp__ViewController__) */
