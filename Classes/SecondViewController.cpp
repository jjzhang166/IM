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
		CABarButtonItem* talkButtonItem = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_NAVIGATION_BAR_ITEM_NAME_2).c_str(), NULL, NULL);
		CABarButtonItem* searchButtonItem = CABarButtonItem::create("", CAImage::create(NAVIGATION_BAR_ITEM_SEARCH_NORMAL), CAImage::create(NAVIGATION_BAR_ITEM_SEARCH_SELECTED));
		searchButtonItem->setTarget(this, CAControl_selector(SecondViewController::onButtonSearch));
		CABarButtonItem* addButtonItem = CABarButtonItem::create("", CAImage::create(NAVIGATION_BAR_ITEM_ADD_NORMAL), CAImage::create(NAVIGATION_BAR_ITEM_ADD_SELECTED));
		addButtonItem->setTarget(this, CAControl_selector(SecondViewController::onButtonAdd));

		m_pNavigationBarItem = CANavigationBarItem::create("");
		m_pNavigationBarItem->setShowGoBackButton(false);
		m_pNavigationBarItem->addLeftButtonItem(talkButtonItem);
		m_pNavigationBarItem->addRightButtonItem(addButtonItem);
		m_pNavigationBarItem->addRightButtonItem(searchButtonItem);
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


	//添加朋友界面实现
	picview();//覆盖界面处理函数
	friendAdd();//朋友添加处理函数
	
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
	m_pPicChoserLayer->setVisible(true);
	addFriendView->setVisible(true);
	
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

//朋友添加函数
void SecondViewController::friendAdd()
{
	static const std::string name[3] = { TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_69).c_str(), 
	TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_39).c_str(),
	TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_20).c_str()};

	addFriendView = CAScale9ImageView::createWithImage(CAImage::create(FRIEND_ADD));
	addFriendView->setFrame(CCRect(420,0,0,0));
	m_pPicChoserLayer->insertSubview(addFriendView, 2);
	addFriendView->setVisible(false);
	CCSize picSize = addFriendView->getFrame().size;

	CAButton *labelone = CAButton::createWithCenter(CCRect(picSize.width*0.5, _px(50), picSize.width*0.9, _px(80)), CAButtonTypeCustom);
	labelone->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_clear));
	labelone->setTitleForState(CAControlStateAll, name[0]);
	labelone->setTitleColorForState(CAControlStateAll, CAColor_white);
	//labelone->addTarget(this, CAControl_selector(), CAControlEventTouchUpInSide);//好友加的群
	addFriendView->addSubview(labelone);

	CAView *lineView = CAView::createWithCenter(CCRect(picSize.width*0.5, _px(80), picSize.width*0.9, _px(1)));
	addFriendView->addSubview(lineView);

	CAButton *labeltwo = CAButton::createWithCenter(CCRect(picSize.width*0.5, _px(130), picSize.width*0.9, _px(80)), CAButtonTypeCustom);
	labeltwo->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_clear));
	labeltwo->setTitleForState(CAControlStateAll, name[1]);
	labeltwo->setTitleColorForState(CAControlStateAll, CAColor_white);
	//labeltwo->addTarget(this, CAControl_selector(), CAControlEventTouchUpInSide);//QQ好友
	addFriendView->addSubview(labeltwo);

	CAView *lineViewtwo = CAView::createWithCenter(CCRect(picSize.width*0.5, _px(160), picSize.width*0.9, _px(1)));
	addFriendView->addSubview(lineViewtwo);

	CAButton *labelthree = CAButton::createWithCenter(CCRect(picSize.width*0.5, _px(210), picSize.width*0.9, _px(80)), CAButtonTypeCustom);
	labelthree->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_clear));
	labelthree->setTitleForState(CAControlStateAll, name[2]);
	labelthree->setTitleColorForState(CAControlStateAll, CAColor_white);
	//labelthree->addTarget(this, CAControl_selector(), CAControlEventTouchUpInSide);//手机联系人
	addFriendView->addSubview(labelthree);
}
//覆盖处理函数
void SecondViewController::picview()
{
	m_pPicChoserLayer = CAView::createWithFrame(this->getView()->getFrame(), ccc4(0, 0, 0, 0));
	m_pPicChoserLayer->setVisible(false);
	this->getView()->addSubview(m_pPicChoserLayer);

	CAButton *pbutton = CAButton::createWithFrame(this->getView()->getFrame(), CAButtonTypeCustom);
	pbutton->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_clear));
	pbutton->setTitleColorForState(CAControlStateAll, CAColor_white);
	pbutton->addTarget(this, CAControl_selector(SecondViewController::onDissmiss), CAControlEventTouchUpInSide);
	m_pPicChoserLayer->insertSubview(pbutton, 1);
}
//界面消失
void SecondViewController::onDissmiss(CAControl* pTarget, CCPoint point)
{
	addFriendView->setVisible(false);
	m_pPicChoserLayer->setVisible(false);
}