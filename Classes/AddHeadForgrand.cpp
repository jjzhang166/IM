//
//  AddHeadForgrand.cpp
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "AddHeadForgrand.h"
static AddHeadForgrand *m_pAddHeadForgrand = NULL;
AddHeadForgrand::AddHeadForgrand()
{

}

AddHeadForgrand::~AddHeadForgrand()
{

}

AddHeadForgrand* AddHeadForgrand::getInstance()
{
	if (m_pAddHeadForgrand == NULL)
	{
		m_pAddHeadForgrand = new AddHeadForgrand();
		m_pAddHeadForgrand->autorelease();
		return m_pAddHeadForgrand;
	}
}

void AddHeadForgrand::addHeadForgrand(CAImageView* pImageView)
{
	CCRect winRect = pImageView->getFrame();
	CAImageView *headTopView = CAImageView::createWithCenter(CCRect(winRect.size.width*0.5, winRect.size.height*0.5, _px(120), _px(120)));
	headTopView->setImage(CAImage::create(HEADBEFORE));
	pImageView->addSubview(headTopView);
}

