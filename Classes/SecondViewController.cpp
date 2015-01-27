//
//  SecondViewController.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-9.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "SecondViewController.h"
#include "IMDATA.h"
#include "groupview\GroupInfoViewController.h"
#include "RootWindow.h"
#include "HXSDKController.h"


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
    if(CAViewController::init())
    {
        CABarButtonItem* talkButtonItem = CABarButtonItem::create(NAVIGATION_BAR_ITEM_NAME_2, NULL, NULL);
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
    loginBtn->setTitleForState(CAControlStateAll, "登录") ;
    loginBtn->addTarget(this, CAControl_selector(SecondViewController::onButtonLogin), CAControlEventTouchUpInSide);
    this->getView()->addSubview(loginBtn);
    
    CAButton * logoutBtn = CAButton::createWithFrame(CCRect(100, 200, 500, 50), CAButtonTypeRoundedRect);
    logoutBtn->setTitleForState(CAControlStateAll, "退出") ;
    logoutBtn->addTarget(this, CAControl_selector(SecondViewController::onButtonLogOff), CAControlEventTouchUpInSide);
    this->getView()->addSubview(logoutBtn);
    
    CAButton * sendMsgBtn = CAButton::createWithFrame(CCRect(100, 300, 500, 50), CAButtonTypeRoundedRect);
    sendMsgBtn->setTitleForState(CAControlStateAll, "发送消息") ;
    sendMsgBtn->addTarget(this, CAControl_selector(SecondViewController::onButtonSendText), CAControlEventTouchUpInSide);
    this->getView()->addSubview(sendMsgBtn);

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
    GroupInfo info = GroupInfo(CAImage::create("HelloWorld.png"), CCString::create("我是主题"), CCString::create("我是介绍"), CCString::create("我是群主"), CCString::create("我是权限"), true, 520);
    GroupInfoViewController * _group = GroupInfoViewController::create(info,false);
    RootWindow::getInstance()->getNavigationController()->pushViewController(_group, true);
    
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
    
};