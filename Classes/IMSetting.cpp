//
//  IMSetting.cpp
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "IMSetting.h"
#include "IMDATA.h"
#include "RootWindow.h"
#include "IMSettingClassify.h"
IMSetting::IMSetting() :pNagivationitem(NULL)
, m_pTableView(NULL)
, cell(NULL)
, newMessage(NULL)
, changePwd(NULL)
, suggestion(NULL)
, score(NULL)
, logout(NULL)
{

}

IMSetting::~IMSetting()
{
	CC_SAFE_RELEASE(pNagivationitem);
}

bool IMSetting::init()
{
	if (CAViewController::init())
	{
		pNagivationitem = CANavigationBarItem::create(UTF8("设置"));
		setNavigationBarItem(pNagivationitem);
		return true;
	}
}

IMSetting* IMSetting::create()
{
	IMSetting *pIMSetting = new IMSetting();
	pIMSetting->init();
	pIMSetting->autorelease();
	return pIMSetting;
}
void IMSetting::viewDidLoad()
{
	winSize = this->getView()->getBounds().size;
	m_pTableView = CATableView::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.5, winSize.width, winSize.height));
	m_pTableView->setTableViewDelegate(this);
	m_pTableView->setTableViewDataSource(this);
	m_pTableView->setAllowsSelection(true);
	this->getView()->addSubview(m_pTableView);
}
void IMSetting::viewDidUnload()
{

}
void IMSetting::viewDidAppear()
{

}
//点击cell事件
void IMSetting::tableViewDidSelectRowAtIndexPath(CATableView *table, unsigned int section, unsigned int row)
{
	if (section == 0)
	{
		IMSettingClassifyNewMessage *pmessage = IMSettingClassify::getInstance()->messageCreate();
		RootWindow::getInstance()->getNavigationController()->pushViewController(pmessage, true);
	}
	else if (section == 1)
	{
		IMSettingClassifyPwd *pmessage = IMSettingClassify::getInstance()->pwdChangeCreate();
		RootWindow::getInstance()->getNavigationController()->pushViewController(pmessage, true);
	}
	else if (section == 2 && row == 0)
	{
		IMSettingClassifySuggestion *pmessage = IMSettingClassify::getInstance()->suggestionCreate();
		RootWindow::getInstance()->getNavigationController()->pushViewController(pmessage, true);
	}
}
void IMSetting::tableViewDidDeselectRowAtIndexPath(CATableView *table, unsigned int section, unsigned int row)
{

}

CATableViewCell* IMSetting::tableCellAtIndex(CATableView *table,const CCSize& cellsize, unsigned int section, unsigned int row)
{

	/*cell页面的初始化*/
	cell = table->dequeueReusableCellWithIdentifier("CrossApp");
	switch (section)
	{
	case 0:
	{
		 cell = initMessage(cellsize);
		 return cell;
		 break;

	}
	case 1:
	{
		cell = initChangePwd(cellsize);
		return cell;
	    break;
	}
	case 2:
	{
			  switch (row)
			  {
			  case 0:
			  {
						cell = initSuggestion(cellsize);
						return cell;
						break;
			  }
			  case 1:
			  {
						cell = initScore(cellsize);
						return cell;
						break;
			  }
			  }
	}
	case 3:
	{
		cell = initLogout(cellsize);
		return cell;
		break;
	}
	default:
		break;
	}
}

CATableViewCell* IMSetting::initMessage(const CCSize& cellsize)
{

	if (cell == NULL)
	{
		cell = CATableViewCell::create("CrossApp");
		CALabel *nickname = CALabel::createWithFrame(CCRect(35, 0, cellsize.width*0.2, cellsize.height));
		nickname->setColor(CAColor_black);
		nickname->setTextAlignment(CATextAlignmentLeft);
		nickname->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		nickname->setText(UTF8("新消息提醒"));
		nickname->setFontSize(_px(30));
		cell->addSubview(nickname);

		newMessage = CALabel::createWithFrame(CCRect(cellsize.width*0.35, 0, cellsize.width*0.4, cellsize.height));
		newMessage->setColor(CAColor_gray);
		newMessage->setTextAlignment(CATextAlignmentLeft);
		newMessage->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		newMessage->setFontSize(_px(30));
		newMessage->setTag(601);
		cell->addSubview(newMessage);
	}
	//网络获取数据或者本地获取，暂时用常量代替
	CALabel *pUserName = (CALabel*)cell->getSubviewByTag(601);
	pUserName->setText(UTF8("震动"));
	return cell;
}

CATableViewCell* IMSetting::initChangePwd(const CCSize& cellsize)
{
	if (cell == NULL)
	{
		cell = CATableViewCell::create("CrossApp");
		changePwd = CALabel::createWithFrame(CCRect(35, 0, cellsize.width*0.2, cellsize.height));
		changePwd->setColor(CAColor_black);
		changePwd->setTextAlignment(CATextAlignmentLeft);
		changePwd->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		changePwd->setText(UTF8("修改密码"));
		changePwd->setFontSize(_px(30));
		cell->addSubview(changePwd);
	}
	return cell;
}
CATableViewCell* IMSetting::initSuggestion(const CCSize& cellsize)
{
	if (cell == NULL)
	{
		cell = CATableViewCell::create("CrossApp");
		suggestion = CALabel::createWithFrame(CCRect(35, 0, cellsize.width*0.2, cellsize.height));
		suggestion->setColor(CAColor_black);
		suggestion->setTextAlignment(CATextAlignmentLeft);
		suggestion->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		suggestion->setText(UTF8("意见反馈"));
		suggestion->setFontSize(_px(30));
		cell->addSubview(suggestion);
	}
	return cell;
}
CATableViewCell* IMSetting::initScore(const CCSize& cellsize)
{
	if (cell == NULL)
	{
		cell = CATableViewCell::create("CrossApp");
		score = CALabel::createWithFrame(CCRect(35, 0, cellsize.width*0.2, cellsize.height));
		score->setColor(CAColor_black);
		score->setTextAlignment(CATextAlignmentLeft);
		score->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		score->setText(UTF8("去评分"));
		score->setFontSize(_px(30));
		cell->addSubview(score);
	}
	return cell;
}
CATableViewCell* IMSetting::initLogout(const CCSize& cellsize)
{
	if (cell == NULL)
	{
		cell = CATableViewCell::create("CrossApp");
		logout = CALabel::createWithCenter(CCRect(cellsize.width*0.5, cellsize.height*0.5, cellsize.width*0.8, cellsize.height));
		logout->setColor(CAColor_black);
		logout->setTextAlignment(CATextAlignmentCenter);
		logout->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		logout->setText(UTF8("退出登录"));
		logout->setFontSize(_px(30));
		cell->addSubview(logout);
	}
	return cell;
}

CAView* IMSetting::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& cellsize, unsigned int section)
{
	CAView* view = CAView::createWithColor(ccc4(230, 230, 230, 255));
	return view;
}
unsigned int IMSetting::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	if (section == 2){
		return 2;
	}
	else{
		return 1;

	}
}
unsigned int IMSetting::numberOfSections(CATableView *table)
{
	return 4;
}
unsigned int IMSetting::tableViewHeightForRowAtIndexPath(CATableView *table, unsigned int section, unsigned int row)
{
	return winSize.height*0.1;
}
unsigned int IMSetting::tableViewHeightForHeaderInSection(CATableView *table, unsigned int section)
{
	return _px(45);
}