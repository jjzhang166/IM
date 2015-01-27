//
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
    
}

RootWindow::~RootWindow()
{
    CC_SAFE_RELEASE(m_pTabelBarController);
    CC_SAFE_RELEASE(m_pNavigationController);
}

bool RootWindow::init()
{
    if (!CAWindow::init())
    {
        return false;
    }
    
    m_pTabelBarController = init_tabelBarController();
    
    m_pNavigationController = init_navigationController(m_pTabelBarController);
    
    this->setRootViewController(m_pNavigationController);
    return true;
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
        //tabelBarController->setTabBarBackGroundImage(<#CrossApp::CAImage *var#>)
        
        
        //        CATabBar* tabBar = tabelBarController->getTabBar();
        //        tabBar->setBackGroundView(CAScale9ImageView::createWithImage(CAImage::create(TABLE_BAR_BG)));
        //        tabBar->setSelectedBackGroundView(CAView::createWithColor(CAColor_clear));
        //        tabBar->setTitleColorForNormal(ccc4(51, 51, 51, 255));
        //        tabBar->setTitleColorForSelected(CAColor_black);
        //        tabBar->setSelectedAtIndex(0);
        
        
        tabelBarController->setTabBarBackGroundImage(CAImage::create(TABLE_BAR_BG));
        //tabelBarController->setTabBarSelectedBackGroundImage(CrossApp::CAImage *var);
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



