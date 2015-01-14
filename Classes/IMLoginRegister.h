#ifndef __IM_LOGIN_REGISTER_H__
#define __IM_LOGIN_REGISTER_H__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;
//用户登录或者注册事件
typedef enum{
	IM_USERLOGIN,
    IM_USERREGISTER
}UserAction;
class IMLoginRegister :public CAViewController, public CATextFieldDelegate
{
public:
	IMLoginRegister();
	virtual ~IMLoginRegister();
    static IMLoginRegister* create(UserAction action);
    bool init(UserAction action);
protected:
	virtual void viewDidLoad();
	virtual void viewDidUnload();
	virtual void viewDidAppear();
	void loadView();
	bool onTextFieldAttachWithIME(CATextField * sender);
	bool onTextFieldDetachWithIME(CATextField * sender);
	virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
	virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);
public:
	void onButtonLogin(CAControl *pTarget, CCPoint point);  //用户登录
	void onButtonRegister(CAControl *pTarget, CCPoint point); //用户注册
	void onButtonCancel(CAControl *pTarget, CCPoint point);  //返回上一级
	void onButtonMissPassword(CAControl *pTarget, CCPoint point); //忘记密码
	void onButtonSwitchToRegister(CAControl *pTarget, CCPoint point); //登录界面进入注册界面
	void onButtonSwitchToLogin(CAControl *pTarget, CCPoint point); //注册界面进入登录界面
protected:
	UserAction m_pAction;
	CAScrollView *m_pLayoutView;
	CANavigationBarItem* m_pNavigationBarItem;
	CABarButtonItem* m_pButtonCancl;
	
	CATextField *m_pAccount;
	CATextField *m_pAccountRegist;
	CATextField *m_pPassword;
	CATextField *m_pPasswordAgain;

	CAButton *m_pLoginButton;
	CAButton *m_pRegisterButton;
	CAButton *m_pMissPassword;
	CAButton *m_pButtonSwitch;
	CAButton *m_pButtonSwitchTo;
};



#endif