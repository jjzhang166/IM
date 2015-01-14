#include "IMLoginRegister.h"
#include "IMDATA.h"
#include "RootWindow.h"
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
	
}

bool IMLoginRegister::init(UserAction action)
{
	if (CAViewController::init())
	{
		m_pAction = action;
		//返回按钮
		m_pButtonCancl = CABarButtonItem::create(IM_CANCEL, CAImage::create(NAVIGATION_BG), CAImage::create(NAVIGATION_BG));
		m_pButtonCancl->setTarget(this, CAControl_selector(IMLoginRegister::onButtonCancel));
		m_pNavigationBarItem = CANavigationBarItem::create(IM_USER_LOGIN);
		m_pNavigationBarItem->setShowGoBackButton(false);
		m_pNavigationBarItem->addLeftButtonItem(m_pButtonCancl);
		setNavigationBarItem(m_pNavigationBarItem);
		return true;
	}
	return false;

}

void IMLoginRegister::viewDidLoad()
{

	//初始化相关界面
	loadView();
	//用户登录
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
	//用户注册
	else if (m_pAction == IM_USERREGISTER)
	{
		m_pLayoutView->addSubview(m_pAccountRegist);
		m_pLayoutView->addSubview(m_pPassword);
		m_pLayoutView->addSubview(m_pPasswordAgain);
		m_pLayoutView->addSubview(m_pRegisterButton);
		m_pLoginButton->addTarget(this, CAControl_selector(IMLoginRegister::onButtonRegister), CAControlEventTouchUpSide);
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
	//账号
	CCRect accr = CCRect(_px(30), _px(30), winRect.size.width - _px(60), _px(82));
	m_pAccount = CATextField::createWithFrame(accr);
	m_pAccount->setHoriMargins(_px(20));
	m_pAccount->setPlaceHolder(UTF8("111111"));
	m_pAccount->setDelegate(this);

	//注册账号

	m_pAccountRegist = CATextField::createWithFrame(accr);
	m_pAccountRegist->setHoriMargins(_px(20));
	m_pAccountRegist->setPlaceHolder(UTF8("22222"));
	m_pAccountRegist->setDelegate(this);

	//用户密码
	CCRect pwdr = CCRect(_px(30), accr.origin.y + accr.size.height + _px(30), winRect.size.width - _px(60), _px(82));
	m_pPassword = CATextField::createWithFrame(pwdr);
	m_pPassword->setHoriMargins(_px(20));
	m_pPassword->setPlaceHolder(UTF8("33333"));
	m_pPassword->setInputType(KEY_BOARD_INPUT_PASSWORD);
	m_pPassword->setDelegate(this);

	//再次输入密码
	CCRect pwdragain = CCRect(_px(30), pwdr.origin.y + pwdr.size.height + _px(30), winRect.size.width - _px(60), _px(82));
	m_pPasswordAgain = CATextField::createWithFrame(pwdragain);
	m_pPasswordAgain->setHoriMargins(_px(20));
	m_pPasswordAgain->setPlaceHolder(UTF8("4444444"));
	m_pPasswordAgain->setInputType(KEY_BOARD_INPUT_PASSWORD);
	m_pPasswordAgain->setDelegate(this);

	//用户登录按钮
	CCRect login = CCRect(_px(30), pwdr.origin.y + pwdr.size.height + _px(30), winRect.size.width - _px(60), _px(82));
	m_pLoginButton = CAButton::createWithFrame(login, CAButtonTypeRoundedRect);
	m_pLoginButton->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_green));
	m_pLoginButton->setTitleForState(CAControlStateAll, UTF8("55555"));
	m_pLoginButton->setTitleColorForState(CAControlStateAll, CAColor_white);

	//用户注册按钮
	CCRect regist = CCRect(_px(30), pwdragain.origin.y + pwdragain.size.height + _px(30), winRect.size.width - _px(60), _px(82));
	m_pRegisterButton = CAButton::createWithFrame(regist, CAButtonTypeRoundedRect);
	m_pRegisterButton->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_green));
	m_pRegisterButton->setTitleForState(CAControlStateAll, UTF8("66666"));
	m_pRegisterButton->setTitleColorForState(CAControlStateAll, CAColor_white);

	//忘记密码
	CCRect missPassword = CCRect(winRect.size.width - _px(150), login.origin.y + login.size.height + _px(30), _px(120), _px(20));
	m_pMissPassword = CAButton::createWithFrame(missPassword, CAButtonTypeRoundedRect);
	m_pMissPassword->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_clear));
	m_pMissPassword->setTitleForState(CAControlStateAll, UTF8("77777"));
	m_pMissPassword->setTitleColorForState(CAControlStateAll, CAColor_gray);

	//切换到注册
	m_pButtonSwitch = CAButton::createWithCenter(CCRect(winRect.size.width*0.5, winRect.size.height*0.9, winRect.size.width*0.4, winRect.size.height*0.1), CAButtonTypeRoundedRect);
	CAScale9ImageView *switchBg = CAScale9ImageView::createWithImage(CAImage::create(USER_STATUS_BUTTON));
	m_pButtonSwitch->setBackGroundViewForState(CAControlStateAll, switchBg);
	m_pButtonSwitch->setTitleForState(CAControlStateAll, UTF8("8888888"));
	m_pButtonSwitch->setTitleColorForState(CAControlStateAll, CAColor_gray);
	m_pButtonSwitch->setTag(101);
	//切换到登录
	m_pButtonSwitchTo = CAButton::createWithCenter(CCRect(winRect.size.width*0.5, winRect.size.height*0.9, winRect.size.width*0.4, winRect.size.height*0.1), CAButtonTypeRoundedRect);
	CAScale9ImageView *switchBgTo = CAScale9ImageView::createWithImage(CAImage::create(USER_STATUS_BUTTON));
	m_pButtonSwitchTo->setBackGroundViewForState(CAControlStateAll, switchBgTo);
	m_pButtonSwitchTo->setTitleForState(CAControlStateAll, UTF8("999999"));
	m_pButtonSwitchTo->setTitleColorForState(CAControlStateAll, CAColor_gray);

}

void IMLoginRegister::viewDidUnload()
{

}

void IMLoginRegister::viewDidAppear()
{
	
}
//返回
void IMLoginRegister::onButtonCancel(CAControl *pTarget, CCPoint point)
{

}
//登录
void IMLoginRegister::onButtonLogin(CAControl *pTarget, CCPoint point)
{

}
//注册
void IMLoginRegister::onButtonRegister(CAControl *pTarget, CCPoint point)
{
	
}
//忘记密码
void IMLoginRegister::onButtonMissPassword(CAControl *pTarget, CCPoint point)
{

}
//登录和注册之间跳转
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