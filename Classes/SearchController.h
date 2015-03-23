//
//  SearchController.h
//  IM
//
//  Created by qiaoxin on 15-3-23.
//
//

#ifndef __IM__SearchController__
#define __IM__SearchController__

#include <iostream>
#include "crossApp.h"
#include <stdio.h>

USING_NS_CC;

class SearchController : public CAViewController
,public CATableViewDelegate
,public CATableViewDataSource
,public CATextFieldDelegate
{
public :
    
    SearchController();
    virtual ~SearchController();
    static SearchController* create();
    virtual bool init();
    
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
    /*textFieldDelegate*/
    bool onTextFieldAttachWithIME(CATextField * sender);
    bool onTextFieldDetachWithIME(CATextField * sender);
    virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);
    
    void init_searchBar();
protected:
    CATextField*        m_pSearchTextField;
    CCSize              m_winSize;
    CATableViewCell*    cell;  //tableView中的cell
};

#endif /* defined(__IM__SearchController__) */
