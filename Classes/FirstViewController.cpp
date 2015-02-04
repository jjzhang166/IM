//
//  FirstViewController.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-9.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "FirstViewController.h"
#include "IMDATA.h"
#include "IMLoginRegister.h"
#include "RootWindow.h"

FirstViewController::FirstViewController()
:m_pNavigationBarItem(NULL)
,m_pTitleView(NULL)
,m_pSearchTextField(NULL)
{
    

}

FirstViewController::~FirstViewController()
{
    CC_SAFE_RELEASE(m_pNavigationBarItem);
    CC_SAFE_RELEASE(m_pSearchTextField);
}

bool FirstViewController::init()
{
    if(CAViewController::init())
    {
        /*
        CABarButtonItem* popularButtonItem = CABarButtonItem::create(NAVIGATION_BAR_ITEM_NAME_0,
                                                                     CAImage::create(NAVIGATION_BAR_ITEM_POPULAR_NORMAL),
                                                                     CAImage::create(NAVIGATION_BAR_ITEM_POPULAR_SELECTED));
        popularButtonItem->setTarget(this, CAControl_selector(FirstViewController::onButtonPopular));
        CABarButtonItem* newButtonItem = CABarButtonItem::create(NAVIGATION_BAR_ITEM_NAME_1,
                                                                 CAImage::create(NAVIGATION_BAR_ITEM_NEW_NORMAL),
                                                                 CAImage::create(NAVIGATION_BAR_ITEM_NEW_SELECTED));
        newButtonItem->setTarget(this, CAControl_selector(FirstViewController::onButtonNew));
         
        CABarButtonItem* searchButtonItem = CABarButtonItem::create("",
                                                                    CAImage::create(NAVIGATION_BAR_ITEM_SEARCH_NORMAL),
                                                                    CAImage::create(NAVIGATION_BAR_ITEM_SEARCH_SELECTED));
        searchButtonItem->setTarget(this, CAControl_selector(FirstViewController::onButtonSearch));
         */
        CABarButtonItem* addButtonItem = CABarButtonItem::create("",
                                                                 CAImage::create(NAVIGATION_BAR_ITEM_ADD_NORMAL),
                                                                 CAImage::create(NAVIGATION_BAR_ITEM_ADD_SELECTED));
        addButtonItem->setTarget(this, CAControl_selector(FirstViewController::onButtonAdd));
        
        m_pTitleView = CASegmentedControl::createWithFrame(CADipRect(0, 0, 270, 40), 2);
        /* by qiaoxin
        m_pTitleView->setBackgroundImageAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_POPULAR_NORMAL), 0, CAControlStateNormal);
        m_pTitleView->setBackgroundImageAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_POPULAR_NORMAL), 0, CAControlStateHighlighted);
        m_pTitleView->setBackgroundImageAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_POPULAR_SELECTED), 0, CAControlStateSelected);
        m_pTitleView->setBackgroundImageAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_NEW_NORMAL), 1, CAControlStateNormal);
        m_pTitleView->setBackgroundImageAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_NEW_NORMAL), 1, CAControlStateHighlighted);
        m_pTitleView->setBackgroundImageAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_NEW_SELECTED), 1, CAControlStateSelected);
        m_pTitleView->setTitleAtIndex(NAVIGATION_BAR_ITEM_NAME_0, 0, CAControlStateAll);
        m_pTitleView->setTitleColorAtIndex(CAColor_white, 0, CAControlStateNormal);
        m_pTitleView->setTitleColorAtIndex(CAColor_black, 0, CAControlStateSelected);
        m_pTitleView->setTitleAtIndex(NAVIGATION_BAR_ITEM_NAME_1, 1, CAControlStateAll);
        m_pTitleView->setTitleColorAtIndex(CAColor_white, 1, CAControlStateNormal);
        m_pTitleView->setTitleColorAtIndex(CAColor_black, 1, CAControlStateSelected);
         */
        
         m_pTitleView->setImageForSegmentAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_POPULAR_NORMAL), 0, CAControlStateNormal);
         m_pTitleView->setImageForSegmentAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_POPULAR_NORMAL), 0, CAControlStateHighlighted);
         m_pTitleView->setImageForSegmentAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_POPULAR_SELECTED), 0, CAControlStateSelected);
         m_pTitleView->setImageForSegmentAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_NEW_NORMAL), 1, CAControlStateNormal);
         m_pTitleView->setImageForSegmentAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_NEW_NORMAL), 1, CAControlStateHighlighted);
         m_pTitleView->setImageForSegmentAtIndex(CAImage::create(NAVIGATION_BAR_ITEM_NEW_SELECTED), 1, CAControlStateSelected);
         m_pTitleView->setTitleForSegmentAtIndex(NAVIGATION_BAR_ITEM_NAME_0, 0);
         m_pTitleView->setTitleColor(CAColor_white);
         m_pTitleView->setTitleSelectedColor(CAColor_black);
         m_pTitleView->setTitleForSegmentAtIndex(NAVIGATION_BAR_ITEM_NAME_1, 1);
        m_pTitleView->setSelectedAtIndex(0);
        m_pTitleView->addTarget(this, CASegmentedControl_selector(FirstViewController::onButtonSegmented));

        m_pNavigationBarItem = CANavigationBarItem::create("");
        m_pNavigationBarItem->setShowGoBackButton(false);
        /*
        m_pNavigationBarItem->addLeftButtonItem(popularButtonItem);
         m_pNavigationBarItem->addLeftButtonItem(newButtonItem);
         m_pNavigationBarItem->addRightButtonItem(searchButtonItem);
         */
        m_pNavigationBarItem->addRightButtonItem(addButtonItem);
        m_pNavigationBarItem->setTitleView(m_pTitleView);
        m_pNavigationBarItem->retain();
        
        return true;
    }
    return false;
}

void FirstViewController::viewDidLoad()
{
    init_searchBar();
    
	CCRect winRect = this->getView()->getBounds();
    CAImageView* imageView = CAImageView::createWithImage(CAImage::create("HelloWorld.png"));
    imageView->setFrame(winRect);
    this->getView()->addSubview(imageView);
    
    CALabel* label = CALabel::createWithCenter(CCRect(winRect.size.width*0.5, winRect.size.height*0.5-270, winRect.size.width, 200));
    label->setTextAlignment(CATextAlignmentCenter);
    label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    label->setFontSize(72 * CROSSAPP_ADPTATION_RATIO);
    label->setText("FirstViewController");
    label->setColor(CAColor_white);
    this->getView()->insertSubview(label, 1);
}

void FirstViewController::viewDidAppear()
{
    this->getTabBarController()->setNavigationBarItem(m_pNavigationBarItem);
}

void FirstViewController::viewDidUnload()
{

}

void FirstViewController::init_searchBar()
{
    CADipSize size = this->getView()->getBounds().size;
    
    CAScale9ImageView* searchBackground = CAScale9ImageView::createWithImage(CAImage::create(TABLE_GRAY_BG));
    searchBackground->setFrame(CADipRect(0.0f, 0.0f, size.width, 75.0f));
    this->getView()->insertSubview(searchBackground, 10);
    
    m_pSearchTextField = CATextField::createWithFrame(CADipRect(20.0f, 10.0f, size.width-40.0f, 50.0f));
    m_pSearchTextField->setBackgroundView(CAView::createWithColor(CAColor_white));
    m_pSearchTextField->setPlaceHolder(SEARCH_CONTENT_TEXT);
    m_pSearchTextField->setSpaceHolderColor(ccc4(0x96, 0x96, 0x96, 0xff));
    m_pSearchTextField->setFontSize(_px(28.0f));
    m_pSearchTextField->setDelegate(this);
    m_pSearchTextField->setKeyboardReturnType(KEY_BOARD_RETURN_SEARCH);
    searchBackground->addSubview(m_pSearchTextField);
}
/*
void FirstViewController::onButtonPopular(CAControl* control, CCPoint point)
{
    
}

void FirstViewController::onButtonNew(CAControl* control, CCPoint point)
{
    
}

void FirstViewController::onButtonSearch(CAControl* control, CCPoint point)
{
    
}
*/
void FirstViewController::onButtonAdd(CAControl* control, CCPoint point)
{
    //qiaoxin test
    IMLoginRegister* aaa =IMLoginRegister::create(IM_USERLOGIN);
    RootWindow::getInstance()->getNavigationController()->pushViewController(aaa, true);
}

void FirstViewController::onButtonSegmented(CASegmentedControl*, int index)
{
    switch (index) {
        case 0:
            
            break;
        case 1:
            
            break;
        default:
            break;
    }
}

#pragma mark TextFieldDelegate

bool FirstViewController::onTextFieldAttachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool FirstViewController::onTextFieldDetachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool FirstViewController::onTextFieldInsertText(CATextField * sender, const char * text, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(text);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

bool FirstViewController::onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(delText);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}




