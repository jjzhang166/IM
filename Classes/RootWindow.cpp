﻿//
//  RootWindow.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-9.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//


#include "RootWindow.h"
#include "FirstViewController.h"
#include "SecondViewController.h"
#include "IMMyController.h"
#include "IMDATA.h"
#include "HXSDKController.h"
#include "IMLoginRegister.h"

static RootWindow* m_pRootWindow = NULL;

RootWindow* RootWindow::getInstance()
{
    if(!m_pRootWindow)
    {
        m_pRootWindow = new RootWindow();
        m_pRootWindow->init();
        m_pRootWindow->autorelease();
    }
    return m_pRootWindow;
}

RootWindow::RootWindow()
:m_pTabelBarController(NULL)
,m_pNavigationController(NULL)
{
	std::string fullPath = CCFileUtils::sharedFileUtils()->getWritablePath() + "userinformation.db";
	sqlite3_open(fullPath.c_str(), &m_pSqlite3);
}

RootWindow::~RootWindow()
{
    CC_SAFE_RELEASE(m_pTabelBarController);
    CC_SAFE_RELEASE(m_pNavigationController);
	sqlite3_close(m_pSqlite3);
}

bool RootWindow::init()
{
    if (!CAWindow::init())
    {
        return false;
    }
    
    HXSDKController::getInstance()->autoLogin();
    if(!HXSDKController::getInstance()->isLogin())
    {
        init_LoginController();
    }
    else
    {
        init_ViewController();
    }
    return true;
}

void RootWindow::init_LoginController()
{
    IMLoginRegister* LoginController =IMLoginRegister::create(IM_USERLOGIN);
    
    CANavigationController* navigationController = new CANavigationController();
    navigationController->setNavigationBarBackGroundImage(CAImage::create(NAVIGATION_BG));
    navigationController->initWithRootViewController(LoginController);
    this->setRootViewController(navigationController);
}

void RootWindow::init_ViewController()
{
    m_pTabelBarController = init_tabelBarController();
    
    m_pNavigationController = init_navigationController(m_pTabelBarController);
    
    this->setRootViewController(m_pNavigationController);
}

CATabBarController* RootWindow::init_tabelBarController()
{
    CATabBarController* tabelBarController =new CATabBarController();
    std::vector<CAViewController*> views;
    {
        FirstViewController* firstViewController = new FirstViewController();
        firstViewController->init();
        firstViewController->setTabBarItem(CATabBarItem::create("", CAImage::create(TABLE_BAR_IMAGE_0_NORMAL), CAImage::create(TABLE_BAR_IMAGE_0_SELECTED)));
        firstViewController->autorelease();
        views.push_back(firstViewController);
    }
	
    {
        SecondViewController* secondViewController = new SecondViewController();
        secondViewController->init();
        secondViewController->setTabBarItem(CATabBarItem::create("", CAImage::create(TABLE_BAR_IMAGE_1_NORMAL), CAImage::create(TABLE_BAR_IMAGE_1_SELECTED)));
        secondViewController->autorelease();
        views.push_back(secondViewController);
    }
    {
        IMMyController* thirdViewController = new IMMyController();
        thirdViewController->init();
        thirdViewController->setTabBarItem(CATabBarItem::create("", CAImage::create(TABLE_BAR_IMAGE_2_NORMAL), CAImage::create(TABLE_BAR_IMAGE_2_SELECTED)));
        thirdViewController->autorelease();
        views.push_back(thirdViewController);
    }
    
    if(tabelBarController->initWithViewControllers(views))
    {
        tabelBarController->setScrollEnabled(true);
        tabelBarController->setTabBarBackGroundImage(CAImage::create(TABLE_BAR_BG));
        tabelBarController->setTabBarTitleColorForNormal(ccc4(51, 51, 51, 255));
        tabelBarController->setTabBarTitleColorForSelected(CAColor_black);
        tabelBarController->showSelectedViewControllerAtIndex(0);
        
        return tabelBarController;
    }
    return NULL;
}

CANavigationController* RootWindow::init_navigationController(CATabBarController* tableBarController)
{
    CANavigationController* navigationController = new CANavigationController();
    navigationController->setNavigationBarBackGroundImage(CAImage::create(NAVIGATION_BG));
    navigationController->initWithRootViewController(tableBarController);
    return navigationController;
}

CANavigationController* RootWindow::getNavigationController()
{
    return m_pNavigationController;
}



