//
//  IMMyController.cpp
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "IMMyController.h"
#include "IMDATA.h"
#include "IMMyInfo.h"
#include "RootWindow.h"
#include "AddHeadForgrand.h"
#include "IMSetting.h"
//构造函数
IMMyController::IMMyController() :cell(NULL), m_pTableView(NULL)
{
	
}
//析构函数
IMMyController::~IMMyController()
{
	CC_SAFE_RELEASE(m_pNavigationBarItem);   //release掉navigationbaritem
}
/*controller的初始化*/
bool IMMyController::init()
{
	if (CAViewController::init())
	{
		/*添加按钮*/
		CABarButtonItem* addButtonItem = CABarButtonItem::create("", CAImage::create(NAVIGATION_BAR_ITEM_ADD_NORMAL), CAImage::create(NAVIGATION_BAR_ITEM_ADD_SELECTED));
		addButtonItem->setTarget(this, CAControl_selector(IMMyController::onButtonAdd));

		m_pNavigationBarItem = CANavigationBarItem::create(UTF8("我"));
		m_pNavigationBarItem->setShowGoBackButton(false); 
		m_pNavigationBarItem->addRightButtonItem(addButtonItem);
		setNavigationBarItem(m_pNavigationBarItem);
		m_pNavigationBarItem->retain();
		return true;
	}
	return false;
}
/*界面的初始化，主要就是初始化一个tableview*/
void IMMyController::viewDidLoad()
{
	winSize = this->getView()->getBounds().size;
	m_pTableView = CATableView::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.5, winSize.width, winSize.height));
	m_pTableView->setTableViewDataSource(this);
	m_pTableView->setTableViewDelegate(this);
	m_pTableView->setAllowsSelection(true);
	this->getView()->addSubview(m_pTableView);
}

void IMMyController::viewDidUnload()
{

}
/*刷新界面，把navigationitem加载到顶部*/
void IMMyController::viewDidAppear()
{
}

void IMMyController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	//cell点击处理事件
	if (section == 0){
		IMMyInfo *pIMMyInfo = IMMyInfo::create();
		RootWindow::getInstance()->getNavigationController()->pushViewController(pIMMyInfo, true);
	}
	else if (section == 1){
		//通讯录
	}
	else if (section == 2)
	{
		//点击设置栏，进入用户设置页面
		IMSetting *pIMSetting = IMSetting::create();
		RootWindow::getInstance()->getNavigationController()->pushViewController(pIMSetting, true);
	}
	else{
	}
}

void IMMyController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{

}

CATableViewCell* IMMyController::tableCellAtIndex(CATableView* table, const CCSize& cellsize, unsigned int section, unsigned int row)
{
	/*cell页面的初始化*/
	cell = table->dequeueReusableCellWithIdentifier("CrossApp");
	switch (section)
	{
		case 0:
		{
			/*初始化用户信息栏*/
			cell = initViewOfMe(cellsize);
			return cell;
			break;
		}
		case 1:
		{   /*初始化通讯录栏*/
				cell = initViewOfContanct(cellsize);
			  return cell;
			  break;
		}
		case 2:
		{     /*初始化设置栏*/
			  cell = initViewOfSetting(cellsize);
			  return cell;
			  break;
		}
		default:
			break;
	}
}

CATableViewCell* IMMyController::initViewOfMe(const CCSize& cellsize)
{
	if (cell == NULL)
	{
		
		cell = CATableViewCell::create("CrossApp");
		/*添加头像view*/
		CAImageView *phead = CAImageView::createWithCenter(CCRect(cellsize.width*0.1, cellsize.height*0.5, _px(120), _px(120)));
		phead->setTag(300);
		AddHeadForgrand::getInstance()->addHeadForgrand(phead);
		cell->addSubview(phead);
		
		/*添加用户名label*/
		CALabel *pname = CALabel::createWithCenter(CCRect(cellsize.width*0.6, cellsize.height*0.25, cellsize.width*0.8, cellsize.height*0.5));
		pname->setColor(CAColor_black);
		pname->setTextAlignment(CATextAlignmentLeft);
		pname->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		pname->setFontSize(_px(30));
		pname->setTag(301);
		cell->addSubview(pname);
		/*添加用户自我介绍label*/
		CALabel *pcontent = CALabel::createWithCenter(CCRect(cellsize.width*0.6, cellsize.height*0.75, cellsize.width*0.8, cellsize.height*0.5));
		pcontent->setColor(CAColor_gray);
		pcontent->setTextAlignment(CATextAlignmentLeft);
		pcontent->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
		pcontent->setFontSize(_px(30));
		pcontent->setTag(302);
		cell->addSubview(pcontent);
		
	}
	//获取网络数据源或者本地数据库,暂时用本地数据代替
	CAImageView *p_head = (CAImageView*)cell->getSubviewByTag(300);
	p_head->setImage(CAImage::create("head.png"));

	CALabel *p_name = (CALabel*)cell->getSubviewByTag(301);
	p_name->setText(UTF8("我的用户名"));

	CALabel *p_content = (CALabel*)cell->getSubviewByTag(302);
	p_content->setText(UTF8("我的自我介绍"));

	return cell;
}

CATableViewCell* IMMyController::initViewOfContanct(const CCSize& cellsize)
{
	if (cell == NULL)
	{
		/*同用户信息设置栏*/
		cell = CATableViewCell::create("CrossApp");
		CAImageView *image = CAImageView::createWithCenter(CCRect(cellsize.width*0.1, cellsize.height*0.5, _px(69), _px(69)));
		image->setImage(CAImage::create(CONTANCT_ICON));
		cell->addSubview(image);

		CALabel *plabel = CALabel::createWithCenter(CCRect(cellsize.width*0.3, cellsize.height*0.5, cellsize.width*0.2, cellsize.height*0.6));
		plabel->setColor(CAColor_black);
		plabel->setTextAlignment(CATextAlignmentLeft);
		plabel->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		plabel->setFontSize(_px(30));
		plabel->setText(UTF8("通讯录"));
		cell->addSubview(plabel);
	}
	return cell;
}

CATableViewCell* IMMyController::initViewOfSetting(const CCSize& cellsize)
{
	if (cell == NULL)
	{
		/*同上*/
		cell = CATableViewCell::create("CrossApp");
		CAImageView *image2 = CAImageView::createWithCenter(CCRect(cellsize.width*0.1, cellsize.height*0.5, _px(60), _px(60)));
		image2->setImage(CAImage::create(SETTING_ICON));
		cell->addSubview(image2);

		CALabel *plabel2 = CALabel::createWithCenter(CCRect(cellsize.width*0.3, cellsize.height*0.5, cellsize.width*0.2, cellsize.height*0.6));
		plabel2->setColor(CAColor_black);
		plabel2->setTextAlignment(CATextAlignmentLeft);
		plabel2->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		plabel2->setFontSize(_px(30));
		plabel2->setText(UTF8("设置"));
		cell->addSubview(plabel2);
	}
	return cell;
}



/*在section之间添加一个view，就是UI中section之间的灰色地带*/
CAView* IMMyController::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
	CAView* view = CAView::createWithColor(ccc4(230, 230, 230, 255));
	return view;
}

/*设置每个section含有的cell个数*/
unsigned int IMMyController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	return 1;
}

/*设置含有几个section*/
unsigned int IMMyController::numberOfSections(CATableView *table)
{
	return 3;
}

unsigned int IMMyController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{	/*section的大小设置*/
	switch (section)
	{
	case 0:
		{
			 return winSize.height*0.2;
			 break;
		}
	case 1:
	{
			  return winSize.height*0.13;
			  break;
	}
	case 2:
	{
			  return winSize.height*0.13;
			  break;
	}
	}
}

unsigned int IMMyController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
	return _px(25);
}

void IMMyController::onButtonAdd(CAControl* control, CCPoint point)
{
	//进入添加页面
}