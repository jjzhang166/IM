#include "IMChatController.h"
#include "ChatViewCell.h"
#include "CommentInputView.h"
#include "../data/TableLanguage.h"
#include "../table/TableLanguagesfontnewHeader.h"
#include "RootWindow.h"

#define CAColor_blueStyle ccc4(51,204,255,255)
#define KEYBOARD_HEIGHT 88.0f
static IMChatController* m_vController = NULL;

IMChatController::IMChatController()
:m_sID("")
,m_bIsOpen(false)
,m_pSize(CCSizeZero)
{

}

IMChatController::~IMChatController()
{
    m_vecMessage.clear();
    m_mapAllMessage.clear();
}

IMChatController* IMChatController::getInstance()
{
    if (m_vController == NULL)
    {
        m_vController = new IMChatController();
    }
    return m_vController;
}

void IMChatController::setControllerByID(std::string ID)
{
    m_sID = ID;
    m_vecMessage = getMessageByID(m_sID);
}

VEC_MESSAGE& IMChatController::getMessageByID(std::string ID)
{
    MAP_ID_MESSAGE::iterator itr = m_mapAllMessage.find(ID);
    if(itr!=m_mapAllMessage.end())
    {
        return (itr->second);
    }
    else
    {
        VEC_MESSAGE vecMessage;
        itr = m_mapAllMessage.insert(itr,pair<std::string , VEC_MESSAGE>(ID, vecMessage));
    }
    return (itr->second);
}

void IMChatController::pushMessageByID(std::string ID, HXSDKMessage* message)
{
    MAP_ID_MESSAGE::iterator itr = m_mapAllMessage.find(ID);
    if(itr!=m_mapAllMessage.end())
    {
        (itr->second).push_back(message);
        CCLog("find !!!id:%s,  messageCount:%lu", ID.c_str(), itr->second.size());
    }
    else
    {
        CCLog("not find ...id:%s", ID.c_str());
        VEC_MESSAGE vecMessage;
        vecMessage.push_back(message);
        itr = m_mapAllMessage.insert(--itr,pair<std::string , VEC_MESSAGE>(ID, vecMessage));
    }
    m_vecMessage = getMessageByID(m_sID);
    if(m_bIsOpen)
    {
        p_TableView->reloadData();
        CCPoint point = p_TableView->getContentOffset();
        CCLog("%f   %f",point.x,point.y);
        CCSize tableSize = p_TableView->getViewSize();
        float offHeight = tableSize.height- m_pSize.height + KEYBOARD_HEIGHT;
        if(offHeight<0) offHeight = 0;
        p_TableView->setContentOffset(CCPoint(0, offHeight), true);
    }
}

HXSDKMessage* IMChatController::getMessagePackageByMessageInfo()
{
    
}

bool IMChatController::init()
{
    if (CAViewController::init())
    {
        CABarButtonItem* backItem = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LOGOUT).c_str(), NULL, NULL);
        backItem->setTarget(this, CAControl_selector(IMChatController::onButtonBack));
        
        m_pNavigationBarItem = CANavigationBarItem::create(m_sID.c_str());
        m_pNavigationBarItem->setShowGoBackButton(false);
        m_pNavigationBarItem->addLeftButtonItem(backItem);
        setNavigationBarItem(m_pNavigationBarItem);
        m_pNavigationBarItem->retain();
        return true;
    }
    return false;
}

void IMChatController::viewDidLoad()
{
    m_pSize = this->getView()->getBounds().size;

	p_TableView = CATableView::createWithCenter(CADipRect(m_pSize.width*0.5, (m_pSize.height-KEYBOARD_HEIGHT)*0.5, m_pSize.width, m_pSize.height - KEYBOARD_HEIGHT));
	p_TableView->setTableViewDataSource(this);
	p_TableView->setTableViewDelegate(this);
	//p_TableView->setAllowsSelection(true);
	//p_TableView->setAllowsMultipleSelection(true);s
	//p_TableView->setSeparatorColor(CAColor_clear);
	
	//chinahypo 2015-3-19
	//message = HXSDKController::getInstance()->loadMessage(m_sID);
	this->getView()->addSubview(p_TableView);
    
    m_pCommentInputView = CommentInputView::createWithFrame(CADipRect(0, m_pSize.height -KEYBOARD_HEIGHT, m_pSize.width, KEYBOARD_HEIGHT));
    m_pCommentInputView->getBtnComment()->addTarget(this, CAControl_selector(IMChatController::onBtnComment), CAControlEventTouchUpInSide);
    m_pCommentInputView->getBtnSend()->addTarget(this, CAControl_selector(IMChatController::onBtnSend), CAControlEventTouchUpInSide);
    m_pCommentInputView->getBtnPraise()->addTarget(this, CAControl_selector(IMChatController::onBtnPraise), CAControlEventTouchUpInSide);
    m_pCommentInputView->showCommentPage();
    m_pCommentInputView->setDelegate(this);
    m_pCommentInputView->getTextFeild()->setKeyboardReturnType(KEY_BOARD_RETURN_SEND);
    m_pCommentInputView->getTextFeild()->becomeFirstResponder();
    getView()->addSubview(m_pCommentInputView);
}

void IMChatController::viewDidUnload()
{
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
}

void IMChatController::viewDidAppear()
{
    m_bIsOpen = true;
}

void IMChatController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{

}

void IMChatController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{

}

bool loaded = false;
CATableViewCell* IMChatController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
	CADipSize _size = cellSize;
	ChatViewCell* cell = dynamic_cast<ChatViewCell*>(table->dequeueReusableCellWithIdentifier("CrossApp"));
	if (cell == NULL)
	{
		cell = ChatViewCell::create("CrossApp", CADipRect(0, 0, _size.width, _size.height));
		cell->initWithCell();
	}
	if (loaded)
		return cell;
	string dpos;
//	sprintf(time,"%ld",m_vecMessage.at(row)->m_vTime);
//	timeLast = time;
//	cell->setMsgTime(timeLast);
    if (m_vecMessage.at(row)->m_vSend.compare(HXSDKController::getInstance()->getMyName()))
	{
		dpos = "left";
	}
	else
	{
		dpos = "right";
	}
	cell->showTextMsg(m_vecMessage.at(row)->m_vMessage, dpos.c_str());
	return cell;
	/*
	// 开始显示
	cell->setMsgTime(strTime);
	string dpos = (isMe == true) ? "right" : "left";
	if (isImg)
	{// 暂时仅支持JPG格式
		cell->showImgMsg(url, dpos.c_str());
	}
	else
	{
		cell->showTextMsg(msg, dpos.c_str());
	}

	return cell;
     */
}

// CAView* FirstViewController::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
// {
// 	std::string head = "";
// 	head = (section == 0) ? "Selection-0" : "Selection-1";
// 	CAView* view = CAView::createWithColor(CAColor_gray);
// 
// 	CADipSize _size = viewSize;
// 	CALabel* header = CALabel::createWithCenter(CADipRect(_size.width*0.5, _size.height*0.5, _size.width*0.8, _size.height));
// 	header->setText(head);
// 	header->setFontSize(_px(30));
// 	header->setColor(CAColor_white);
// 	header->setTextAlignment(CATextAlignmentCenter);
// 	header->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
// 	view->addSubview(header);
// 
// 	return view;
// }
 
 CAView* IMChatController::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
 {
 	CAView* view = CAView::createWithColor(CAColor_gray);
 	return view;
 }

unsigned int IMChatController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    CCLog("message size:%lu",m_vecMessage.size());
    return m_vecMessage.size();
}

unsigned int IMChatController::numberOfSections(CATableView *table)
{
	return 1;
}

unsigned int IMChatController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	return _px(90);
}

unsigned int IMChatController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
	return 0;
}

unsigned int IMChatController::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
{
	return 1;
}

void IMChatController::onBtnComment(CAControl* control, CCPoint point)
{
    
    CCLog("onBtnComment !!!------:%s", m_pCommentInputView->getTextFeild()->getText().c_str());
}

void IMChatController::onBtnSend(CAControl* control, CCPoint point)
{
    std::string message = m_pCommentInputView->getTextFeild()->getText();
    HXSDKController::getInstance()->pushMessageDetail(m_sID, 1, 1000, HXSDKController::getInstance()->getMyName(), m_sID, 1, message);
    HXSDKController::getInstance()->sendMessage(message.c_str(), m_sID.c_str());
    CCLog("onBtnSend !!!------:%s", message.c_str());
    m_pCommentInputView->getTextFeild()->setText("");
}

void IMChatController::onBtnPraise(CAControl* control, CCPoint point)
{
    
    CCLog("onBtnPraise !!!------:%s", m_pCommentInputView->getTextFeild()->getText().c_str());
}

void IMChatController::onSend(const string& sText)
{
    if (sText.empty())
    {
        CCLog("is empty ...");
        return;
    }
    CCLog("send !!!------:%s", sText.c_str());
}

bool IMChatController::commentInputView_onTextFieldAttachWithIME(CATextField * sender)
{
    CCLog("aaaaaaaaaaaaa");
//    m_iKeyBoardHeight = 500;
//    if(!m_isReply)
//    {
//        CCPoint point =  m_pTableView->getFrameOrigin();
//        m_pTableView->setFrameOrigin(ccp(point.x,point.y-m_iKeyBoardHeight));
//    }
    return false;
}
	
bool IMChatController::commentInputView_onTextFieldDetachWithIME(CATextField * sender)
{
    CCLog("bbbbbbbbbbb");
//    m_iKeyBoardHeight = 500;
//    CCPoint point =  m_pTableView->getFrameOrigin();
//    m_pTableView->setFrameOrigin(ccp(point.x,point.y+m_iKeyBoardHeight));
//    m_isReply = false;
    return false;
}

bool IMChatController::commentInputView_getKeyBoardHeight(int height)
{
    return false;
}

bool IMChatController::commentInputView_keyBoardCallBack(CATextField *sender)
{
    return false;
}

void IMChatController::onButtonBack(CAControl* control, CCPoint point)
{
    m_bIsOpen = false;
    RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(this);
}
