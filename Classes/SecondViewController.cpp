//
//  SecondViewController.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-9.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "SecondViewController.h"
#include "IMDATA.h"
#include "groupview/GroupInfoViewController.h"
#include "RootWindow.h"
#include "HXSDKController.h"
#include "table/TableLanguagesfontnewHeader.h"
#include "data/TableLanguage.h"
#include "IMTableCell.h"


using namespace CrossApp;

SecondViewController::SecondViewController()
{
    
    
}

SecondViewController::~SecondViewController()
{
    CC_SAFE_RELEASE(m_pNavigationBarItem);
}

bool SecondViewController::init()
{
    if (CAViewController::init())
    {
        CABarButtonItem* addButtonItem = CABarButtonItem::create("", CAImage::create(NAVIGATION_BAR_ITEM_ADD_NORMAL), CAImage::create(NAVIGATION_BAR_ITEM_ADD_SELECTED));
        addButtonItem->setTarget(this, CAControl_selector(SecondViewController::onButtonAdd));
        
        m_pNavigationBarItem = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_NAVIGATION_BAR_ITEM_NAME_2).c_str());
        m_pNavigationBarItem->setShowGoBackButton(false);
        m_pNavigationBarItem->addRightButtonItem(addButtonItem);
        
        m_pNavigationBarItem->retain();
        
        return true;
    }
    return false;
}

void SecondViewController::viewDidLoad()
{
    init_searchBar();
    
    CCRect winRect = this->getView()->getBounds();
    size = this->getView()->getBounds().size;
    m_pWinSize = this->getView()->getBounds().size;
    
    init_searchResultTable();
}
void SecondViewController::init_searchBar()
{
    CADipSize size = this->getView()->getBounds().size;

    CAScale9ImageView* searchBackground = CAScale9ImageView::createWithImage(CAImage::create(TABLE_GRAY_BG));
    searchBackground->setFrame(CADipRect(0.0f, 0.0f, size.width, 75.0f));
    this->getView()->insertSubview(searchBackground, 10);
    
    m_pSearchTextField = CATextField::createWithFrame(CADipRect(20.0f, 10.0F, size.width-40.0f, 50.0f));
    m_pSearchTextField->setBackgroundView(CAView::createWithColor(CAColor_white));
    m_pSearchTextField->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_SEARCH_CONTENT_TEXT).c_str());
    m_pSearchTextField->setSpaceHolderColor(ccc4(0x96, 0x96, 0x96, 0xff));
    m_pSearchTextField->setFontSize(_px(28.0f));
    m_pSearchTextField->setDelegate(this);
    m_pSearchTextField->setKeyboardReturnType(KEY_BOARD_RETURN_SEARCH);
    searchBackground->addSubview(m_pSearchTextField);
}

void SecondViewController::init_searchResultTable()
{
    m_pTableView = CATableView::createWithCenter(CCRect(m_pWinSize.width*0.5, m_pWinSize.height*0.5f + 75.0F*0.5f-25.0f, m_pWinSize.width, m_pWinSize.height - 75.0F));
    m_pTableView->setTableViewDataSource(this);
    m_pTableView->setTableViewDelegate(this);
    m_pTableView->setAllowsSelection(true);
    this->getView()->addSubview(m_pTableView);

}

void SecondViewController::viewDidAppear()
{
    this->getTabBarController()->setNavigationBarItem(m_pNavigationBarItem);
    
    m_vMyFriends = HXSDKController::getInstance()->getFriendsList();
    m_vMyGroups = HXSDKController::getInstance()->getMyGroupList();

    
    
    m_pTableView->reloadData();
}

void SecondViewController::viewDidUnload()
{
    
}

void SecondViewController::onButtonAdd(CAControl* control, CCPoint point)
{
    
    //	string a = UTF8("我是主题");
    //	string b = UTF8("我是介绍");
    //	string c = UTF8("我是群主");
    //	string d = UTF8("我是成员");
    
    
    //	GroupInfo info = GroupInfo(CAImage::create("HelloWorld.png"), a, b, c, d,  520, true);
    //	GroupInfoViewController * _group = GroupInfoViewController::create(info, false);
    //	RootWindow::getInstance()->getNavigationController()->pushViewController(_group, true);
    
}


#pragma mark TextFieldDelegate

bool SecondViewController::onTextFieldAttachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool SecondViewController::onTextFieldDetachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool SecondViewController::onTextFieldInsertText(CATextField * sender, const char * text, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(text);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

bool SecondViewController::onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(delText);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

#pragma mark CATableViewDelegate
void SecondViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    //    //cell点击处理事件
    //    if (section == 0){
    //        IMMyInfo *pIMMyInfo = IMMyInfo::create();
    //        RootWindow::getInstance()->getNavigationController()->pushViewController(pIMMyInfo, true);
    //    }
    //    else if (section == 1){
    //        //通讯录
    //    }
    //    else if (section == 2)
    //    {
    //        //点击设置栏，进入用户设置页面
    //        IMSetting *pIMSetting = IMSetting::create();
    //        RootWindow::getInstance()->getNavigationController()->pushViewController(pIMSetting, true);
    //    }
    //    else{
    //    }
}

void SecondViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* SecondViewController::tableCellAtIndex(CATableView* table, const CCSize& cellsize, unsigned int section, unsigned int row)
{
    /*cell页面的初始化*/
    cell = table->dequeueReusableCellWithIdentifier("Crossapp");
    CCSize cellSize = CCSizeMake(m_pWinSize.width, _px(90));
    switch (section) {
        case 0:
        {
            cell = IMTableCell::create(SearchResult, cellSize);
            ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), m_vMyGroups.at(row)->m_sGroupSubject);
            break;
        }
        case 1:
        {
            cell = IMTableCell::create(SearchResult, cellSize);
            ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), m_vMyFriends.at(row)->m_sUserName);
            break;
        }
        case 2:
        {
            cell = IMTableCell::create(SearchResult, cellSize);
            ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), "test");
            break;
        }
        default:
            break;
    }
    return cell;
}

/*在section之间添加一个view，就是UI中section之间的灰色地带*/
CAView* SecondViewController::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    CAView* view = CAView::createWithFrame(CADipRect(0, 0, m_pWinSize.width, 130.0f));
    CAView* splitview = CAView::createWithFrame(CADipRect(0, 0, m_pWinSize.width, 25.0f), ccc4(230, 230, 230, 255));
    view->addSubview(splitview);

    CALabel* label = CALabel::createWithFrame(CCRect(40, 65.0f, m_pWinSize.width, 104.0f));
    label->setColor(ccc4(152, 152, 152, 255));
    label->setFontSize(_px(38));
    switch (section) {
        case 0:
               label->setText(UTF8("群聊"));
            break;
        case 1:
               label->setText(UTF8("好友"));
            break;
        case 2:
            label->setText(UTF8("聊天记录"));
            break;
        default:
            break;
    }
    view->addSubview(label);

    CAView* lineview = CAView::createWithFrame(CCRect(40.0f, 129.0f, m_pWinSize.width-80.0f, 1.0f), ccc4(200, 200, 200, 255));
    view->addSubview(lineview);
    
    return view;
}

/*设置每个section含有的cell个数*/
unsigned int SecondViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    int num=0;
    switch (section) {
        case 0:
            num = m_vMyGroups.size();
            break;
        case 1:
            num = m_vMyFriends.size();
            break;
        case 2:
            num = 1;
            break;
        default:
            break;
    }
    return num;
}

/*设置含有几个section*/
unsigned int SecondViewController::numberOfSections(CATableView *table)
{
    return 3;
}

unsigned int SecondViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{	/*section的大小设置*/
    
    return _px(90);
}

unsigned int SecondViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    return _px(130);
}
