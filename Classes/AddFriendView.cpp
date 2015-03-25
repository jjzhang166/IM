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
    m_pButtons.clear();
}

AddFriendView* AddFriendView::create(int numbers, const CCRect& rect,const CCRect& winRect)
{
	addfriendview = new AddFriendView();
	if (addfriendview && addfriendview->init(numbers, rect, winRect))
	{
		addfriendview->autorelease();
		return addfriendview;
	}
	CC_SAFE_DELETE(addfriendview);
	return NULL;
}

bool AddFriendView::init(int numbers, const CCRect& rect,const CCRect& winRect)
{
    if(CAView::init())
    {
        count = numbers;
        m_rect = rect;
        addfriendview->setFrame(winRect);
        addfriendview->setColor(ccc4(0, 100, 0, 0));
        background = CAScale9ImageView::createWithImage(CAImage::create(FRIEND_ADD));
        background->setFrame(m_rect);
        addfriendview->addSubview(background);
        float tmp = m_rect.size.height/count;
        for (int i = 0; i < count; i++)
        {
            CAButton* button[10];
            CAView* line[9];
            button[i] = CAButton::createWithCenter(CCRect(m_rect.size.width*0.5, tmp*(0.5+i), m_rect.size.width, tmp), CAButtonTypeCustom);
            button[i]->setBackGroundViewForState(CAControlStateAll, CAView::createWithColor(CAColor_clear));
            button[i]->setTitleColorForState(CAControlStateAll, CAColor_white);
            m_pButtons.push_back(button[i]);
            background->addSubview(button[i]);
            if (i != 0)
            {
                line[i] = CAView::createWithCenter(CCRect(m_rect.size.width*0.5, tmp*i, m_rect.size.width, _px(1)));
                background->addSubview(line[i]);
            }
            
        }
        return true;
    }
    return false;
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