#include "AddFriendView.h"
#include "dispatcher/CATouch.h"
#include "table/TableLanguagesfontnewHeader.h"
#include "data/TableLanguage.h"
#include "IMDATA.h"

static AddFriendView *addfriendview = NULL;
AddFriendView::AddFriendView() :m_pTarget(NULL)
, m_pCallFunc(NULL)
, m_pButtons(NULL)
, background(NULL)
{
	
}

AddFriendView::~AddFriendView()
{

}

AddFriendView* AddFriendView::create(int numbers, const CCRect& rect)
{
	addfriendview = new AddFriendView();
	if (addfriendview && addfriendview->init(numbers, rect))
	{
		addfriendview->autorelease();
		return addfriendview;
	}
	CC_SAFE_DELETE(addfriendview);
	return NULL;
}

bool AddFriendView::init(int numbers, const CCRect& rect)
{
	count = numbers;
	winRect = rect;
	addfriendview->setFrame(winRect);
	addfriendview->setColor(ccc4(0, 0, 0, 0));
	background = CAScale9ImageView::createWithImage(CAImage::create(FRIEND_ADD));
	background->setFrame(CCRect(winRect.size.width*0.5, 0, winRect.size.width*0.4, winRect.size.height*0.1*count));
	addfriendview->addSubview(background);
	for (int i = 0; i < count; i++)
	{
		CAButton* button[10];
		CAView* line[9];
		button[i] = CAButton::createWithCenter(CCRect(winRect.size.width*0.7, winRect.size.height*0.05*(2*i+1), WIDTH, HEIGHT), CAButtonTypeCustom);
		button[i]->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_clear));
		button[i]->setTitleColorForState(CAControlStateAll, CAColor_white);
		m_pButtons.push_back(button[i]);
		addfriendview->addSubview(button[i]);
		if (i < count - 1)
		{
			line[i] = CAView::createWithCenter(CCRect(winRect.size.width*0.7, winRect.size.height*0.1*(i + 1), WIDTH, _px(1)));
			addfriendview->addSubview(line[i]);
		}

	}
	return true;
}

void AddFriendView::setItemNameAtIndex(string name, int index)
{
	m_pButtons[index]->setTitleForState(CAControlStateAll,name);
	m_pButtons[index]->addTarget(this, CAControl_selector(AddFriendView::onButtonCallBack), CAControlEventTouchUpInSide);
}

void AddFriendView::addTarget(CAObject* target, SEL_AddFriendView selector)
{
	m_pTarget = target;
	m_pCallFunc = selector;
}

void AddFriendView::callFunc(CAObject* object, int index)
{
	if (m_pTarget && m_pCallFunc)
	{
		((CAObject *)m_pTarget->*m_pCallFunc)(this, index);
	}
}

#pragma button callback
void AddFriendView::onButtonCallBack(CAControl *pTarget, CCPoint point)
{
	int number = 0;
	for (std::vector<CAButton*>::iterator iter = m_pButtons.begin(); iter != m_pButtons.end(); ++iter)
	{
		if (pTarget == *iter)
		{
			if (m_pTarget && m_pCallFunc)
			{
				((CAObject *)m_pTarget->*m_pCallFunc)(this, number);
			}
		}
		number++;
	}
}


#pragma mark --

bool AddFriendView::ccTouchBegan(CATouch *pTouch, CAEvent *pEvent)
{
	callFunc(this, -1);
	return true;
}

void AddFriendView::ccTouchMoved(CATouch *pTouch, CAEvent *pEvent)
{
	callFunc(this, -1);
}
void AddFriendView::ccTouchEnded(CATouch *pTouch, CAEvent *pEvent)
{
	callFunc(this, -1);
}