//
//  FirstViewController.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-9.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "FirstViewController.h"
#include "IMDATA.h"
#include "IMLoginRegister.h"
#include "RootWindow.h"
#include "data/TableLanguage.h"
#include "table/TableLanguagesfontnewHeader.h"
#include "IMTableCell.h"
#include "HXSDKController.h"
#include "AddFriendView.h"
#include "groupview/GroupInfoViewController.h"
#include "SearchController.h"
#include "AddFriendController.h"
#include "AddGroupController.h"
#include "GroupInfoViewController.h"
#include "groupview/GroupCreateViewController.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "LocalStorageUserData.h"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"",__VA_ARGS__)
#endif

#define SEARCH_HEIGH  75.0f

FirstViewController::FirstViewController()
:m_pNavigationBarItem(NULL)
,m_pTitleView(NULL)
,m_pSearchTextField(NULL)
,m_pTableView(NULL)
,m_pWinSize(CCSizeZero)
,cell(NULL)
,addView(NULL)
{

}

FirstViewController::~FirstViewController()
{
    CC_SAFE_RELEASE(m_pNavigationBarItem);
    CC_SAFE_RELEASE(m_pSearchTextField);
}

bool FirstViewController::init()
{
    if(CAViewController::init())
    {
        CABarButtonItem* addButtonItem = CABarButtonItem::create("",
                                                                 CAImage::create(NAVIGATION_BAR_ITEM_ADD_NORMAL),
                                                                 CAImage::create(NAVIGATION_BAR_ITEM_ADD_SELECTED));
        addButtonItem->setTarget(this, CAControl_selector(FirstViewController::onButtonAdd));
        
        m_pTitleView = CASegmentedControl::createWithFrame(CADipRect(0, 0, 270, 40), 2);
        
        m_pTitleView->setImageForSegmentAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_POPULAR_NORMAL), 0, CAControlStateNormal);
        m_pTitleView->setImageForSegmentAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_POPULAR_SELECTED), 0, CAControlStateSelected);
        m_pTitleView->setImageForSegmentAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_NEW_NORMAL), 1, CAControlStateNormal);
        m_pTitleView->setImageForSegmentAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_NEW_SELECTED), 1, CAControlStateSelected);
        m_pTitleView->setTitleForSegmentAtIndex(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_NAVIGATION_BAR_ITEM_NAME_0).c_str(), 0);
        m_pTitleView->setTitleColor(CAColor_white);
        m_pTitleView->setTitleSelectedColor(CAColor_red);
        m_pTitleView->setTitleForSegmentAtIndex(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_NAVIGATION_BAR_ITEM_NAME_1).c_str(), 1);
        m_pTitleView->setSelectedAtIndex(0);
        m_pTitleView->addTarget(this, CASegmentedControl_selector(FirstViewController::onButtonSegmented));

        m_pNavigationBarItem = CANavigationBarItem::create("");
        m_pNavigationBarItem->setShowGoBackButton(false);

        m_pNavigationBarItem->addRightButtonItem(addButtonItem);
        m_pNavigationBarItem->setTitleView(m_pTitleView);
        m_pNavigationBarItem->retain();
        
        //CANotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(FirstViewController::isLoginCallBack), KNOTIFICATION_LOGIN, NULL);
        
        return true;
    }
    return false;
}

void FirstViewController::viewDidLoad()
{
    m_pWinSize = this->getView()->getBounds().size;
    
    init_searchBar();
    
    init_tableView();
}

void FirstViewController::viewDidAppear()
{
    this->getTabBarController()->setNavigationBarItem(m_pNavigationBarItem);
    if(HXSDKController::getInstance()->isLogin())
    {
        m_vGroups = HXSDKController::getInstance()->getPublicGroupList();
        m_vMyGroups = HXSDKController::getInstance()->getMyGroupList();
        setGroupsDidIJoined();
    }
    if(NULL != addView)
    {
        addView->setVisible(false);
    }
    
    if (m_sKeyWord != "") {
       getGroupsWithKeyWords(m_sKeyWord.c_str());
    }
    m_pTableView->reloadData();
}

void FirstViewController::viewDidUnload()
{

}

void FirstViewController::init_searchBar()
{    
    CAScale9ImageView* searchBackground = CAScale9ImageView::createWithImage(CAImage::create(TABLE_GRAY_BG));
    searchBackground->setFrame(CADipRect(0.0f, 0.0f, m_pWinSize.width, SEARCH_HEIGH));
    this->getView()->insertSubview(searchBackground, 10);
    
    m_pSearchTextField = CATextField::createWithFrame(CADipRect(20.0f, 10.0f, m_pWinSize.width-40.0f, 50.0f));
    m_pSearchTextField->setBackgroundView(CAView::createWithColor(CAColor_white));
    m_pSearchTextField->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_SEARCH_CONTENT_TEXT).c_str());
    m_pSearchTextField->setSpaceHolderColor(ccc4(0x96, 0x96, 0x96, 0xff));
    m_pSearchTextField->setFontSize(_px(28.0f));
    m_pSearchTextField->setDelegate(this);
    m_pSearchTextField->setKeyboardReturnType(KEY_BOARD_RETURN_SEARCH);
    searchBackground->addSubview(m_pSearchTextField);
}

void FirstViewController::init_tableView()
{
    m_pTableView = CATableView::createWithCenter(CCRect(m_pWinSize.width*0.5, m_pWinSize.height*0.5f + SEARCH_HEIGH*0.5f, m_pWinSize.width, m_pWinSize.height - SEARCH_HEIGH));
    m_pTableView->setTableViewDataSource(this);
    m_pTableView->setTableViewDelegate(this);
    m_pTableView->setAllowsSelection(true);
    this->getView()->addSubview(m_pTableView);
}

void FirstViewController::refreshTableView()
{
    m_pTableView->reloadData();
}

void FirstViewController::getGroupsWithKeyWords(const char *keywords)
{
    m_vGroupsWithKeyWords.clear();
    for (int i = 0; i<m_vGroups.size(); i++) {
        std::string subject = m_vGroups.at(i)->m_sGroupSubject;
        string::size_type idx = subject.find(keywords);
        if ( idx != string::npos )
        {
            m_vGroupsWithKeyWords.push_back(m_vGroups.at(i));
        }
        
    }
    
}

void FirstViewController::setGroupsDidIJoined()
{
    for (int j = 0; j<m_vGroups.size(); j++) {
        HXSDKGroup * group = m_vGroups.at(j);
        group->m_bIsJoined = false;
    }

    for (int i = 0; i<m_vMyGroups.size(); i++) {
        HXSDKGroup * pGroup = m_vMyGroups.at(i);
        for (int j = 0; j<m_vGroups.size(); j++) {
            HXSDKGroup * group = m_vGroups.at(j);
            if (group->isEqual(pGroup))
            {
                group->m_bIsJoined = true;
                break;
            }
        }
    }
}
/*
void FirstViewController::onButtonPopular(CAControl* control, CCPoint point)
{
    
}

void FirstViewController::onButtonNew(CAControl* control, CCPoint point)
{
    
}
*/
void FirstViewController::onButtonAdd(CAControl* control, CCPoint point)
{
    if(NULL == addView)
    {
        addView = AddFriendView::create(3,CCRect(m_pWinSize.width-250, 10, 230, 300), this->getView()->getBounds());
        addView->setItemNameAtIndex(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_25).c_str(), 0);
        addView->setItemNameAtIndex(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_26).c_str(), 1);
        addView->setItemNameAtIndex(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_27).c_str(), 2);
        addView->addTarget(this, AddFriendView_selector(FirstViewController::addViewButtonCallBack));
        this->getView()->insertSubview(addView, 100);
    }
    else if(addView->isVisible())
    {
        addView->setVisible(false);
    }
    else if(!addView->isVisible())
    {
        addView->setVisible(true);
    }
    
}

void FirstViewController::addViewButtonCallBack(AddFriendView* controller, int index)
{
    if(-1 == index)
    {
        addView->setVisible(false);
    }
    else if(0 == index)
    {
        AddGroupController* addGroupController = AddGroupController::create();
        RootWindow::getInstance()->getNavigationController()->pushViewController(addGroupController, true);
    }
    else if(1 == index)
    {
        GroupCreateViewController *pController = GroupCreateViewController::create();
        RootWindow::getInstance()->getNavigationController()->pushViewController(pController,true);
    }
    else if(2 == index)
    {
        AddFriendController* addFriendController = AddFriendController::create();
        RootWindow::getInstance()->getNavigationController()->pushViewController(addFriendController, true);
        
    }
}

void FirstViewController::onButtonSegmented(CASegmentedControl*, int index)
{
    switch (index) {
        case 0:
            
            break;
        case 1:
            
            break;
        default:
            break;
    }
}

void FirstViewController::isLoginCallBack(CAObject* obj)
{
    if(obj)
    {
        CCLog("login success!!!");
        refreshTableView();
    }	
    else
    {
        CCLog("login failed...");
    }
}

#pragma mark TextFieldDelegate

bool FirstViewController::onTextFieldAttachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool FirstViewController::onTextFieldDetachWithIME(CATextField * sender)
{
    m_sKeyWord = m_pSearchTextField->getText();
    getGroupsWithKeyWords(m_sKeyWord.c_str());
    m_pTableView->reloadData();
    
    return false;
}

bool FirstViewController::onTextFieldInsertText(CATextField * sender, const char * text, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(text);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

bool FirstViewController::onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(delText);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

#pragma mark TableViewDelegate
void FirstViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    HXSDKGroup* sdkGroup = m_vGroups.at(row);
    
    GroupInfo groupInfo;
    groupInfo.m_pFaceImg = CAImage::create("IMResources/button_photo Album_normal.png");//qiaoxin test Image : sdk没有返回群图片数据
    groupInfo.m_sGroupID = sdkGroup->m_sGroupId;
    groupInfo.m_sTopic = sdkGroup->m_sGroupSubject;
    groupInfo.m_sIntroduce = sdkGroup->m_sGroupDescription;
    groupInfo.m_sOwner = sdkGroup->m_sGroupOwer;
    groupInfo.m_itotal = sdkGroup->m_iGroupOccupantsCount+1;
    groupInfo.m_sLimit = sdkGroup->m_eGroupType;
    groupInfo.m_bIsNotice = sdkGroup->m_bIsPushNotificationEnable;
    
    GroupInfoViewController* groupController = GroupInfoViewController::create(groupInfo, sdkGroup->m_bIsJoined);
    RootWindow::getInstance()->getNavigationController()->pushViewController(groupController, true);
}

void FirstViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* FirstViewController::tableCellAtIndex(CATableView* table, const CCSize& cellsize, unsigned int section, unsigned int row)
{
    /*cell页面的初始化*/
    cell = table->dequeueReusableCellWithIdentifier("Crossapp");
    CCSize cellSize = CCSizeMake(m_pWinSize.width, _px(90));
    if(cell == NULL)
    {
        cell = IMTableCell::create(Group, cellSize);
    }
    if (m_sKeyWord == "") {
        ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), m_vGroups.at(row)->m_sGroupSubject,m_vGroups.at(row)->m_sGroupDescription);
    }
    else{
       ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), m_vGroupsWithKeyWords.at(row)->m_sGroupSubject,m_vGroupsWithKeyWords.at(row)->m_sGroupDescription);
    }

    return cell;
}

/*在section之间添加一个view，就是UI中section之间的灰色地带*/
CAView* FirstViewController::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    CAView* view = CAView::createWithColor(ccc4(230, 230, 230, 255));
    return view;
}

/*设置每个section含有的cell个数*/
unsigned int FirstViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    int num=0;
    if (m_sKeyWord == "") {
        num = m_vGroups.size();
    } else{
        num = m_vGroupsWithKeyWords.size();
    }

    return num;
}

/*设置含有几个section*/
unsigned int FirstViewController::numberOfSections(CATableView *table)
{
    return 1;
}

unsigned int FirstViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{	/*section的大小设置*/
    
    return _px(90);
}

unsigned int FirstViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    return _px(5);
}




