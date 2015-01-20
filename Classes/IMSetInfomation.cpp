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
IMSetInformation::IMSetInformation() :m_pLabel(NULL)
, m_pText(NULL)
, pbutton1(NULL)
, pbutton2(NULL)
, pchoose(NULL)
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
	IMSetInformation *p_IMsetinfo = new IMSetInformation();
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
	CALabel *plabelsex = (CALabel*)this->getView()->getSubviewByTag(500);
	plabelsex->setText(UTF8("性别"));

	m_pText->setVisible(false);
	pbutton1 = CAButton::createWithCenter(CCRect(winSize.width*0.5,winSize.height*0.2,winSize.width,winSize.height*0.099),CAButtonTypeSquareRect);
	pbutton1->setTitleColorForState(CAControlStateAll, CAColor_black);
	pbutton1->setTitleForState(CAControlStateAll, UTF8("男"));
	pbutton1->addTarget(this, CAControl_selector(IMSetInformation::setbutton1Visible), CAControlTouchUpInSide);
	this->getView()->addSubview(pbutton1);
	
	pbutton2 = CAButton::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.3, winSize.width, winSize.height*0.099), CAButtonTypeSquareRect);
	pbutton2->setTitleColorForState(CAControlStateAll, CAColor_black);
	pbutton2->setTitleForState(CAControlStateAll, UTF8("女"));
	pbutton2->addTarget(this, CAControl_selector(IMSetInformation::setbutton2Visible), CAControlTouchUpInSide);
	this->getView()->addSubview(pbutton2);
}

void IMSetInformation::setbutton1Visible(CAControl *pTarget, CCPoint point)
{
	//pbutton1->setBackGroundViewForState(CAScale9ImageView::createWithImage())
}
void IMSetInformation::setbutton2Visible(CAControl *pTarget, CCPoint point)
{

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