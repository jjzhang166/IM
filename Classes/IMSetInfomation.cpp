//
//  IMSetInfomation.cpp
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#include "IMSetInformation.h"
#include "IMDATA.h"
#include "RootWindow.h"
static IMSetInformation *p_IMsetinfo = NULL;
IMSetInformation::IMSetInformation() :m_pLabel(NULL)
, m_pText(NULL)
, pbutton1(NULL)
, pbutton2(NULL)
, pchoose(NULL)
, pimage1(NULL)
, pimage2(NULL)
{
	list.insert(pair<IMinfoset, std::string>(NAMESET, UTF8("填写昵称")));
	list.insert(pair<IMinfoset, std::string>(SEXSET, UTF8("确定性别")));
	list.insert(pair<IMinfoset, std::string>(SIGNATURESET, UTF8("个性签名")));
}

IMSetInformation::~IMSetInformation()
{
	list.clear();
	//CC_SAFE_RELEASE(m_pNavigationBarItem);
}

IMSetInformation* IMSetInformation::create(IMinfoset p_infoset)
{
	p_IMsetinfo = new IMSetInformation();
	p_IMsetinfo->infoset = p_infoset;
	p_IMsetinfo->init();
	p_IMsetinfo->autorelease();
	return p_IMsetinfo;
}

bool IMSetInformation::init()
{
	if (CAViewController::init())
	{
		/*添加返回按钮*/
		CABarButtonItem* addCancelBtn = CABarButtonItem::create(UTF8("取消"), NULL, NULL);
		addCancelBtn->setTarget(this, CAControl_selector(IMSetInformation::onaddCancelBtn));
		//完成按钮
		CABarButtonItem* addFinishBtn = CABarButtonItem::create(UTF8("完成"), NULL, NULL);
		addFinishBtn->setTarget(this, CAControl_selector(IMSetInformation::onaddFinishBtn));

		//获取头部信息
		nagivation = findString();
		pNavigationitem = CANavigationBarItem::create(nagivation);
		pNavigationitem->setShowGoBackButton(false);
		pNavigationitem->addLeftButtonItem(addCancelBtn);
		pNavigationitem->addRightButtonItem(addFinishBtn);
		setNavigationBarItem(pNavigationitem);
		//m_pNavigationBarItem->retain();
		return true;
	}
	return false;
}

std::string IMSetInformation::findString()
{
	map<IMinfoset, std::string>::iterator it = list.find(infoset);
	return it->second;
}

void IMSetInformation::viewDidLoad()
{
	winSize = this->getView()->getBounds().size;
	//this->getView()->setColor(ccc4(230, 230, 230, 255));
	loadBaseView();
	switch (infoset){
	case NAMESET:
		{
			initViewOfName();
			break;
		}
	case SEXSET:
		{
			 initViewOfSex();
			 break;
		}
	case SIGNATURESET:
		{
			 initViewOfSignature();
			 break;
		}
	}

}
//界面初始化 
void IMSetInformation::loadBaseView()
{
	m_pLabel = CALabel::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.05, winSize.width*0.9, winSize.height*0.05));
	m_pLabel->setTextAlignment(CATextAlignmentLeft);
	m_pLabel->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
	m_pLabel->setFontSize(_px(20));
	m_pLabel->setColor(CAColor_gray);
	m_pLabel->setTag(500);
	m_pLabel->setFontSize(_px(30));
	this->getView()->addSubview(m_pLabel);

	m_pText = CATextField::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.1, winSize.width, winSize.height*0.08));
	m_pText->setHoriMargins(_px(20));
	m_pText->setDelegate(this);
	m_pText->setTag(501);
	this->getView()->addSubview(m_pText);
}
//设置昵称界面
void IMSetInformation::initViewOfName()
{
	CALabel *plabel = (CALabel*)this->getView()->getSubviewByTag(500);
	plabel->setText(UTF8("昵称"));
}
//设置性别界面
void IMSetInformation::initViewOfSex()
{
	CCRect winRect = this->getView()->getBounds();
	CALabel *plabelsex = (CALabel*)this->getView()->getSubviewByTag(500);
	plabelsex->setText(UTF8("性别"));
	
	m_pText->setVisible(false);
	pbutton1 = CAButton::createWithFrame(CCRect(0, _px(80), winRect.size.width, _px(80)), CAButtonTypeCustom);
	pbutton1->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_clear));
	pbutton1->addTarget(this, CAControl_selector(IMSetInformation::setbutton1Visible), CAControlEventTouchUpInSide);
	this->getView()->addSubview(pbutton1);
	CALabel* plabel1 = CALabel::createWithFrame(CCRect(_px(40), _px(100), _px(40), _px(40)));
	plabel1->setTextAlignment(CATextAlignmentCenter);
	plabel1->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	plabel1->setText(UTF8("男"));
	this->getView()->addSubview(plabel1);
	pimage1 = CAImageView::createWithImage(CAImage::create(RIGHT_ARROW));
	pimage1->setFrame(CCRect(_px(540),_px(100),_px(40),_px(40)));
	pimage1->setVisible(false);
	this->getView()->addSubview(pimage1);

	CAView* _lineView2 = CAView::createWithFrame(CCRect(_px(40), _px(160), winRect.size.width - _px(80), _px(1)), ccc4(200, 200, 200, 255));
	this->getView()->addSubview(_lineView2);

	pbutton2 = CAButton::createWithFrame(CCRect(0, _px(160), winRect.size.width, _px(80)), CAButtonTypeCustom);
	pbutton2->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_clear));
	pbutton2->addTarget(this, CAControl_selector(IMSetInformation::setbutton2Visible), CAControlEventTouchUpInSide);
	this->getView()->addSubview(pbutton2);
	CALabel* plabel2 = CALabel::createWithFrame(CCRect(_px(40), _px(180), _px(40), _px(40)));
	plabel2->setTextAlignment(CATextAlignmentCenter);
	plabel2->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	plabel2->setText(UTF8("女"));
	this->getView()->addSubview(plabel2);
	pimage2 = CAImageView::createWithImage(CAImage::create(RIGHT_ARROW));
	pimage2->setFrame(CCRect(_px(540), _px(180), _px(40), _px(40)));
	pimage2->setVisible(false);
	this->getView()->addSubview(pimage2);

}

void IMSetInformation::setbutton1Visible(CAControl *pTarget, CCPoint point)
{
	if (pimage2->isVisible())
	{
		pimage2->setVisible(false);
	}
	pimage1->setVisible(true);
	m_pText->setText(UTF8("男"));

}
void IMSetInformation::setbutton2Visible(CAControl *pTarget, CCPoint point)
{
	if (pimage1->isVisible())
	{
		pimage1->setVisible(false);
	}
	pimage2->setVisible(true);
	m_pText->setText(UTF8("女"));
}
//设置个性签名界面
void IMSetInformation::initViewOfSignature()
{
	CALabel *plabelsignature = (CALabel*)this->getView()->getSubviewByTag(500);
	plabelsignature->setText(UTF8("填写个性签名(24字)"));
}


void IMSetInformation::viewDidUnload()
{

}

void IMSetInformation::viewDidAppear()
{
	//this->getNavigationController()->setNavigationBarItem(m_pNavigationBarItem);
}

void IMSetInformation::onaddFinishBtn(CAControl *pTarget, CCPoint point)
{
	//函数处理，根据条件选择处理昵称，性别或者签名
	std::string name_temp = m_pText->getText();
	if (infoset == NAMESET)
	{
		CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_NAME, (CAObject*)name_temp.c_str());
		this->getNavigationController()->popViewControllerAnimated(true);
	}
	else if (infoset == SEXSET)
	{
		CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_SEX, (CAObject*)name_temp.c_str());
		this->getNavigationController()->popViewControllerAnimated(true);
	}
	else if (infoset == SIGNATURESET)
	{
		CANotificationCenter::sharedNotificationCenter()->postNotification(KNOTIFICATION_SIGNATURE, (CAObject*)name_temp.c_str());
		this->getNavigationController()->popViewControllerAnimated(true);
	}
	
}

void IMSetInformation::onaddCancelBtn(CAControl *pTarget, CCPoint point)
{
	RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(true);
}

#pragma mark TextFieldDelegate

bool IMSetInformation::onTextFieldAttachWithIME(CATextField * sender)
{
	CC_UNUSED_PARAM(sender);

	return false;
}

bool IMSetInformation::onTextFieldDetachWithIME(CATextField * sender)
{
	CC_UNUSED_PARAM(sender);

	return false;
}

bool IMSetInformation::onTextFieldInsertText(CATextField * sender, const char * text, int nLen)
{
	CC_UNUSED_PARAM(sender);
	CC_UNUSED_PARAM(text);
	CC_UNUSED_PARAM(nLen);

	return false;
}

bool IMSetInformation::onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen)
{
	CC_UNUSED_PARAM(sender);
	CC_UNUSED_PARAM(delText);
	CC_UNUSED_PARAM(nLen);
	return false;
}