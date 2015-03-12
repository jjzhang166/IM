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

		CABarButtonItem* searchButtonItem = CABarButtonItem::create("", CAImage::create(NAVIGATION_BAR_ITEM_SEARCH_NORMAL), CAImage::create(NAVIGATION_BAR_ITEM_SEARCH_SELECTED));
		searchButtonItem->setTarget(this, CAControl_selector(SecondViewController::onButtonSearch));
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
	//    CAImageView* imageView = CAImageView::createWithImage(CAImage::create("HelloWorld.png"));
	//    imageView->setFrame(winRect);
	//    this->getView()->addSubview(imageView);
	//    
	//    CALabel* label = CALabel::createWithCenter(CCRect(winRect.size.width*0.5, winRect.size.height*0.5-270, winRect.size.width, 200));
	//    label->setTextAlignment(CATextAlignmentCenter);
	//    label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	//    label->setFontSize(72 * CROSSAPP_ADPTATION_RATIO);
	//    label->setText("SecondViewController");
	//    label->setColor(CAColor_white);
	//    this->getView()->insertSubview(label, 1);

	//test IM
	CAButton * loginBtn = CAButton::createWithFrame(CCRect(100, 100, 500, 50), CAButtonTypeRoundedRect);
	loginBtn->setTitleForState(CAControlStateAll, "login");
	loginBtn->addTarget(this, CAControl_selector(SecondViewController::onButtonLogin), CAControlEventTouchUpInSide);
	this->getView()->addSubview(loginBtn);

	CAButton * logoutBtn = CAButton::createWithFrame(CCRect(100, 200, 500, 50), CAButtonTypeRoundedRect);
	logoutBtn->setTitleForState(CAControlStateAll, "logout");
	logoutBtn->addTarget(this, CAControl_selector(SecondViewController::onButtonLogOff), CAControlEventTouchUpInSide);
	this->getView()->addSubview(logoutBtn);

	CAButton * sendMsgBtn = CAButton::createWithFrame(CCRect(100, 300, 500, 50), CAButtonTypeRoundedRect);
	sendMsgBtn->setTitleForState(CAControlStateAll, "sendmessage");
	sendMsgBtn->addTarget(this, CAControl_selector(SecondViewController::onButtonSendText), CAControlEventTouchUpInSide);
	this->getView()->addSubview(sendMsgBtn);

	CAButton * getFriendsListBtn = CAButton::createWithFrame(CCRect(100, 400, 500, 50), CAButtonTypeRoundedRect);
	getFriendsListBtn->setTitleForState(CAControlStateAll, "getFrendsList");
	getFriendsListBtn->addTarget(this, CAControl_selector(SecondViewController::onButtonGetFriends), CAControlEventTouchUpInSide);
	this->getView()->addSubview(getFriendsListBtn);


	CAButton * createGroupBtn = CAButton::createWithFrame(CCRect(100, 500, 500, 50), CAButtonTypeRoundedRect);
	createGroupBtn->setTitleForState(CAControlStateAll, "create group");
	createGroupBtn->addTarget(this, CAControl_selector(SecondViewController::onButtonCreateGroup), CAControlEventTouchUpInSide);
	this->getView()->addSubview(createGroupBtn);

	CAButton * getGroupListBtn = CAButton::createWithFrame(CCRect(100, 600, 500, 50), CAButtonTypeRoundedRect);
	getGroupListBtn->setTitleForState(CAControlStateAll, "accept group");
	getGroupListBtn->addTarget(this, CAControl_selector(SecondViewController::onButtonGetGroups), CAControlEventTouchUpInSide);
	this->getView()->addSubview(getGroupListBtn);

	CAButton * getMyGroupListBtn = CAButton::createWithFrame(CCRect(100, 700, 500, 50), CAButtonTypeRoundedRect);
	getMyGroupListBtn->setTitleForState(CAControlStateAll, "accept mygroup");
	getMyGroupListBtn->addTarget(this, CAControl_selector(SecondViewController::onButtonGetMyGroups), CAControlEventTouchUpInSide);
	this->getView()->addSubview(getMyGroupListBtn);

//	//好友添加界面
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

void SecondViewController::onButtonSearch(CAControl* control, CCPoint point)
{

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

void SecondViewController::onButtonLogin(CAControl* control, CCPoint point)
{
	HXSDKController::getInstance()->Login("lhjtest", "123aa123");
}

void SecondViewController::onButtonLogOff(CAControl* control, CCPoint point)
{
	HXSDKController::getInstance()->Logout();
}

void SecondViewController::onButtonSendText(CrossApp::CAControl *control, CrossApp::CCPoint point)
{

}


void SecondViewController::onButtonGetFriends(CrossApp::CAControl *control, CrossApp::CCPoint point)
{
	HXSDKController::getInstance()->getFriendsList();
}

void SecondViewController::onButtonGetGroups(CrossApp::CAControl *control, CrossApp::CCPoint point)
{

	HXSDKController::getInstance()->getPublicGroupList();
}

void SecondViewController::onButtonCreateGroup(CrossApp::CAControl *control, CrossApp::CCPoint point)
{
	//HXSDKController::getInstance()->createGroup(eHXSDKGroupStyle_PublicOpenJoin, UTF8("傻逼群组"), UTF8("傻逼描述"));
}

void SecondViewController::onButtonGetMyGroups(CrossApp::CAControl *control, CrossApp::CCPoint point)
{
	HXSDKController::getInstance()->getMyGroupList();
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