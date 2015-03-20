//
//  IMMyInfo.cpp
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#include "IMMyInfo.h"
#include "IMDATA.h"
#include "AddHeadForgrand.h"
#include "IMSetInformation.h"
#include "RootWindow.h"
#include "IMUserManager.h"
IMMyInfo::IMMyInfo() :cell(NULL), m_pTableView(NULL)
, m_pUserHead(NULL)
, m_pUserName(NULL)
, m_pUserSex(NULL)
, m_pUserSignature(NULL)
, m_pPicChoserLayer(NULL)
, m_pStart(NULL)
, pbutton(NULL)
{

}
IMMyInfo::~IMMyInfo()
{
	CC_SAFE_RELEASE(pNagivationitem);
	CANotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

bool IMMyInfo::init()
{
	if (CAViewController::init())
	{
		pNagivationitem = CANavigationBarItem::create(UTF8("个人信息"));
		setNavigationBarItem(pNagivationitem);
		m_pNavigationBarItem->retain();
		return true;
	}
}
//类接口
IMMyInfo* IMMyInfo::create()
{
	IMMyInfo *pInfo = new IMMyInfo();
	pInfo->init();
	pInfo->autorelease();
	return pInfo;
}
void IMMyInfo::viewDidLoad()
{
	//初始化tableview
	winSize = this->getView()->getBounds().size;
	m_pTableView = CATableView::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.5, winSize.width, winSize.height));
	m_pTableView->setTableViewDataSource(this);
	m_pTableView->setTableViewDelegate(this);
	m_pTableView->setAllowsSelection(true);
	this->getView()->addSubview(m_pTableView);
	/*开始使用button按钮*/
	m_pStart = CAButton::createWithCenter(CCRect(winSize.width*0.5, winSize.height*0.94, winSize.width*0.8, winSize.height*0.08), CAButtonTypeRoundedRect);
	m_pStart->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_green));
	m_pStart->setTitleForState(CAControlStateAll, UTF8("开始使用"));
	m_pStart->setTitleColorForState(CAControlStateAll, CAColor_white);
	m_pStart->addTarget(this, CAControl_selector(IMMyInfo::onStartBtnClick), CAControlTouchUpInSide);
	this->getView()->addSubview(m_pStart);
	addPicChoserLayer();
}

void IMMyInfo::viewDidUnload()
{

}

void IMMyInfo::viewDidAppear()
{
	
}

void IMMyInfo::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	//cell点击之后进入事件
	if (section == 0)
	{
		if (row == 0)
		{
			onHeadClick();
		}
		else
		{
			IMSetInformation *pimsetinfoname = IMSetInformation::create(NAMESET);
			RootWindow::getInstance()->getNavigationController()->pushViewController(pimsetinfoname, true);
		}
	}
	else 
	{
		if (row == 0){
			IMSetInformation *pimsetinfosex= IMSetInformation::create(SEXSET);
			RootWindow::getInstance()->getNavigationController()->pushViewController(pimsetinfosex, true);
		}
		else{
			IMSetInformation *pimsetinfosig = IMSetInformation::create(SIGNATURESET);
			RootWindow::getInstance()->getNavigationController()->pushViewController(pimsetinfosig, true);
		}
		
	}	
}

void IMMyInfo::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{

}

CATableViewCell* IMMyInfo::tableCellAtIndex(CATableView* table, const CCSize& cellsize, unsigned int section, unsigned int row)
{
	/*cell页面的初始化*/
	cell = table->dequeueReusableCellWithIdentifier("CrossApp");
	switch (section)
	{
	case 0:
	{
			  switch (row)
			  {
			  case 0:
				  {
						cell = initHeadImage(cellsize);
						return cell;
						break;
				  }
			  case 1:
				 {
						cell = initName(cellsize);
						return cell;
						break;
				}
			  }
			 
	}
	case 1:
	{   
			  switch (row)
			  {
			  case 0:
			  {
						cell = initSex(cellsize);
						return cell;
						break;
			  }
			  case 1:
			  {
						cell = initSignature(cellsize);
						return cell;
						break;
			  }
			  }
	}
	default:
		break;
	}
}

CATableViewCell* IMMyInfo::initHeadImage(const CCSize& cellsize)
{
	if (cell == NULL)
	{

		cell = CATableViewCell::create("CrossApp");
		/*添加头像view*/
		m_pUserHead = CAImageView::createWithCenter(CCRect(cellsize.width*0.5, cellsize.height*0.5, _px(100), _px(100)));
		m_pUserHead->setTag(400);
		//cell->addSubview(m_pUserHead);
		AddHeadForgrand::getInstance()->addHeadForgrand(m_pUserHead);
		m_pUserHead->setImage(CAImage::create("head.png"));
		addRightArrow(cell, cellsize);
		pbutton = CAButton::createWithFrame(m_pUserHead->getFrame(),CAButtonTypeCustom);
		pbutton->setBackGroundViewForState(CAControlStateAll, m_pUserHead);
		cell->addSubview(pbutton);
	}
	return cell;
}

CATableViewCell* IMMyInfo::initName(const CCSize& cellsize)
{
	
	if (cell == NULL)
	{
		cell = CATableViewCell::create("CrossApp");
		CALabel *nickname = CALabel::createWithFrame(CCRect(15, 0, cellsize.width*0.2, cellsize.height));
		nickname->setColor(CAColor_gray);
		nickname->setTextAlignment(CATextAlignmentLeft);
		nickname->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		nickname->setText(UTF8("昵称"));
		nickname->setFontSize(_px(30));
		cell->addSubview(nickname);

		m_pUserName = CALabel::createWithFrame(CCRect(cellsize.width*0.25, 0, cellsize.width*0.6, cellsize.height));
		m_pUserName->setColor(CAColor_black);
		m_pUserName->setTextAlignment(CATextAlignmentLeft);
		m_pUserName->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		m_pUserName->setFontSize(_px(30));
		m_pUserName->setTag(401);
		cell->addSubview(m_pUserName);
		addRightArrow(cell, cellsize);
		CANotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(IMMyInfo::getUserName), KNOTIFICATION_NAME, NULL);
	}
	return cell;
}

void IMMyInfo::getUserName(CAObject* obj)
{
	std::string temp_name = (char*)obj;
	m_pUserName->setText(temp_name);
}
CATableViewCell* IMMyInfo::initSex(const CCSize& cellsize)
{
	if (cell == NULL)
	{
		cell = CATableViewCell::create("CrossApp");
		CALabel *sex = CALabel::createWithFrame(CCRect(15, 0, cellsize.width*0.2, cellsize.height));
		sex->setColor(CAColor_gray);
		sex->setTextAlignment(CATextAlignmentLeft);
		sex->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		sex->setText(UTF8("性别"));
		sex->setFontSize(_px(30));
		cell->addSubview(sex);

		m_pUserSex = CALabel::createWithFrame(CCRect(cellsize.width*0.25, 0, cellsize.width*0.6, cellsize.height));
		m_pUserSex->setColor(CAColor_black);
		m_pUserSex->setTextAlignment(CATextAlignmentLeft);
		m_pUserSex->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		m_pUserSex->setFontSize(_px(30));
		m_pUserSex->setTag(402);
		cell->addSubview(m_pUserSex);
		addRightArrow(cell, cellsize);
		CANotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(IMMyInfo::getUserSex), KNOTIFICATION_SEX, NULL);
	}
	return cell;
}

void IMMyInfo::getUserSex(CAObject* obj)
{
	std::string temp_sex = (char*)obj;
	m_pUserSex->setText(temp_sex);
}
CATableViewCell* IMMyInfo::initSignature(const CCSize& cellsize)
{
	if (cell == NULL)
	{
		cell = CATableViewCell::create("CrossApp");
		CALabel *qianming = CALabel::createWithFrame(CCRect(15, 0, cellsize.width*0.2, cellsize.height));
		qianming->setColor(CAColor_gray);
		qianming->setTextAlignment(CATextAlignmentLeft);
		qianming->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		qianming->setText(UTF8("个性签名"));
		qianming->setFontSize(_px(30));
		cell->addSubview(qianming);

		m_pUserSignature = CALabel::createWithFrame(CCRect(cellsize.width*0.25, 0, cellsize.width*0.6, cellsize.height));
		m_pUserSignature->setColor(CAColor_black);
		m_pUserSignature->setTextAlignment(CATextAlignmentLeft);
		m_pUserSignature->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		m_pUserSignature->setFontSize(_px(30));
		m_pUserSignature->setTag(403);
		cell->addSubview(m_pUserSignature);
		addRightArrow(cell, cellsize);
		CANotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(IMMyInfo::getUserSignature), KNOTIFICATION_SIGNATURE, NULL);
	}
	return cell;
}
void IMMyInfo::getUserSignature(CAObject* obj)
{
	std::string temp_signature = (char*)obj;
	m_pUserSignature->setText(temp_signature);
}
//向右箭头处理
void IMMyInfo::addRightArrow(CATableViewCell *m_pCell, const CCSize& pcellsize)
{
	CAImageView *pright = CAImageView::createWithCenter(CCRect(pcellsize.width*0.92, pcellsize.height*0.5, _px(60), _px(60)));
	pright->setImage(CAImage::create(RIGHT_ARROW));
	m_pCell->addSubview(pright);
}


//添加照片选项
void IMMyInfo::addPicChoserLayer()
{
	
	m_pPicChoserLayer = CAView::createWithFrame(this->getView()->getFrame(), ccc4(100, 100, 100, 100));
	m_pPicChoserLayer->setVisible(false);
	this->getView()->addSubview(m_pPicChoserLayer);

	CCSize hViewSize = this->getView()->getFrame().size;
	CCRect cancelR = CCRect(_px(10), hViewSize.height - _px(90), hViewSize.width - _px(20), _px(85));
	CAButton *cancelBtn = CAButton::createWithFrame(cancelR, CAButtonTypeRoundedRect);
	cancelBtn->setTitleForState(CAControlStateAll, UTF8("取消"));
	cancelBtn->addTarget(this, CAControl_selector(IMMyInfo::onCancelBtnClick), CAControlEventTouchUpInSide);
	m_pPicChoserLayer->addSubview(cancelBtn);

	CCRect albumR = CCRect(_px(10), cancelR.origin.y - _px(90), hViewSize.width - _px(20), _px(85));
	CAButton *albumBtn = CAButton::createWithFrame(albumR, CAButtonTypeRoundedRect);
	albumBtn->setTitleForState(CAControlStateAll, UTF8("从相册选择"));
	albumBtn->addTarget(this, CAControl_selector(IMMyInfo::onAlbumBtnClick), CAControlEventTouchUpInSide);
	m_pPicChoserLayer->addSubview(albumBtn);

	CCRect cameraR = CCRect(_px(10), albumR.origin.y - _px(90), hViewSize.width - _px(20), _px(85));
	CAButton *cameraBtn = CAButton::createWithFrame(cameraR, CAButtonTypeRoundedRect);
	cameraBtn->setTitleForState(CAControlStateAll, UTF8("拍照"));
	cameraBtn->addTarget(this, CAControl_selector(IMMyInfo::onCameraBtnClick), CAControlEventTouchUpInSide);
	m_pPicChoserLayer->addSubview(cameraBtn);
	
}


//点击头像处理函数
void IMMyInfo::onHeadClick()
{
	if (!m_pPicChoserLayer->isVisible()){
		m_pPicChoserLayer->setVisible(true);
	}
}

//点击照相处理函数
void IMMyInfo::onCameraBtnClick(CAControl *pTarget, CCPoint point)
{
	CADevice::openCamera(this);
	m_pPicChoserLayer->setVisible(false);
}
//点击相册处理函数
void IMMyInfo::onAlbumBtnClick(CAControl *pTarget, CCPoint point)
{
	CADevice::openAlbum(this);
	m_pPicChoserLayer->setVisible(false);
}
//点击取消处理函数
void IMMyInfo::onCancelBtnClick(CAControl *pTarget, CCPoint point)
{
	m_pPicChoserLayer->setVisible(false);
}
//头像获取
void IMMyInfo::getSelectedImage(CAImage* image)
{
	CAImageView *bac = CAImageView::createWithFrame(m_pUserHead->getFrame());
	bac->setImage(image);
	pbutton->setBackGroundViewForState(CAControlStateNormal, bac);
	//CAImage变成数据
	CADipSize size = bac->getFrame().size;
	CARenderImage *renderImage = CARenderImage::create(size.width, size.height);
	renderImage->beginWithClear(0, 0, 0, 255);
	bac->visit();
	renderImage->end();
	CCImage *ccImage = renderImage->newCCImage();
	photoname = CCFileUtils::sharedFileUtils()->getWritablePath() + "head.png";
	ccImage->saveToFile(photoname.c_str());
}

void IMMyInfo::onStartBtnClick(CAControl *pTarget, CCPoint point)
{
	
	//开始使用按钮点击，获取用户填写的信息上传到服务器
	onStartBtnClickBack();

}
void IMMyInfo::onStartBtnClickBack()
{
	
	
	
	//上传数据到服务器成功后保存数据到本地
	User user;
	user.init("100", m_pUserName->getText(), m_pUserSex->getText(), photoname, m_pUserSignature->getText(), online);
	IMUserManager::Instance()->userLogin(user);
	this->getNavigationController()->popViewControllerAnimated(true);
}


/*设置每个section含有的cell个数*/
unsigned int IMMyInfo::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	return 2;
}

/*设置含有几个section*/
unsigned int IMMyInfo::numberOfSections(CATableView *table)
{
	return 2;
}

unsigned int IMMyInfo::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{	/*section的大小设置*/
	if (section == 0 && row == 0)
	{
		return winSize.height*0.2;
	}
	else
	{
		return winSize.height*0.1;
	}
	
}

unsigned IMMyInfo::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
{
	return _px(20);
}
/*在section之间添加一个view，就是UI中section之间的灰色地带*/
CAView* IMMyInfo::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
	CAView* view = CAView::createWithColor(ccc4(230, 230, 230, 255));
	return view;
}