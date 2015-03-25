
#include "IMChatController.h"

#include "ChatViewCell.h"

#define CAColor_blueStyle ccc4(51,204,255,255)
static IMChatController* m_vController = NULL;

IMChatController::IMChatController(std::string ID):message(NULL)
{
	id = ID.c_str();
}

IMChatController::~IMChatController()
{
	if (m_vController)
	{
		delete m_vController;
	}
	m_vController = NULL;
}

IMChatController* IMChatController::create(std::string _id)
{
	if (m_vController == NULL)
	{
		m_vController = new IMChatController(_id);
	}
	return m_vController;
}

void IMChatController::viewDidLoad()
{
		
	// Do any additional setup after loading the view from its nib.
	size = this->getView()->getBounds().size;

	p_TableView = CATableView::createWithCenter(CADipRect(size.width*0.5, size.height*0.5, size.width, size.height));
	p_TableView->setTableViewDataSource(this);
	p_TableView->setTableViewDelegate(this);
	//p_TableView->setAllowsSelection(true);
	//p_TableView->setAllowsMultipleSelection(true);s
	//p_TableView->setSeparatorColor(CAColor_clear);
	
	//chinahypo 2015-3-19
	message = HXSDKController::getInstance()->loadMessage(id);
	this->getView()->addSubview(p_TableView);
}

void IMChatController::viewDidUnload()
{
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
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
	sprintf(time,"%f",message.at(row)->m_vTime);
	timeLast = time;
	cell->setMsgTime(timeLast);
	if (message.at(row)->m_vReceive == id)
	{
		dpos = "left";
	}
	else
	{
		dpos = "right";
	}
	cell->showTextMsg(message.at(row)->m_vMessage, dpos.c_str());
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

	// 解析出来的信息//测试
	string strTime = "14:11:13";
	bool isMe = false;
	bool isImg = true;
	string msg = UTF8("测是发生法律思考");
	string url = "http://v1.qzone.cc/avatar/201503/16/11/40/550650944b939553.jpg!200x200.jpg";

	switch (row)
	{
	case 0:
		strTime = "14:12:13";
		isMe = false;
		isImg = false;
		msg = UTF8("测是发生法律思考");
		break;
	case 1:
		strTime = "14:15:13";
		isMe = false;
		isImg = false;
		msg = UTF8("测是发生法律思考长文字长文字长文字长文字长文字长文字长文字长文字长文字长文字长文字长文字长文字测");
		break;
	case 2:
		strTime = "14:16:13";
		isMe = true;
		isImg = false;
		msg = UTF8("这里是短文字测试");
		break;
	case 3:
		strTime = "14:17:13";
		isMe = true;
		isImg = false;
		msg = UTF8("这里是长文字测试长文字测试长文字测试长文字测试长文字测试长文字测试长文字测试长文字测试长文字测试");
		break;
	case 4:
		strTime = "14:18:13";
		isMe = false;
		isImg = true;
		url = "http://v1.qzone.cc/avatar/201503/16/11/40/550650944b939553.jpg!200x200.jpg";
		break;
	case 5:
		strTime = "14:19:13";
		isMe = true;
		isImg = true;
		url = "http://image.tianjimedia.com/uploadImages/2015/075/36/070VNM8X3GOY_680x500.jpg";
		break;
	case 6:
		strTime = "14:20:13";
		isMe = false;
		isImg = true;
		url = "http://image.tianjimedia.com/uploadImages/2015/013/23/F0JR9H8ZQNV3_680x500.jpg";
		break;
	case 7:
		strTime = "14:22:13";
		isMe = true;
		isImg = true;
		url = "http://image.tianjimedia.com/uploadImages/2015/013/25/C180F327382R_680x500.jpg";
		break;
	case 8:
		strTime = "14:23:13";
		isMe = false;
		isImg = true;
		url = "http://p2.qqyou.com/touxiang/UploadPic/2015-3/14/2015031419352215649.jpg";
		break;
	case 9:
		strTime = "14:24:13";
		isMe = true;
		isImg = true;
		url = "http://p2.qqyou.com/touxiang/UploadPic/2015-3/14/2015031422443329053.jpg";
		break;
	case 10:
		loaded = true;
		break;
	default:
		break;
	}
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
// 
// CAView* FirstViewController::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
// {
// 	CAView* view = CAView::createWithColor(CAColor_gray);
// 
// 
// 	return view;
// }

unsigned int IMChatController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	return message.size();
}

unsigned int IMChatController::numberOfSections(CATableView *table)
{
	return 1;
}

unsigned int IMChatController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	return _px(260);
}


unsigned int IMChatController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
	return _px(50);
}

unsigned int IMChatController::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
{
	return 1;
}