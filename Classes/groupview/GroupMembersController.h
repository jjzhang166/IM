//
//  GroupMembersController.h
//  IM
//
//  Created by qiaoxin on 15-3-23.
//
//

#ifndef __IM__GroupMembersController__
#define __IM__GroupMembersController__

#include <iostream>
#include "crossApp.h"
#include <stdio.h>

USING_NS_CC;

class HXSDKBuddy;

class GroupMembersController : public CAViewController
,public CATableViewDelegate
,public CATableViewDataSource
{
public :
    
    GroupMembersController();
    virtual ~GroupMembersController();
    static GroupMembersController* create(std::vector<HXSDKBuddy*> members);
    virtual bool init(std::vector<HXSDKBuddy *> members);
    
    void onButtonBack(CAControl *pTarget, CCPoint point); // 返回按钮
    
protected:
    void viewDidLoad();
    void viewDidUnLoad();
    
    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& viewSize, unsigned int section, unsigned int row);
    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& cellsize, unsigned int section);
    virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
    virtual unsigned int numberOfSections(CATableView *table);
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
    
protected:
    std::vector<HXSDKBuddy*> m_vGroupMembers;
    CCSize m_winSize;
    CATableViewCell*        cell;  //tableView中的cell
};

#endif /* defined(__IM__GroupMembersController__) */
