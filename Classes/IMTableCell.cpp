//
//  IMTableCell.cpp
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "IMTableCell.h"
#include "IMDATA.h"
#include "AddHeadForgrand.h"

IMTableCell::IMTableCell() :
m_pGroup(NULL)
,m_pHead(NULL)
,m_pName(NULL)
,m_pContent(NULL)
,m_pcelltype(Friend)
{
	
}

IMTableCell::~IMTableCell()
{

}

IMTableCell* IMTableCell::create(IMCellType celltype, CCSize size)
{
	IMTableCell* imTableCell = new IMTableCell();
	imTableCell->m_pcelltype = celltype;
	if (imTableCell&&imTableCell->initWithReuseIdentifier("Crossapp"))
	{
        imTableCell->setFrame(CCRectMake(0, 0, size.width, size.height));
        imTableCell->initCell();
		imTableCell->autorelease();
		return imTableCell;
	}
	CC_SAFE_DELETE(imTableCell);
	return NULL;

}

void IMTableCell::initCell()
{
	switch (m_pcelltype){
	case Group:
        {
            initCellWithGroup();
            break;
        }
	case Friend:
		{
            initCellWithFriend();
            break;
        }
	case Strange:
		{
            initCellWithStrange();
            break;
        }
    case SearchResult:
        {
            initCellWithSearchResult();
            break;
        }
    case UNKnow:
        {
            break;
        }
		default:
			break;
	}
}


void IMTableCell::baseView()
{
	CADipSize cellsize = this->getFrame().size;
	m_pHead = CAImageView::createWithCenter(CCRect(60, cellsize.height*0.5, 100, cellsize.height));
	m_pHead->setTag(200);
	AddHeadForgrand::getInstance()->addHeadForgrand(m_pHead);
	
	m_pGroup = CAImageView::createWithCenter(CCRect(165, cellsize.height*0.3, 80, cellsize.height*0.3));
	m_pGroup->setTag(201);
	m_pGroup->setImage(CAImage::create(GROUP));

	m_pName = CALabel::createWithFrame(CCRect(130, cellsize.height*0.1, cellsize.width*0.3, cellsize.height*0.4));
	m_pName->setColor(CAColor_black);
	m_pName->setTextAlignment(CATextAlignmentLeft);
	m_pName->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	m_pName->setFontSize(20 * CROSSAPP_ADPTATION_RATIO);
	m_pName->setTag(202);

	m_pContent = CALabel::createWithFrame(CCRect(125, cellsize.height*0.6, cellsize.width*0.76, cellsize.height*0.4));
	m_pContent->setColor(CAColor_gray);
	m_pContent->setTextAlignment(CATextAlignmentLeft);
	m_pContent->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
	m_pContent->setFontSize(18 * CROSSAPP_ADPTATION_RATIO);
	m_pContent->setTag(203);
    
    m_pResult = CALabel::createWithFrame(CCRect(130,cellsize.height *0.25,cellsize.width*0.76,cellsize.height*0.4));
    m_pResult->setColor(ccc4(22, 22, 22, 255));
    m_pResult->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    m_pResult->setFontSize(_px(38));
    m_pResult->setTag(204);
}

void IMTableCell::initCellWithGroup()
{
	CADipSize cellsize = this->getFrame().size;
	baseView();
	m_pName->setFrame(CCRect(230, cellsize.height*0.1, cellsize.width*0.3, cellsize.height*0.4));
	this->addSubview(m_pHead);
	this->addSubview(m_pGroup);
	this->addSubview(m_pName);
	this->addSubview(m_pContent);
}

void IMTableCell::initCellWithFriend()
{
	baseView();
	this->addSubview(m_pHead);
	this->addSubview(m_pName);
	this->addSubview(m_pContent);
}

void IMTableCell::initCellWithStrange()
{
	baseView();
	this->addSubview(m_pHead);
	this->addSubview(m_pName);
	this->addSubview(m_pContent);
}

void IMTableCell::initCellWithSearchResult()
{
    baseView();
    this->addSubview(m_pHead);
    this->addSubview(m_pResult);
}

void IMTableCell::setCellInfo(CAImage* headIcon, const std::string name, const std::string introduce)
{
    m_pHead->setImage(headIcon);
    m_pName->setText(name);
    m_pContent->setText(introduce);
}

void IMTableCell:: setCellInfo(CAImage* headIcon,const std::string result)
{
    m_pHead->setImage(headIcon);
    m_pResult->setText(result);
}