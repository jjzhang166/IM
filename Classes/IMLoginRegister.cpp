//
//  IMLoginRegister.cpp
//  IM
//
// 
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#include "IMLoginRegister.h"
#include "IMDATA.h"
#include "RootWindow.h"
#include "HXSDKController.h"
#include "data/TableLanguage.h"
#include "table/TableLanguagesfontnewHeader.h"

IMLoginRegister::IMLoginRegister()
:m_pNavigationBarItem(NULL)
, m_pButtonCancl(NULL)
, m_pAccount(NULL)
, m_pAccountRegist(NULL)
, m_pPassword(NULL)
, m_pPasswordAgain(NULL)
, m_pLoginButton(NULL)
, m_pRegisterButton(NULL)
, m_pLayoutView(NULL)
, m_pMissPassword(NULL)
, m_pButtonSwitch(NULL)
{

}

IMLoginRegister::~IMLoginRegister()
{
	CANotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

IMLoginRegister* IMLoginRegister::create(UserAction action)
{
    IMLoginRegister *pUser = new IMLoginRegister();
    pUser->init(action);
    pUser->autorelease();
    return pUser;
}

bool IMLoginRegister::init(UserAction action)
{
	if (CAViewController::init())
	{
		m_pAction = action;
		//∑µªÿ∞¥≈•
        m_pButtonCancl = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_17).c_str(), NULL, NULL);
		m_pButtonCancl->setTarget(this, CAControl_selector(IMLoginRegister::onButtonCancel));
        if(	IM_USERLOGIN == action)
        {
                    m_pNavigationBarItem = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_05).c_str());
        }
        else if(IM_USERREGISTER == action)
        {
                   m_pNavigationBarItem = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_03).c_str());
        }

		m_pNavigationBarItem->setShowGoBackButton(false);
		m_pNavigationBarItem->addLeftButtonItem(m_pButtonCancl);
		setNavigationBarItem(m_pNavigationBarItem);
		return true;
	}
	return false;

}

void IMLoginRegister::viewDidLoad()
{

	//≥ı ºªØœ‡πÿΩÁ√Ê
	loadView();
	//”√ªßµ«¬º
	if (m_pAction == IM_USERLOGIN)
	{
		m_pLayoutView->addSubview(m_pAccount);
		m_pLayoutView->addSubview(m_pPassword);
		m_pLayoutView->addSubview(m_pLoginButton);
		m_pLoginButton->addTarget(this, CAControl_selector(IMLoginRegister::onButtonLogin), CAControlEventTouchUpSide);
		m_pLayoutView->addSubview(m_pMissPassword);
		m_pMissPassword->addTarget(this, CAControl_selector(IMLoginRegister::onButtonMissPassword), CAControlEventTouchUpInSide);
		m_pLayoutView->addSubview(m_pButtonSwitch);
		m_pButtonSwitch->addTarget(this, CAControl_selector(IMLoginRegister::onButtonSwitchToRegister), CAControlEventTouchUpInSide);
	}
	//”√ªß◊¢≤·
	else if (m_pAction == IM_USERREGISTER)
	{
		m_pLayoutView->addSubview(m_pAccountRegist);
		m_pLayoutView->addSubview(m_pPassword);
		m_pLayoutView->addSubview(m_pPasswordAgain);
		m_pLayoutView->addSubview(m_pRegisterButton);
		m_pRegisterButton->addTarget(this, CAControl_selector(IMLoginRegister::onButtonRegister), CAControlEventTouchUpInSide);
		m_pLayoutView->addSubview(m_pButtonSwitchTo);
		m_pButtonSwitchTo->addTarget(this, CAControl_selector(IMLoginRegister::onButtonSwitchToLogin), CAControlEventTouchUpInSide);
	}
	this->getView()->addSubview(m_pLayoutView);
}


void IMLoginRegister::loadView()
{
	CCRect winRect = this->getView()->getBounds();
	m_pLayoutView = CAScrollView::createWithFrame(CCRect(0, 0, winRect.size.width, winRect.size.height));
	m_pLayoutView->setBounceHorizontal(false);
	m_pLayoutView->setTouchMovedListenHorizontal(false);
	m_pLayoutView->setShowsHorizontalScrollIndicator(false);
	//’À∫≈
	CCRect accr = CCRect(_px(30), _px(30), winRect.size.width - _px(60), _px(82));
	m_pAccount = CATextField::createWithFrame(accr);
	m_pAccount->setHoriMargins(_px(20));
	m_pAccount->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_01).c_str());
	m_pAccount->setDelegate(this);

	//◊¢≤·’À∫≈

	m_pAccountRegist = CATextField::createWithFrame(accr);
	m_pAccountRegist->setHoriMargins(_px(20));
	m_pAccountRegist->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_06).c_str());
	m_pAccountRegist->setDelegate(this);

	//”√ªß√‹¬Î
	CCRect pwdr = CCRect(_px(30), accr.origin.y + accr.size.height + _px(30), winRect.size.width - _px(60), _px(82));
	m_pPassword = CATextField::createWithFrame(pwdr);
	m_pPassword->setHoriMargins(_px(20));
	m_pPassword->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_02).c_str());
	m_pPassword->setInputType(KEY_BOARD_INPUT_PASSWORD);
	m_pPassword->setDelegate(this);

	//‘Ÿ¥Œ ‰»Î√‹¬Î
	CCRect pwdragain = CCRect(_px(30), pwdr.origin.y + pwdr.size.height + _px(30), winRect.size.width - _px(60), _px(82));
	m_pPasswordAgain = CATextField::createWithFrame(pwdragain);
	m_pPasswordAgain->setHoriMargins(_px(20));
	m_pPasswordAgain->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_08).c_str());
	m_pPasswordAgain->setInputType(KEY_BOARD_INPUT_PASSWORD);
	m_pPasswordAgain->setDelegate(this);

	//”√ªßµ«¬º∞¥≈•
	CCRect login = CCRect(_px(30), pwdr.origin.y + pwdr.size.height + _px(30), winRect.size.width - _px(60), _px(82));
	m_pLoginButton = CAButton::createWithFrame(login, CAButtonTypeRoundedRect);
	m_pLoginButton->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_green));
	m_pLoginButton->setTitleForState(CAControlStateAll, TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LOGIN).c_str());
	m_pLoginButton->setTitleColorForState(CAControlStateAll, CAColor_white);
	m_pLoginButton->setTag(111);

	//”√ªß◊¢≤·∞¥≈•
	CCRect regist = CCRect(_px(30), pwdragain.origin.y + pwdragain.size.height + _px(30), winRect.size.width - _px(60), _px(82));
	m_pRegisterButton = CAButton::createWithFrame(regist, CAButtonTypeRoundedRect);
	m_pRegisterButton->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_green));
	m_pRegisterButton->setTitleForState(CAControlStateAll, TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_68).c_str());
	m_pRegisterButton->setTitleColorForState(CAControlStateAll, CAColor_white);

	//Õ¸º«√‹¬Î
	CCRect missPassword = CCRect(winRect.size.width - _px(150), login.origin.y + login.size.height + _px(30), _px(120), _px(20));
	m_pMissPassword = CAButton::createWithFrame(missPassword, CAButtonTypeRoundedRect);
	m_pMissPassword->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_clear));
	m_pMissPassword->setTitleForState(CAControlStateAll, TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_04).c_str());
	m_pMissPassword->setTitleColorForState(CAControlStateAll, CAColor_gray);

	//«–ªªµΩ◊¢≤·
	m_pButtonSwitch = CAButton::createWithCenter(CCRect(winRect.size.width*0.5, winRect.size.height*0.9, winRect.size.width*0.4, winRect.size.height*0.1), CAButtonTypeRoundedRect);
	CAScale9ImageView *switchBg = CAScale9ImageView::createWithImage(CAImage::create(USER_STATUS_BUTTON));
	m_pButtonSwitch->setBackGroundViewForState(CAControlStateAll, switchBg);
	m_pButtonSwitch->setTitleForState(CAControlStateAll, TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_03).c_str());
	m_pButtonSwitch->setTitleColorForState(CAControlStateAll, CAColor_gray);
	m_pButtonSwitch->setTag(101);
	//«–ªªµΩµ«¬º
	m_pButtonSwitchTo = CAButton::createWithCenter(CCRect(winRect.size.width*0.5, winRect.size.height*0.9, winRect.size.width*0.4, winRect.size.height*0.1), CAButtonTypeRoundedRect);
	CAScale9ImageView *switchBgTo = CAScale9ImageView::createWithImage(CAImage::create(USER_STATUS_BUTTON));
	m_pButtonSwitchTo->setBackGroundViewForState(CAControlStateAll, switchBgTo);
	m_pButtonSwitchTo->setTitleForState(CAControlStateAll, TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_09).c_str());
	m_pButtonSwitchTo->setTitleColorForState(CAControlStateAll, CAColor_gray);

}

void IMLoginRegister::viewDidUnload()
{

}

void IMLoginRegister::viewDidAppear()
{
	
}
//∑µªÿ
void IMLoginRegister::onButtonCancel(CAControl *pTarget, CCPoint point)
{
    RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(true);
}
//µ«¬º
void IMLoginRegister::onButtonLogin(CAControl *pTarget, CCPoint point)
{
    std::string accountName = m_pAccount->getText();
    std::string accountPassword = m_pPassword->getText();
    
//    if(accountName.empty())
//    {
//        CCLog("account name is empty");
//        return;
//    }
//    if(accountPassword.empty())
//    {
//        CCLog("account password is empty");
//        return;
//    }
	//添加观察者模式
	CANotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(IMLoginRegister::onLoginSuccess), KNOTIFICATION_LOGIN, NULL);
    //HXSDKController::getInstance()->Login(accountName.c_str(),accountPassword.c_str());
    
    HXSDKController::getInstance()->Login("qiaoxin5","123456");
}
// 登录成功回调函数
void IMLoginRegister::onLoginSuccess(CAObject* obj)
{
	bool isloginsuccess = (bool)obj;
	if (isloginsuccess){

		this->getNavigationController()->popToRootViewControllerAnimated(true);
		//this->getNavigationController()->popViewControllerAnimated(true);
	}
	else{
		CCLog("login fail");
	}
	
	
}
//◊¢≤·
void IMLoginRegister::onButtonRegister(CAControl *pTarget, CCPoint point)
{
	
    std::string accountName = m_pAccountRegist->getText();
    std::string accountPassword = m_pPassword->getText();
    std::string accountasswordAgain = m_pPasswordAgain->getText();
    
    if(accountName.empty())
    {
        CCLog("account name is empty");
        return;
    }
    if(accountPassword.empty())
    {
        CCLog("account password is empty");
        return;
    }
    if(accountasswordAgain.empty())
    {
        CCLog("account passwordAgain is empty");
        return;
    }
    if(accountasswordAgain.compare(accountPassword))
    {
        CCLog("account passwordAgain != Password");
        return;
    }
	//添加注册观察者模式
	CANotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(IMLoginRegister::onRegisterSuccess), KNOTIFICATION_REGISTER, NULL);
    HXSDKController::getInstance()->RegisterAccount(accountName.c_str(),accountasswordAgain.c_str());
	
	
}
//注册成功跳转函数
void IMLoginRegister::onRegisterSuccess(CAObject* obj)
{
	bool isregistersuccess = (bool)obj;
	if (isregistersuccess){
		//注册成功，跳转到主界面
		this->getNavigationController()->popToRootViewControllerAnimated(true);
	}
	else{
		
		CCLog("register success");
	}
}
//Õ¸º«√‹¬Î
void IMLoginRegister::onButtonMissPassword(CAControl *pTarget, CCPoint point)
{

}
//µ«¬º∫Õ◊¢≤·÷Æº‰Ã¯◊™
void IMLoginRegister::onButtonSwitchToRegister(CAControl *pTarget, CCPoint point)
{
	IMLoginRegister *pUser = new IMLoginRegister();
	pUser->init(IM_USERREGISTER);
	this->getNavigationController()->pushViewController(pUser, true);
	pUser->autorelease();
}
void IMLoginRegister::onButtonSwitchToLogin(CAControl *pTarget, CCPoint point)
{
	IMLoginRegister *pUser = new IMLoginRegister();
	pUser->init(IM_USERLOGIN);
	this->getNavigationController()->pushViewController(pUser,true);
	pUser->autorelease();
}


#pragma mark TextFieldDelegate

bool IMLoginRegister::onTextFieldAttachWithIME(CATextField * sender)
{
	CC_UNUSED_PARAM(sender);

	return false;
}

bool IMLoginRegister::onTextFieldDetachWithIME(CATextField * sender)
{
	CC_UNUSED_PARAM(sender);

	return false;
}

bool IMLoginRegister::onTextFieldInsertText(CATextField * sender, const char * text, int nLen)
{
	CC_UNUSED_PARAM(sender);
	CC_UNUSED_PARAM(text);
	CC_UNUSED_PARAM(nLen);

	return false;
}

bool IMLoginRegister::onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen)
{
	CC_UNUSED_PARAM(sender);
	CC_UNUSED_PARAM(delText);
	CC_UNUSED_PARAM(nLen);

	return false;
}