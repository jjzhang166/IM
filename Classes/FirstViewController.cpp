
#include "FirstViewController.h"
#include "IMDATA.h"

FirstViewController::FirstViewController()
:m_pNavigationBarItem(NULL)
,m_pTitleView(NULL)
{
    

}

FirstViewController::~FirstViewController()
{
    CC_SAFE_RELEASE(m_pNavigationBarItem);
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
         */
        CABarButtonItem* searchButtonItem = CABarButtonItem::create("",
                                                                    CAImage::create(NAVIGATION_BAR_ITEM_SEARCH_NORMAL),
                                                                    CAImage::create(NAVIGATION_BAR_ITEM_SEARCH_SELECTED));
        searchButtonItem->setTarget(this, CAControl_selector(FirstViewController::onButtonSearch));
        CABarButtonItem* addButtonItem = CABarButtonItem::create("",
                                                                 CAImage::create(NAVIGATION_BAR_ITEM_ADD_NORMAL),
                                                                 CAImage::create(NAVIGATION_BAR_ITEM_ADD_SELECTED));
        addButtonItem->setTarget(this, CAControl_selector(FirstViewController::onButtonAdd));
        
        m_pTitleView = CASegmentedControl::createWithFrame(CADipRect(0, 0, 270, 40), 2);
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
        m_pTitleView->setSelectedAtIndex(0);
        m_pTitleView->addTarget(this, CAControl_selector(FirstViewController::onButtonSegmented));

        
        m_pNavigationBarItem = CANavigationBarItem::create("");
        m_pNavigationBarItem->setShowGoBackButton(false);
        /*
        m_pNavigationBarItem->addLeftButtonItem(popularButtonItem);
        m_pNavigationBarItem->addLeftButtonItem(newButtonItem);
         */
        
        m_pNavigationBarItem->addRightButtonItem(addButtonItem);
        m_pNavigationBarItem->addRightButtonItem(searchButtonItem);
        m_pNavigationBarItem->setTitleView(m_pTitleView);
        m_pNavigationBarItem->retain();
        return true;
    }
    return false;
}

void FirstViewController::viewDidLoad()
{
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
/*
void FirstViewController::onButtonPopular(CAControl* control, CCPoint point)
{
    
}

void FirstViewController::onButtonNew(CAControl* control, CCPoint point)
{
    
}
*/
void FirstViewController::onButtonSearch(CAControl* control, CCPoint point)
{
    
}

void FirstViewController::onButtonAdd(CAControl* control, CCPoint point)
{
    
}

void FirstViewController::onButtonSegmented(CAControl* control, CCPoint point)
{
    if (0 == m_pTitleView->getSelectedIndex())
    {
      
    }
    else
    {
       
    }
}





