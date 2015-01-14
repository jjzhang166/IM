#ifndef __IM_LOGIN_REGISTER_H__
#define __IM_LOGIN_REGISTER_H__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;
//�û���¼����ע���¼�
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
	void onButtonLogin(CAControl *pTarget, CCPoint point);  //�û���¼
	void onButtonRegister(CAControl *pTarget, CCPoint point); //�û�ע��
	void onButtonCancel(CAControl *pTarget, CCPoint point);  //������һ��
	void onButtonMissPassword(CAControl *pTarget, CCPoint point); //��������
	void onButtonSwitchToRegister(CAControl *pTarget, CCPoint point); //��¼�������ע�����
	void onButtonSwitchToLogin(CAControl *pTarget, CCPoint point); //ע���������¼����
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