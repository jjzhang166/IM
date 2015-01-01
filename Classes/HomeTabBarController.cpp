//
//  HomeTabBarController.cpp
//  BabyGenius
//
//  Created by 栗元峰 on 14-9-5.
//
//

#include "HomeTabBarController.h"
#include "FirstViewController.h"
#include "IMDATA.h"


HomeTabBarController::HomeTabBarController()
:m_pNewTabBar(NULL)
{

}

HomeTabBarController::~HomeTabBarController()
{
    
}

bool HomeTabBarController::initWithTabBarController()
{
    std::vector<CAViewController*> views;
    
    for (int i=0; i<TABLE_BAR_SIZE; i++) {
        FirstViewController* viewController1 = new FirstViewController();
        viewController1->init();
        viewController1->autorelease();
        views.push_back(viewController1);
    }

    
    return CATabBarController::initWithViewControllers(views);
}

void HomeTabBarController::viewDidLoad()
{
    CATabBarController::viewDidLoad();
    
    m_pTabBar->setVisible(false);
    m_pTabBar->setDelegate(NULL);
    std::vector<CATabBarItem*> items;
    items.push_back(CATabBarItem::create(TABLE_BAR_LABEL_0, CAImage::create(TABLE_BAR_IMAGE_0_NORMAL), CAImage::create(TABLE_BAR_IMAGE_0_SELECTED)));
    items.push_back(CATabBarItem::create(TABLE_BAR_LABEL_1, CAImage::create(TABLE_BAR_IMAGE_1_NORMAL), CAImage::create(TABLE_BAR_IMAGE_1_SELECTED)));
    items.push_back(CATabBarItem::create(TABLE_BAR_LABEL_2, CAImage::create(TABLE_BAR_IMAGE_2_NORMAL), CAImage::create(TABLE_BAR_IMAGE_2_SELECTED)));
    
    m_pNewTabBar = CATabBar::create(items);
    m_pNewTabBar->setBackGroundView(CAScale9ImageView::createWithImage(CAImage::create("baby_genius/tabBar_background.png")));
    m_pNewTabBar->setSelectedBackGroundView(CAView::createWithColor(CAColor_clear));
    m_pNewTabBar->setTitleColorForNormal(ccc4(51, 51, 51, 255));
    m_pNewTabBar->setTitleColorForSelected(CAColor_black);
    this->getView()->addSubview(m_pNewTabBar);
    m_pNewTabBar->setFrame(m_pTabBar->getFrame());
    
    m_pNewTabBar->setDelegate(this);
    m_pNewTabBar->setSelectedAtIndex(0);
}

void HomeTabBarController::viewDidAppear()
{
    CATabBarController::viewDidAppear();
}

void HomeTabBarController::viewDidDisappear()
{
    CATabBarController::viewDidDisappear();
}

void HomeTabBarController::onButton(CrossApp::CAControl *control, CrossApp::CCPoint point)
{
    
}

void HomeTabBarController::tabBarSelectedItem(CATabBar* tabBar, CATabBarItem* item, unsigned int index)
{
    index = index > 2 ? index-1 : index;
    CC_RETURN_IF(m_nSelectedIndex == index);
    this->showSelectedViewControllerAtIndex(index);
}

void HomeTabBarController::tabBarClickToForbidSelectedItem(CATabBar* tabBar, CATabBarItem* item, unsigned int index)
{
    //CADevice::openCamera(this);
}

void HomeTabBarController::getSelectedImage(CAImage *image)
{
  
}



