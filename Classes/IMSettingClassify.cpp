//
//  IMSettingClassify.cpp
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#include "IMDATA.h"
#include "IMSettingClassify.h"
#include "data/TableLanguage.h"
#include "table/TableLanguagesfontnewHeader.h"

#pragma NewMessageSet
IMSettingClassifyNewMessage::IMSettingClassifyNewMessage() :m_pTableView(NULL)
, pNavigationBarItem(NULL)
, cell(NULL)
, label1(NULL)
, m_pSwitch(NULL)
{

}
IMSettingClassifyNewMessage::~IMSettingClassifyNewMessage()
{
	CC_SAFE_RELEASE(pNavigationBarItem);
}
bool IMSettingClassifyNewMessage::init()
{
	if (CAViewController::init())
	{
		pNavigationBarItem = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_37).c_str());
		setNavigationBarItem(pNavigationBarItem);
		return true;
	}
}
void IMSettingClassifyNewMessage::viewDidLoad()
{
	winSize = this->getView()->getBounds().size;
	this->getView()->setColor(ccc4(230, 230, 230, 255));
	m_pTableView = CATableView::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.15, winSize.width, winSize.height*0.2));
	m_pTableView->setTableViewDelegate(this);
	m_pTableView->setTableViewDataSource(this);
	m_pTableView->setAllowsSelection(false);
	this->getView()->addSubview(m_pTableView);

}
void IMSettingClassifyNewMessage::viewDidUnload()
{

}
void IMSettingClassifyNewMessage::viewDidAppear()
{

}
CATableViewCell* IMSettingClassifyNewMessage::tableCellAtIndex(CATableView* table, const CCSize& viewSize, unsigned int section, unsigned int row)
{
	cell = table->dequeueReusableCellWithIdentifier("CrossApp");
	if (cell == NULL)
	{
		cell = CATableViewCell::create("CrossApp");
		label1 = CALabel::createWithFrame(CCRect(_px(40), 0, viewSize.width*0.5, viewSize.height));
		label1->setTextAlignment(CATextAlignmentLeft);
		label1->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		label1->setColor(CAColor_black);
		label1->setFontSize(_px(30));
		if (row == 0){
			label1->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_59).c_str());
		}
		else{
			label1->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_60).c_str());
		}
		cell->addSubview(label1);
		m_pSwitch = CASwitch::createWithCenter(CCRect(viewSize.width*0.85, viewSize.height*0.5, 155, 95));
		m_pSwitch->setOnImage(CAImage::create(SWITCH_ON));
		m_pSwitch->setOffImage(CAImage::create(SWITCH_OFF));
		m_pSwitch->setIsOn(false,true);
		cell->addSubview(m_pSwitch);
	}
	return cell;
}
unsigned int IMSettingClassifyNewMessage::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	return 2;
}
unsigned int IMSettingClassifyNewMessage::numberOfSections(CATableView *table)
{
	return 1;
}
unsigned int IMSettingClassifyNewMessage::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	return winSize.height*0.1;
}

#pragma changePwd
IMSettingClassifyPwd::IMSettingClassifyPwd() :plabel1(NULL)
, plabel2(NULL)
, ptextpwd(NULL)
, ptextpwdNew(NULL)
, ptextpwdNewAgain(NULL)
, pNavigationBarItem(NULL)
{

}

IMSettingClassifyPwd::~IMSettingClassifyPwd()
{
	CC_SAFE_RELEASE(pNavigationBarItem);
}

bool IMSettingClassifyPwd::init()
{
	if (CAViewController::init())
	{
		//完成按钮
		CABarButtonItem* addFinishBtn = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_19).c_str(), NULL, NULL);
		addFinishBtn->setTarget(this, CAControl_selector(IMSettingClassifyPwd::onFinish));

		//获取头部信息
		pNavigationBarItem = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_55).c_str());
		pNavigationBarItem->addRightButtonItem(addFinishBtn);
		setNavigationBarItem(pNavigationBarItem);
		//m_pNavigationBarItem->retain();
		return true;
	}
}

void IMSettingClassifyPwd::viewDidLoad()
{
	winSize = this->getView()->getBounds().size;
	this->getView()->setColor(ccc4(230, 230, 230, 255));
	plabel1 = CALabel::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.05, winSize.width*0.9, winSize.height*0.08));
	plabel1->setTextAlignment(CATextAlignmentLeft);
	plabel1->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	plabel1->setColor(CAColor_gray);
	plabel1->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_61).c_str());
	plabel1->setFontSize(_px(30));
	this->getView()->addSubview(plabel1);

	ptextpwd = CATextField::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.15, winSize.width, winSize.height*0.1));
	ptextpwd->setHoriMargins(_px(43));
	ptextpwd->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_62).c_str());
	ptextpwd->setDelegate(this);
	this->getView()->addSubview(ptextpwd);

	plabel2 = CALabel::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.25, winSize.width*0.9, winSize.height*0.08));
	plabel2->setTextAlignment(CATextAlignmentLeft);
	plabel2->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	plabel2->setColor(CAColor_gray);
	plabel2->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_63).c_str());
	plabel2->setFontSize(_px(30));
	this->getView()->addSubview(plabel2);

	ptextpwdNew = CATextField::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.35, winSize.width, winSize.height*0.1));
	ptextpwdNew->setHoriMargins(_px(43));
	ptextpwdNew->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_PASSWORD).c_str());
	ptextpwdNew->setDelegate(this);
	this->getView()->addSubview(ptextpwdNew);

	//CAView* lineView = CAView::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.4, winSize.width*0.9, _px(1)), ccc4(200, 200, 200, 255));
	//this->getView()->addSubview(lineView);

	ptextpwdNewAgain = CATextField::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.45, winSize.width, winSize.height*0.1));
	ptextpwdNewAgain->setHoriMargins(_px(43));
	ptextpwdNewAgain->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_64).c_str());
	ptextpwdNewAgain->setDelegate(this);
	this->getView()->addSubview(ptextpwdNewAgain);

}
void IMSettingClassifyPwd::viewDidUnload()
{

}
void IMSettingClassifyPwd::onFinish(CAControl *ptarget, CCPoint point)
{
	//完成密码修改，实现网络数据传输
}

#pragma suggestion
IMSettingClassifySuggestion::IMSettingClassifySuggestion() :content(NULL)
, result(NULL)
, pNavigationBarItem(NULL)
{

}

IMSettingClassifySuggestion::~IMSettingClassifySuggestion()
{
	CC_SAFE_RELEASE(pNavigationBarItem);
}

bool IMSettingClassifySuggestion::init()
{
	if (CAViewController::init())
	{
		//完成按钮
		CABarButtonItem* addFinishBtn = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_65).c_str(), NULL, NULL);
		addFinishBtn->setTarget(this, CAControl_selector(IMSettingClassifySuggestion::onFinish));

		//获取头部信息
		pNavigationBarItem = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_56).c_str());
		pNavigationBarItem->addRightButtonItem(addFinishBtn);
		setNavigationBarItem(pNavigationBarItem);
		return true;
	}
}

void IMSettingClassifySuggestion::viewDidLoad()
{
	winSize = this->getView()->getBounds().size;
	content = CATextField::createWithFrame(CCRect(0,0, winSize.width, winSize.height*0.4));
	content->setHoriMargins(_px(20));
	content->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_66).c_str());
	content->setFontSize(_px(30));
	content->setDelegate(this);
	this->getView()->addSubview(content);

	result = CAButton::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.5, 200, 80), CAButtonTypeRoundedRect);
	result->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_green));
	result->setTitleForState(CAControlStateAll, TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_67).c_str());
	result->setTitleColorForState(CAControlStateAll, CAColor_white);
	this->getView()->addSubview(result);
	result->setVisible(true);
}
void IMSettingClassifySuggestion::viewDidUnload()
{

}
void IMSettingClassifySuggestion::onFinish(CAControl *ptarget, CCPoint point)
{
	//完成意见修改，实现网络数据传输
}






static IMSettingClassify *setting = NULL;
IMSettingClassify::IMSettingClassify()
{

}
IMSettingClassify::~IMSettingClassify()
{
	CC_SAFE_DELETE(setting);
}
IMSettingClassify* IMSettingClassify::getInstance()
{
	if (!setting)
	{
		setting = new IMSettingClassify();
	}
	return setting;
}
IMSettingClassifyNewMessage* IMSettingClassify::messageCreate()
{
	IMSettingClassifyNewMessage *messageset = new IMSettingClassifyNewMessage();
	messageset->init();
	messageset->autorelease();
	return messageset;
}

IMSettingClassifyPwd* IMSettingClassify::pwdChangeCreate()
{
	IMSettingClassifyPwd *pwdchange = new IMSettingClassifyPwd();
	pwdchange->init();
	pwdchange->autorelease();
	return pwdchange;
}

IMSettingClassifySuggestion* IMSettingClassify::suggestionCreate()
{
	IMSettingClassifySuggestion *pwdchange = new IMSettingClassifySuggestion();
	pwdchange->init();
	pwdchange->autorelease();
	return pwdchange;
}