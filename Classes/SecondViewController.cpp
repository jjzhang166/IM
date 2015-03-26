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
#include "chat/IMChatController.h"
#include "GroupCreateViewController.h"
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
        m_pNavigationBarItem = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_NAVIGATION_BAR_ITEM_NAME_2).c_str());
        m_pNavigationBarItem->setShowGoBackButton(false);
        m_pNavigationBarItem->retain();
        return true;
    }
    return false;
}

void SecondViewController::viewDidLoad()
{
    m_pWinSize = this->getView()->getBounds().size;
    
    init_searchBar();
    
    init_searchResultTable();
}

void SecondViewController::init_searchBar()
{
    CAScale9ImageView* searchBackground = CAScale9ImageView::createWithImage(CAImage::create(TABLE_GRAY_BG));
    searchBackground->setFrame(CADipRect(0.0f, 0.0f, m_pWinSize.width, 75.0f));
    this->getView()->insertSubview(searchBackground, 10);
    
    m_pSearchTextField = CATextField::createWithFrame(CADipRect(20.0f, 10.0F, m_pWinSize.width-40.0f, 50.0f));
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
    m_sKeyWord = m_pSearchTextField->getText();
    
    if (m_sKeyWord == "") {
        m_vMyFriends = HXSDKController::getInstance()->getFriendsList();
        m_vMyGroups = HXSDKController::getInstance()->getMyGroupList();
    }else{
        getMyFriendsWithKeyWords(m_sKeyWord.c_str());
        getMyGroupsWithKeyWords(m_sKeyWord.c_str());
    }
    
    m_pTableView->reloadData();
}

void SecondViewController::viewDidUnload()
{
    
}

void SecondViewController::onButtonAdd(CAControl* control, CCPoint point)
{
   
}

/*通过关键字搜索好友列表*/
void SecondViewController:: getMyFriendsWithKeyWords(const char *keywords)
{
    m_vMyFriendsWithKeyWords.clear();
    
    for (int i = 0; i<m_vMyFriends.size(); i++) {
        std::string name = m_vMyFriends.at(i)->m_sUserName;
        string::size_type idx = name.find(keywords);
        if ( idx != string::npos )
        {
            m_vMyFriendsWithKeyWords.push_back(m_vMyFriends.at(i));
        }
       
    }
}

void SecondViewController::getMyGroupsWithKeyWords(const char *keywords)
{
    m_vMyGroupsWithKeyWords.clear();
    for (int i = 0; i<m_vMyGroups.size(); i++) {
        std::string subject = m_vMyGroups.at(i)->m_sGroupSubject;
        string::size_type idx = subject.find(keywords);
        if ( idx != string::npos )
        {
            m_vMyGroupsWithKeyWords.push_back(m_vMyGroups.at(i));
        }
        
    }

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

    m_sKeyWord = m_pSearchTextField->getText();
    getMyFriendsWithKeyWords(m_sKeyWord.c_str());
    getMyGroupsWithKeyWords(m_sKeyWord.c_str());
    m_pTableView->reloadData();
    
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
    
    IMChatController *pController =IMChatController::getInstance();
    std::string toUserName;
    switch (section) {
        case 0:
        {
            pController->setControllerByID(m_vMyGroups.at(row)->m_sGroupId, m_vMyGroups.at(row)->m_sGroupSubject, true);
            break;
        }
        case 1:
        {
            pController->setControllerByID(m_vMyFriends.at(row)->m_sUserName);
            break;
        }
        case 2:
        {
            toUserName = "qiaoxin5";
            break;
        }
        default:
            break;
    }
    
    pController->init();
    RootWindow::getInstance()->getNavigationController()->pushViewController(pController,true);


}

void SecondViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* SecondViewController::tableCellAtIndex(CATableView* table, const CCSize& cellsize, unsigned int section, unsigned int row)
{
    /*cell页面的初始化*/
    cell = table->dequeueReusableCellWithIdentifier("Crossapp");
    CCSize cellSize = CCSizeMake(m_pWinSize.width, _px(90));
    if(cell == NULL)
    {
        cell = IMTableCell::create(SearchResult, cellSize);
    }
    switch (section) {
        case 0:
        {
            if (m_sKeyWord == "") {
                ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), m_vMyGroups.at(row)->m_sGroupSubject);
            }
            else{
                ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), m_vMyGroupsWithKeyWords.at(row)
                                                  ->m_sGroupSubject);
            }
            break;
        }
        case 1:
        {
            if (m_sKeyWord == "") {
                ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), m_vMyFriends.at(row)->m_sUserName);
            }
            else{
                ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), m_vMyFriendsWithKeyWords.at(row)
                                                  ->m_sUserName);
            }
            
            break;
        }
        case 2:
        {

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
            if (m_sKeyWord == "") {
                 num = m_vMyGroups.size();
            } else{
                 num = m_vMyGroupsWithKeyWords.size();
            }
           
            break;
        case 1:
            if (m_sKeyWord == "") {
                num = m_vMyFriends.size();
            } else{
                num = m_vMyFriendsWithKeyWords.size();
            }
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
