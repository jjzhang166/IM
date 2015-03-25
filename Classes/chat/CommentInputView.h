//
//  CommentInputView.h
//  IM


#ifndef __IM__CommentInputView__
#define __IM__CommentInputView__

#include "CrossApp.h"

class CommentInputViewDelegate
{
public:
	virtual void onSend(const string& sText) {}
    
    virtual bool commentInputView_onTextFieldAttachWithIME(CATextField * sender) { return false; }
    
    virtual bool commentInputView_onTextFieldDetachWithIME(CATextField * sender) { return false; }
    
    virtual bool commentInputView_getKeyBoardHeight(int height) { return false; }
    
    virtual bool commentInputView_keyBoardCallBack(CATextField *sender) { return false; }
};

class CommentInputView : public CAView, public CATextFieldDelegate
{
public:

	enum ViewType
	{
		CommentPage,
		DetailPage,
	};
    
    static CommentInputView* createWithFrame(const CADipRect& rect);
    
    void SetModelInfo(const int nComment, const int nPraise, const bool isPraise);
	
	void showCommentPage();
    
private:
    CommentInputView();
    virtual ~CommentInputView();
    
    bool initWithFrame(const CCRect& rect);

	void ShowDetailWiget(bool bShow);

public:
	virtual bool onTextFieldAttachWithIME(CATextField * sender);

	virtual bool onTextFieldDetachWithIME(CATextField * sender);

	virtual bool getKeyBoardHeight(int height);
	
	virtual bool keyBoardCallBack(CATextField *sender);
    
private:
	CC_SYNTHESIZE_READONLY(CATextField*, m_pTextFeild, TextFeild);
	CC_SYNTHESIZE_READONLY(CAButton*, m_pBtnComment, BtnComment);
	CC_SYNTHESIZE_READONLY(CAButton*, m_pBtnPraise, BtnPraise);
    CALabel*            m_pLabComment;
    CALabel*            m_pLabPraise;
	CC_SYNTHESIZE_READONLY(CAButton*, m_pBtnSend, BtnSend);
    CAScale9ImageView*  m_pImg;
	CC_SYNTHESIZE(CommentInputViewDelegate*, m_pDelegate, Delegate);
	
	ViewType			m_eType;
	float				m_fButtom;
};

#endif /* defined(__IM__CommentInputView__) */
