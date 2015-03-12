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

#define SEARCH_HEIGH  75.0f

using namespace CrossApp;

SecondViewController::SecondViewController() :friendview(NULL)
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
	CCRect winRect = this->getView()->getBounds();
    m_pWinSize = this->getView()->getBounds().size;

    init_searchBar();
	//好友添加界面
//	friendview = AddFriendView::create(3, winRect);
//	friendview->setVisible(false);
//	friendview->setItemNameAtIndex(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_69).c_str(), 0);
//	friendview->setItemNameAtIndex(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_39).c_str(), 1);
//	friendview->setItemNameAtIndex(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_20).c_str(), 2);
//	friendview->addTarget(this, AddFriendView_selector(SecondViewController::onFriend));
//	this->getView()->addSubview(friendview);
}

void SecondViewController::viewDidAppear()
{
	this->getTabBarController()->setNavigationBarItem(m_pNavigationBarItem);
}

void SecondViewController::viewDidUnload()
{

}


void SecondViewController::init_searchBar()
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


void SecondViewController::onButtonAdd(CAControl* control, CCPoint point)
{
	friendview->setVisible(true);
	
//	string a = UTF8("我是主题");
//	string b = UTF8("我是介绍");
//	string c = UTF8("我是群主");
//	string d = UTF8("我是成员");


//	GroupInfo info = GroupInfo(CAImage::create("HelloWorld.png"), a, b, c, d,  520, true);
//	GroupInfoViewController * _group = GroupInfoViewController::create(info, false);
//	RootWindow::getInstance()->getNavigationController()->pushViewController(_group, true);
}

//点击屏幕处理函数
void SecondViewController::onFriend(AddFriendView*, int index)
{
	if (index == -1)
	{
		friendview->setVisible(false);
	}
	//根据index进行函数跳转

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