#include "ChatViewCell.h"

ChatViewCell::ChatViewCell()
:fontSize(22)
{

}

ChatViewCell::~ChatViewCell()
{

}

ChatViewCell* ChatViewCell::create(const std::string& identifier, const CADipRect& _rect)
{
	ChatViewCell* tableViewCell = new ChatViewCell();
	if(tableViewCell&&tableViewCell->initWithReuseIdentifier(identifier))
	{
		tableViewCell->setFrame(_rect);
		tableViewCell->autorelease();
		return tableViewCell;
	}
	CC_SAFE_DELETE(tableViewCell);
	return NULL;
}

void ChatViewCell::initWithCell()
{
	CADipSize m_size = this->getFrame().size;
	
	// event-time [top-middle]
	CALabel* cellText = CALabel::createWithCenter(CADipRect(m_size.width*0.5, m_size.height*0.05, m_size.width*0.3, m_size.height*0.2));
	cellText->setTag(100);
	cellText->setFontSize(_px(18));
	cellText->setColor(CAColor_gray);
	cellText->setTextAlignment(CATextAlignmentCenter);
	cellText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	this->addSubview(cellText);

	// avatar img  left/right
	CAImageView* avatarView = CAImageView::create();	
	avatarView->setImage(CAImage::create("chat_res/default.jpg"));
	CAImageView* maskView = CAImageView::createWithImage(CAImage::create("chat_res/mask_image.png"));
	maskView->setScale(0.5);
	maskView->setTag(101);
	avatarView->setTag(102);
	avatarView->setFrame(CADipRect(6, (m_size.height - maskView->getFrame().size.height)*0.5, maskView->getFrame().size.width, maskView->getFrame().size.height));
	maskView->setFrame(CADipRect(6, (m_size.height - maskView->getFrame().size.height)*0.5, maskView->getFrame().size.width, maskView->getFrame().size.height));
	this->insertSubview(avatarView, 1);
	this->insertSubview(maskView, 2);


	// content text/img left/right
	CAScale9ImageView* meBgView = CAScale9ImageView::createWithImage(CAImage::create("chat_res/chat_bg_me.png"));
	meBgView->setTag(105);
	meBgView->setVisible(false);
	this->addSubview(meBgView);
	meBgView->setFrame(CADipRect(m_size.width*0.5, m_size.height*0.2, meBgView->getFrame().size.width, meBgView->getFrame().size.height));

	CAScale9ImageView* otBgView = CAScale9ImageView::createWithImage(CAImage::create("chat_res/chat_bg_ot.png"));
	otBgView->setTag(106);
	otBgView->setVisible(false);
	this->addSubview(otBgView);
	otBgView->setFrame(CADipRect(m_size.width*0.5, m_size.height*0.2, otBgView->getFrame().size.width, otBgView->getFrame().size.height));
	
	// status 
// 	CAActivityIndicatorView* gray = CAActivityIndicatorView::createWithCenter(CADipRect(m_size.width*0.3, m_size.height*0.4,
// 		m_size.width*0.1, m_size.width*0.1));
// 	gray->setStyle(CAActivityIndicatorViewStyleGray);
// 	gray->setScale(0.4);
// 	this->addSubview(gray);
}


void ChatViewCell::normalTableViewCell()
{
}

void ChatViewCell::highlightedTableViewCell()
{
}

void ChatViewCell::selectedTableViewCell()
{
}

void ChatViewCell::disabledTableViewCell()
{
}

void ChatViewCell::showImgMsg(string& url, const char* dpos)
{
	/*
	CCHttpRequest* request = new CCHttpRequest();
	request->setTag(dpos);
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setUrl(url.c_str());
	request->setResponseCallback(this, httpresponse_selector(ChatViewCell::requestResult));
	CCHttpClient* httpClient = CCHttpClient::getInstance();
	httpClient->setTimeoutForConnect(30);
	httpClient->send(request);
	request->release();
	*/
}
void ChatViewCell::requestResult(CCHttpClient* client, CCHttpResponse* response)
{
	if (!response->isSucceed())
	{
		return;
	}
	std::string responseRes = "";
	std::vector<char> *buffer = response->getResponseData();
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string bufffff(buffer->begin(), buffer->end());
	unsigned char* pBuffer = new unsigned char[buffer->size()];
	memcpy(pBuffer, bufffff.c_str(), buffer->size());
	CCLOG("%ld", buffer->size());
	CCImage* pImage = new CCImage();
	bool bret = pImage->initWithImageData(pBuffer, buffer->size(), CCImage::kFmtJpg);
	CAImage* pImageBuf = new CAImage();
	pImageBuf->initWithImage(pImage);
	CAImageView* imageView = CAImageView::createWithImage(pImageBuf);

	// commom data
	CADipSize cellSize = this->getFrame().size;
	CAImageView* maskView = (CAImageView*)this->getSubviewByTag(101);
	CAImageView* avatView = (CAImageView*)this->getSubviewByTag(102);
	CAScale9ImageView* meBgView = (CAScale9ImageView*)this->getSubviewByTag(105);
	CAScale9ImageView* otBgView = (CAScale9ImageView*)this->getSubviewByTag(106);
	// limit 
	int liWidth = cellSize.width*0.6;
	int liHeight = cellSize.height*0.7;		
	CCRect srcContent = imageView->getBounds();	
	float wRatio = liWidth / srcContent.size.width;
	float hRatio = liHeight / srcContent.size.height;
	imageView->setScaleX(wRatio);
	imageView->setScaleY(hRatio);
	// left / right
	if (!strcmp("right", response->getHttpRequest()->getTag()) && (response->getResponseCode() == 200))
	{
		otBgView->setVisible(false);
		meBgView->setVisible(true);

		imageView->setFrame(CADipRect(cellSize.width - maskView->getFrame().size.width - 10 - 6 - 6 - imageView->getFrame().size.width,
			(cellSize.height - imageView->getFrame().size.height)/2,
			cellSize.width*0.6,
			imageView->getFrame().size.height));
		this->addSubview(imageView);

		meBgView->setCenter(CADipRect(cellSize.width - 6 - maskView->getFrame().size.width - 11 - imageView->getFrame().size.width / 2,
			cellSize.height*0.5,
			imageView->getFrame().size.width + 30,
			imageView->getFrame().size.height + 30));

		avatView->setFrame(CADipRect(cellSize.width - 6 - maskView->getFrame().size.width,
			(cellSize.height - meBgView->getFrame().size.height)*0.5 + meBgView->getFrame().size.height - maskView->getFrame().size.height,
			maskView->getFrame().size.width,
			maskView->getFrame().size.height));
		maskView->setFrame(CADipRect(cellSize.width - 6 - maskView->getFrame().size.width,
			(cellSize.height - meBgView->getFrame().size.height)*0.5 + meBgView->getFrame().size.height - maskView->getFrame().size.height,
			maskView->getFrame().size.width,
			maskView->getFrame().size.height));		
	}
	else if (!strcmp("left", response->getHttpRequest()->getTag()) && (response->getResponseCode() == 200))
	{
		otBgView->setVisible(true);
		meBgView->setVisible(false);
		
		imageView->setFrame(CADipRect(maskView->getFrame().size.width + 10 + 6 + 6 ,
			(cellSize.height - imageView->getFrame().size.height) / 2,
			cellSize.width*0.6,
			imageView->getFrame().size.height));
		this->addSubview(imageView);

		otBgView->setCenter(CADipRect(maskView->getFrame().size.width + 5 + 6 + 6 + imageView->getFrame().size.width / 2,
			cellSize.height*0.5,
			imageView->getFrame().size.width + 30,
			imageView->getFrame().size.height + 30));

		avatView->setFrame(CADipRect(6,
			(cellSize.height - otBgView->getFrame().size.height)*0.5 + otBgView->getFrame().size.height - maskView->getFrame().size.height,
			maskView->getFrame().size.width,
			maskView->getFrame().size.height));
		maskView->setFrame(CADipRect(6,
			(cellSize.height - otBgView->getFrame().size.height)*0.5 + otBgView->getFrame().size.height - maskView->getFrame().size.height,
			maskView->getFrame().size.width,
			maskView->getFrame().size.height));

	}
	pImage->release();
	pImageBuf->release();
	delete[]pBuffer;
}

void ChatViewCell::setMsgTime(string& mTime)
{
	CALabel* cellText = (CALabel*)this->getSubviewByTag(100);
	cellText->setText(mTime);
}

void ChatViewCell::showTextMsg(string& msg, const char* dpos)
{
	CADipSize cellSize = this->getFrame().size;
	CAImageView* maskView = (CAImageView*)this->getSubviewByTag(101);
	CAImageView* avatView = (CAImageView*)this->getSubviewByTag(102);
	CAScale9ImageView* meBgView = (CAScale9ImageView*)this->getSubviewByTag(105);
	CAScale9ImageView* otBgView = (CAScale9ImageView*)this->getSubviewByTag(106);

	int strWidth = CAImage::getStringWidth("", _px(fontSize), msg);
	int fontHeight = CAImage::getFontHeight("", _px(fontSize)) + fontSize / 4;
	int n = strlen(msg.c_str()) / 3;
	CALabel* msgText;
	if (strcmp(dpos, "right") == 0)
	{
		if (n > 15)
		{
			msgText = CALabel::createWithCenter(CADipRect(cellSize.width - maskView->getFrame().size.width - 5 - 6 - 6 - cellSize.width*0.6 / 2,
				cellSize.height*0.5,
				cellSize.width*0.6,
				(n / 15 + 1) * fontHeight));
		}
		else
		{
			msgText = CALabel::createWithCenter(CADipRect(cellSize.width - maskView->getFrame().size.width - 5 - 6 - 6 - strWidth / 2,
				cellSize.height*0.5, strWidth, fontHeight));
		}
		msgText->setFontSize(_px(fontSize));
		msgText->setTextAlignment(CATextAlignmentLeft);
		msgText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		msgText->setTag(103);
		msgText->setText(msg);
		this->addSubview(msgText);

		otBgView->setVisible(false);
		meBgView->setVisible(true);
		// 此处设置
		meBgView->setCenter(CADipRect(cellSize.width - 6 - maskView->getFrame().size.width - 11 - msgText->getFrame().size.width / 2,
			cellSize.height*0.5,
			msgText->getFrame().size.width + 30,
			msgText->getFrame().size.height + 30));

		avatView->setFrame(CADipRect(cellSize.width - 6 - maskView->getFrame().size.width,
			(cellSize.height - meBgView->getFrame().size.height)*0.5 + meBgView->getFrame().size.height - maskView->getFrame().size.height,
			maskView->getFrame().size.width,
			maskView->getFrame().size.height));
		maskView->setFrame(CADipRect(cellSize.width - 6 - maskView->getFrame().size.width,
			(cellSize.height - meBgView->getFrame().size.height)*0.5 + meBgView->getFrame().size.height - maskView->getFrame().size.height,
			maskView->getFrame().size.width,
			maskView->getFrame().size.height));
	}
	else if (strcmp(dpos, "left") == 0)
	{
		if (n > 15)
		{
			msgText = CALabel::createWithCenter(CADipRect(maskView->getFrame().size.width + 15 + 6 + 6 + cellSize.width*0.6/2,
				cellSize.height*0.5,
				cellSize.width*0.6,
				(n / 15 + 1) * fontHeight));
		}
		else
		{
			msgText = CALabel::createWithCenter(CADipRect(maskView->getFrame().size.width + 8 + 6 + 6 + strWidth / 2,
				cellSize.height*0.5, strWidth, fontHeight));
		}
		msgText->setFontSize(_px(fontSize));
		msgText->setTextAlignment(CATextAlignmentLeft);
		msgText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		msgText->setTag(103);
		msgText->setText(msg);
		this->addSubview(msgText);

		otBgView->setVisible(true);
		meBgView->setVisible(false);
		// 此处设置
		otBgView->setCenter(CADipRect(maskView->getFrame().size.width + 5 + 6 + 6 + msgText->getFrame().size.width / 2,
			cellSize.height*0.5,
			msgText->getFrame().size.width + 30,
			msgText->getFrame().size.height + 30));

		avatView->setFrame(CADipRect(6,
			(cellSize.height - otBgView->getFrame().size.height)*0.5 + otBgView->getFrame().size.height - maskView->getFrame().size.height,
			maskView->getFrame().size.width,
			maskView->getFrame().size.height));
		maskView->setFrame(CADipRect(6,
			(cellSize.height - otBgView->getFrame().size.height)*0.5 + otBgView->getFrame().size.height - maskView->getFrame().size.height,
			maskView->getFrame().size.width,
			maskView->getFrame().size.height));
	}	
}

