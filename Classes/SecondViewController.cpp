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
}
void SecondViewController::init_searchBar()
{
    CADipSize size = this->getView()->getBounds().size;
    
    CAScale9ImageView* searchBackground = CAScale9ImageView::createWithImage(CAImage::create(TABLE_GRAY_BG));
    searchBackground->setFrame(CADipRect(0.0f, 0.0f, size.width, 75.0f));
    this->getView()->insertSubview(searchBackground, 10);
    
    m_pSearchTextField = CATextField::createWithFrame(CADipRect(20.0f, 10.0f, size.width-40.0f, 50.0f));
    m_pSearchTextField->setBackgroundView(CAView::createWithColor(CAColor_white));
    m_pSearchTextField->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_SEARCH_CONTENT_TEXT).c_str());
    m_pSearchTextField->setSpaceHolderColor(ccc4(0x96, 0x96, 0x96, 0xff));
    m_pSearchTextField->setFontSize(_px(28.0f));
    m_pSearchTextField->setDelegate(this);
    m_pSearchTextField->setKeyboardReturnType(KEY_BOARD_RETURN_SEARCH);
    searchBackground->addSubview(m_pSearchTextField);
}

void SecondViewController::viewDidAppear()
{
    this->getTabBarController()->setNavigationBarItem(m_pNavigationBarItem);
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
