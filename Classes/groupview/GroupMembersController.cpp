//
//  GroupMembersController.h
//  IM
//
//  Created by qiaoxin on 15-3-23.
//
//

#include "GroupMembersController.h"
#include "CrossApp.h"
#include "RootWindow.h"
#include "IMDATA.h"
#include "HXSDKController.h"
#include "AddHeadForgrand.h"
#include "../data/TableLanguage.h"
#include "../table/TableLanguagesfontnewHeader.h"
#include "IMTableCell.h"

GroupMembersController::GroupMembersController()
:m_winSize(CCSizeZero)
{
    
}

GroupMembersController::~GroupMembersController()
{
    m_vGroupMembers.clear();
}

GroupMembersController* GroupMembersController::create(std::vector<HXSDKBuddy *> members)
{
    GroupMembersController* controller = new GroupMembersController();
    if(controller->init(members))
    {
        controller->autorelease();
        return controller;
    }
    return false;
}

bool GroupMembersController::init(std::vector<HXSDKBuddy *> members)
{
    if (CAViewController::init()) {
        m_vGroupMembers = members;
        
        CABarButtonItem* backItem = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LOGOUT).c_str(), NULL, NULL);
        backItem->setTarget(this, CAControl_selector(GroupMembersController::onButtonBack));
        CANavigationBarItem* navigation = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_35).c_str());
        navigation->setShowGoBackButton(false);
        navigation->addLeftButtonItem(backItem);
        setNavigationBarItem(navigation);
        return true;
    }
    return false;
}

void GroupMembersController::viewDidLoad()
{
    m_winSize = this->getView()->getBounds().size;
    
    CATableView* tableView = CATableView::createWithCenter(CCRect(m_winSize.width*0.5, m_winSize.height*0.5, m_winSize.width, m_winSize.height));
    tableView->setTableViewDataSource(this);
    tableView->setTableViewDelegate(this);
    tableView->setAllowsSelection(true);
    this->getView()->addSubview(tableView);

}

void GroupMembersController::viewDidUnLoad()
{

}

void GroupMembersController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    //cell点击处理事件
}

void GroupMembersController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* GroupMembersController::tableCellAtIndex(CATableView* table, const CCSize& cellsize, unsigned int section, unsigned int row)
{
    /*cell页面的初始化*/
    cell = table->dequeueReusableCellWithIdentifier("Crossapp");
    CCSize cellSize = CCSizeMake(m_winSize.width, _px(90));
    if(cell == NULL)
    {
        cell = IMTableCell::create(Friend, cellSize);
    }
    ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), m_vGroupMembers.at(row)->m_sUserName, "");
    return cell;
}

/*在section之间添加一个view，就是UI中section之间的灰色地带*/
CAView* GroupMembersController::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    CAView* view = CAView::createWithColor(ccc4(230, 230, 230, 255));
    return view;
}

/*设置每个section含有的cell个数*/
unsigned int GroupMembersController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    return m_vGroupMembers.size();
}

/*设置含有几个section*/
unsigned int GroupMembersController::numberOfSections(CATableView *table)
{
    return 1;
}

unsigned int GroupMembersController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{	/*section的大小设置*/
    return _px(90);
}

unsigned int GroupMembersController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    return 0;
}

// 返回按钮
void GroupMembersController:: onButtonBack(CAControl* target, CCPoint point)
{
    RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(this);
    
}
