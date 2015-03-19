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

class HXSDKBuddy;
class HXSDKGroup;

class SecondViewController : public CAViewController, public CATextFieldDelegate,public CATableViewDelegate, public CATableViewDataSource
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
    
    void init_searchResultTable();
    
    void onButtonAdd(CAControl* control, CCPoint point);//添加按钮回调
    
    /*textFieldDelegate*/
    bool onTextFieldAttachWithIME(CATextField * sender);
    bool onTextFieldDetachWithIME(CATextField * sender);
    virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);
public:
    /*CATableViewDelegate*/
    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    /*CATableViewDataSource*/
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& viewSize, unsigned int section, unsigned int row);
    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& cellsize, unsigned int section);
    virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
    virtual unsigned int numberOfSections(CATableView *table);
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);private:

    CATableView* p_TableView;
    
protected:
    CANavigationBarItem* m_pNavigationBarItem;
    
    CASegmentedControl* m_pTitleView;
    
    CATextField* m_pSearchTextField;
    
    CATableView*            m_pTableView;
    
    CADipSize               m_pWinSize;
    
    CATableViewCell*        cell;  //tableView中的cell
    
    std::vector<HXSDKBuddy*> m_vMyFriends;
    
    std::vector<HXSDKGroup*> m_vMyGroups;
};


#endif /* defined(__SECOND_VIEW_CONTROLLER__) */