//
//  SecondViewController.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-9.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "SecondViewController.h"
#include "IMDATA.h"

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
    CAImageView* imageView = CAImageView::createWithImage(CAImage::create("HelloWorld.png"));
    imageView->setFrame(winRect);
    this->getView()->addSubview(imageView);
    
    CALabel* label = CALabel::createWithCenter(CCRect(winRect.size.width*0.5, winRect.size.height*0.5-270, winRect.size.width, 200));
    label->setTextAlignment(CATextAlignmentCenter);
    label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    label->setFontSize(72 * CROSSAPP_ADPTATION_RATIO);
    label->setText("SecondViewController");
    label->setColor(CAColor_white);
    this->getView()->insertSubview(label, 1);
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
    
}
