#include "IMTableCell.h"
#include "IMDATA.h"

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

IMTableCell* IMTableCell::create(IMCellType celltype)
{
	IMTableCell* imTableCell = new IMTableCell();
	imTableCell->m_pcelltype = celltype;
	if (imTableCell&&imTableCell->initWithReuseIdentifier("Crossapp"))
	{
		
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
		{initCellWithGroup();
		break; }
	case Friend:
		{initCellWithFriend();
		break; }
	case Strange:
		{initCellWithStrange();
		break; }
		default:
			break;
	}
}

void IMTableCell::addHeadForegrand()
{
	CAImageView *headTopView = CAImageView::create();
	headTopView->setFrame(CCRect(0, 0, _px(144),_px(144)));
	headTopView->setImage(CAImage::create(HEADBEFORE));
	m_pHead->addSubview(headTopView);

}

void IMTableCell::baseView()
{
	CADipSize cellsize = this->getFrame().size;
	m_pHead = CAImageView::createWithCenter(CCRect(cellsize.width*0.1, cellsize.height*0.5, cellsize.width*0.2, cellsize.height));
	m_pHead->setTag(200);
	addHeadForegrand();
	

	m_pGroup = CAImageView::createWithCenter(CCRect(cellsize.width*0.25, cellsize.height*0.3, cellsize.width*0.06, cellsize.height*0.3));
	m_pGroup->setTag(201);
	m_pGroup->setImage(CAImage::create(GROUP));


	m_pName = CALabel::createWithCenter(CCRect(cellsize.width*0.6, cellsize.height*0.3, cellsize.width*0.76, cellsize.height*0.4));
	m_pName->setColor(CAColor_black);
	m_pName->setTextAlignment(CATextAlignmentLeft);
	m_pName->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	m_pName->setFontSize(20 * CROSSAPP_ADPTATION_RATIO);
	m_pName->setTag(202);

	

	m_pContent = CALabel::createWithCenter(CCRect(cellsize.width*0.6, cellsize.height*0.8, cellsize.width*0.76, cellsize.height*0.4));
	m_pContent->setColor(CAColor_gray);
	m_pContent->setTextAlignment(CATextAlignmentLeft);
	m_pContent->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
	m_pContent->setFontSize(18 * CROSSAPP_ADPTATION_RATIO);
	m_pContent->setTag(203);

	
}

void IMTableCell::initCellWithGroup()
{
	CADipSize cellsize = this->getFrame().size;
	baseView();
	m_pName->setCenter(CCRect(cellsize.width*0.65, cellsize.height*0.3, cellsize.width*0.68, cellsize.height*0.4));
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