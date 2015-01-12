

#include "RootWindow.h"
#include "FirstViewController.h"
#include "SecondViewController.h"
#include "ThirdViewController.h"
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
    m_pTabelBarController->release();
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
        firstViewController->setTabBarItem(CATabBarItem::create(TABLE_BAR_LABEL_0, CAImage::create(TABLE_BAR_IMAGE_0_NORMAL), CAImage::create(TABLE_BAR_IMAGE_0_SELECTED)));
        firstViewController->autorelease();
        views.push_back(firstViewController);
    }
    {
        SecondViewController* secondViewController = new SecondViewController();
        secondViewController->init();
        secondViewController->setTabBarItem(CATabBarItem::create(TABLE_BAR_LABEL_1, CAImage::create(TABLE_BAR_IMAGE_1_NORMAL), CAImage::create(TABLE_BAR_IMAGE_1_SELECTED)));
        secondViewController->autorelease();
        views.push_back(secondViewController);
    }
    {
        ThirdViewController* thirdViewController = new ThirdViewController();
        thirdViewController->init();
        thirdViewController->setTabBarItem(CATabBarItem::create(TABLE_BAR_LABEL_2, CAImage::create(TABLE_BAR_IMAGE_2_NORMAL), CAImage::create(TABLE_BAR_IMAGE_2_SELECTED)));
        thirdViewController->autorelease();
        views.push_back(thirdViewController);
    }
    
    if(tabelBarController->initWithViewControllers(views))
    {
        CATabBar* tabBar = tabelBarController->getTabBar();
        tabBar->setBackGroundView(CAScale9ImageView::createWithImage(CAImage::create("baby_genius/tabBar_background.png")));
        tabBar->setSelectedBackGroundView(CAView::createWithColor(CAColor_clear));
        tabBar->setTitleColorForNormal(ccc4(51, 51, 51, 255));
        tabBar->setTitleColorForSelected(CAColor_black);
        tabBar->setSelectedAtIndex(0);
        return tabelBarController;
    }
    return NULL;
}

CANavigationController* RootWindow::init_navigationController(CATabBarController* tableBarController)
{
    CANavigationController* navigationController = new CANavigationController();
    navigationController->getNavigationBar()->setBackGroundImage(CAImage::create("baby_genius/nav_background.png"));
    navigationController->getNavigationBar()->setTitleColor(CAColor_black);
    navigationController->getNavigationBar()->setButtonColor(ccc4(0x66, 0x66, 0x66, 0xff));
    navigationController->initWithRootViewController(tableBarController);
    return navigationController;
}

