//
//  CommentInputView.cpp
//  IM


#include "CommentInputView.h"

CommentInputView* CommentInputView::createWithFrame(const CADipRect& rect)
{
    CommentInputView *view = new CommentInputView();
    if (view && view->initWithFrame(rect))
    {
        view->autorelease();
        
        
        
        return view;
    }
    CC_SAFE_DELETE(view);
    return NULL;

}

CommentInputView::CommentInputView()
: m_pTextFeild(NULL)
, m_pBtnComment(NULL)
, m_pBtnPraise(NULL)
, m_pLabComment(NULL)
, m_pLabPraise(NULL)
, m_pBtnSend(NULL)
, m_eType(DetailPage)
, m_fButtom(0)
{
    
}

CommentInputView::~CommentInputView()
{
    
}

bool CommentInputView::initWithFrame(const CCRect& rect)
{
    if (!CAView::initWithFrame(rect))
        return false;
    CADipSize size = rect.size;
	m_fButtom = rect.origin.y;
    setColor(ccc4(0xcc, 0xcc, 0xcc, 0xff));
    
    m_pTextFeild = CATextField::createWithFrame(CADipRect(20.0f, 14.0f, size.width - 240.0f, 60.0f));
	m_pTextFeild->setDelegate(this);
	m_pTextFeild->setKeyboardReturnType(KEY_BOARD_RETURN_SEND);
    addSubview(m_pTextFeild);
    
    m_pBtnComment = CAButton::create(CAButtonTypeCustom);
    m_pBtnComment->setFrame(CADipRect(size.width - 200.0f, 10.0f, 72.0f, 60.0f));
    CAImageView* pImgComment = CAImageView::createWithImage(CAImage::create("baby_genius/detail_page/comment1.png"));
    m_pBtnComment->setBackGroundViewForState(CAControlStateNormal, pImgComment);
    pImgComment = CAImageView::createWithImage(CAImage::create("baby_genius/detail_page/comment2.png"));
    m_pBtnComment->setBackGroundViewForState(CAControlStateHighlighted, pImgComment);
    addSubview(m_pBtnComment);
    
    m_pBtnPraise = CAButton::create(CAButtonTypeCustom);
    m_pBtnPraise->setFrame(CADipRect(size.width - 100.0f, 10.0f, 72.0f, 60.0f));
    CAImageView* pImgPraise = CAImageView::createWithImage(CAImage::create("baby_genius/detail_page/praise1.png"));
    m_pBtnPraise->setBackGroundViewForState(CAControlStateNormal, pImgPraise);
    pImgPraise = CAImageView::createWithImage(CAImage::create("baby_genius/detail_page/praise2.png"));
    m_pBtnPraise->setBackGroundViewForState(CAControlStateHighlighted, pImgPraise);
    m_pBtnPraise->setBackGroundViewForState(CAControlStateSelected, CAImageView::createWithImage(CAImage::create("baby_genius/detail_page/praise2.png")));
    m_pBtnPraise->setAllowsSelected(true);
    addSubview(m_pBtnPraise);
    
    CAScale9ImageView* pImg = CAScale9ImageView::createWithCenter(CADipRect(size.width - 150.0f, 21.0f, 20.0f, 24.0f));
    CCRect capInsets = CCRect(9, 20, 2, 0);
    pImg->setImage(CAImage::create("baby_genius/button_bg_normal.png"));
    pImg->setCapInsets(capInsets);
    addSubview(pImg);
    m_pImg = pImg;
    
    m_pLabComment = CALabel::createWithCenter(CADipRect(size.width - 150.0f, 20.0f, 160.0f, 30.0f));
    m_pLabComment->setColor(CAColor_white);
    m_pLabComment->setFontSize(_px(20.0f)  );
    m_pLabComment->setTextAlignment(CATextAlignmentCenter);
    m_pLabComment->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    addSubview(m_pLabComment);
    
    m_pLabPraise = CALabel::createWithCenter(CADipRect(size.width - 50.0f, 20.0f, 160.0f, 30.0f));
    m_pLabPraise->setColor(ccc4(0x99, 0x99, 0x99, 0xff));
    m_pLabPraise->setFontSize(_px(20.0f));
    m_pLabPraise->setTextAlignment(CATextAlignmentCenter);
    m_pLabPraise->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    addSubview(m_pLabPraise);

	m_pBtnSend = CAButton::create(CAButtonTypeCustom);
	m_pBtnSend->setFrame(CADipRect(size.width -130, size.height - 74, 110, 60));
	capInsets = CCRect(9, 9, 1, 1);
	CAScale9ImageView* pImgSendBack = CAScale9ImageView::createWithImage(CAImage::create("baby_genius/button_bg_normal.png"));
	pImgSendBack->setCapInsets(capInsets);
	m_pBtnSend->setBackGroundViewForState(CAControlStateNormal, pImgSendBack);
	m_pBtnSend->setTitleForState(CAControlStateNormal, "发送");
	m_pBtnSend->setTitleColorForState(CAControlStateNormal, CAColor_white);
	m_pBtnSend->setVisible(false);
	addSubview(m_pBtnSend);
    
    return true;
}

void CommentInputView::SetModelInfo(const int nComment, const int nPraise, const bool isPraise)
{
    CADipSize size = getFrame().size;
    m_pLabComment->setText(CCString::createWithFormat("%d",nComment)->getCString());
    m_pLabPraise->setText(CCString::createWithFormat("%d",nPraise)->getCString());
    if (isPraise)
        m_pBtnPraise->setControlState(CAControlStateSelected);
	
    float w = CAImage::getStringWidth("", _px(20.0f), CCString::createWithFormat("%d",nComment)->getCString());
    m_pImg->setCenter(CADipRect(size.width - 150.0f, 21.0f, w + 10.0f, 24.0f));
}


void CommentInputView::showCommentPage()
{
	m_eType = CommentPage;
	ShowDetailWiget(false);
}

void CommentInputView::ShowDetailWiget(bool bShow)
{
	m_pBtnPraise->setVisible(bShow);
	m_pLabPraise->setVisible(bShow);
	m_pBtnComment->setVisible(bShow);
	m_pLabComment->setVisible(bShow);
	m_pImg->setVisible(bShow);
	m_pBtnSend->setVisible(!bShow);

	CADipSize size = getFrame().size;
	if (bShow)
		m_pTextFeild->setFrame(CADipRect(20.0f, 10.0f, size.width - 240.0f, 60.0f));
	else
		m_pTextFeild->setFrame(CADipRect(20.0f, 14.0f, size.width - 170.0f, 60.0f));
}

bool CommentInputView::onTextFieldAttachWithIME(CATextField * sender)
{
	if (m_eType == DetailPage)
		ShowDetailWiget(false);
	
    if (m_pDelegate)
    {
        m_pDelegate->commentInputView_onTextFieldAttachWithIME(sender);
    }
    
	return false;
}

bool CommentInputView::onTextFieldDetachWithIME(CATextField * sender)
{
	if (m_eType == DetailPage)
		ShowDetailWiget(true);
	
	CCRect rect = getFrame();
	rect.origin.y = m_fButtom;
	setFrame(rect);

    if (m_pDelegate)
    {
        m_pDelegate->commentInputView_onTextFieldDetachWithIME(sender);
    }
    
	return false;
}

bool CommentInputView::getKeyBoardHeight(int height)
{
	CCRect rect = getFrame();
	rect.origin.y = m_fButtom - height;
	setFrame(rect);
    
    if (m_pDelegate)
    {
        m_pDelegate->commentInputView_getKeyBoardHeight(height);
    }

	return false;
}

bool CommentInputView::keyBoardCallBack(CATextField *sender)
{
	if (m_pDelegate)
	{
        m_pDelegate->onSend(sender->getText());
        m_pDelegate->commentInputView_keyBoardCallBack(sender);
	}
	
	return false;
}


