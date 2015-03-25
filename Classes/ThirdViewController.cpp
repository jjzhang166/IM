//
//  ThirdViewController.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-9.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "ThirdViewController.h"
#include "IMDATA.h"
#include "RootWindow.h"
//#include "GroupInfoViewController.h"
#include "data/TableLanguage.h"
#include "table/TableLanguagesfontnewHeader.h"

ThirdViewController::ThirdViewController()
{
    
}

ThirdViewController::~ThirdViewController()
{

}

bool ThirdViewController::init()
{
    if(CAViewController::init())
    {
//        CABarButtonItem* selfButtonItem = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_NAVIGATION_BAR_ITEM_NAME_3).c_str(), NULL, NULL);
//        CABarButtonItem* searchButtonItem = CABarButtonItem::create("", CAImage::create(NAVIGATION_BAR_ITEM_SEARCH_NORMAL), CAImage::create(NAVIGATION_BAR_ITEM_SEARCH_SELECTED));
//        searchButtonItem->setTarget(this, CAControl_selector(ThirdViewController::onButtonSearch));
//        CABarButtonItem* addButtonItem = CABarButtonItem::create("", CAImage::create(NAVIGATION_BAR_ITEM_ADD_NORMAL), CAImage::create(NAVIGATION_BAR_ITEM_ADD_SELECTED));
//        addButtonItem->setTarget(this, CAControl_selector(ThirdViewController::onButtonAdd));
//        
//        m_pNavigationBarItem = CANavigationBarItem::create("");
//        m_pNavigationBarItem->setShowGoBackButton(false);
//        m_pNavigationBarItem->addLeftButtonItem(selfButtonItem);
//        m_pNavigationBarItem->addRightButtonItem(addButtonItem);
//          m_pNavigationBarItem->addRightButtonItem(searchButtonItem);
//        setNavigationBarItem(m_pNavigationBarItem);
//        m_pNavigationBarItem->retain();
        
        return true;
    }
    return false;
}

void ThirdViewController::viewDidLoad()
{
	CCRect winRect = this->getView()->getBounds();
    CAImageView* imageView = CAImageView::createWithImage(CAImage::create("HelloWorld.png"));
    imageView->setFrame(winRect);
    this->getView()->addSubview(imageView);
    
    CALabel* label = CALabel::createWithCenter(CCRect(winRect.size.width*0.5, winRect.size.height*0.5-270, winRect.size.width, 200));
    label->setTextAlignment(CATextAlignmentCenter);
    label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    label->setFontSize(72 * CROSSAPP_ADPTATION_RATIO);
    label->setText("ThirdViewController");
    label->setColor(CAColor_white);
    this->getView()->insertSubview(label, 1);
}

void ThirdViewController::viewDidAppear()
{
    this->getTabBarController()->setNavigationBarItem(m_pNavigationBarItem);
}

void ThirdViewController::viewDidUnload()
{
    
}

void ThirdViewController::onButtonSearch(CAControl* control, CCPoint point)
{
    
}

void ThirdViewController::onButtonAdd(CAControl* control, CCPoint point)
{
    
}
