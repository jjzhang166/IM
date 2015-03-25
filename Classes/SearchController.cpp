//
//  SearchController.h
//  IM
//
//  Created by qiaoxin on 15-3-23.
//
//

#include "SearchController.h"
#include "CrossApp.h"
#include "RootWindow.h"
#include "IMDATA.h"
#include "HXSDKController.h"
#include "AddHeadForgrand.h"
#include "data/TableLanguage.h"
#include "table/TableLanguagesfontnewHeader.h"
#include "IMTableCell.h"


SearchController::SearchController()
:m_winSize(CCSizeZero)
{
    
}

SearchController::~SearchController()
{
    
}

SearchController* SearchController::create()
{
    SearchController* controller = new SearchController();
    if(controller->init())
    {
        controller->autorelease();
        return controller;
    }
    return false;
}

bool SearchController::init()
{
    if (CAViewController::init()) {
        CABarButtonItem* backItem = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LOGOUT).c_str(), NULL, NULL);
        backItem->setTarget(this, CAControl_selector(SearchController::onButtonBack));
        CANavigationBarItem* navigation = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_SEARCH_CONTENT_TEXT).c_str());
        navigation->setShowGoBackButton(false);
        navigation->addLeftButtonItem(backItem);
        setNavigationBarItem(navigation);
        return true;
    }
    return false;
}

void SearchController::viewDidLoad()
{
    m_winSize = this->getView()->getBounds().size;
    
    CATableView* tableView = CATableView::createWithCenter(CCRect(m_winSize.width*0.5, m_winSize.height*0.5, m_winSize.width, m_winSize.height));
    tableView->setTableViewDataSource(this);
    tableView->setTableViewDelegate(this);
    tableView->setAllowsSelection(true);
    this->getView()->addSubview(tableView);

    init_searchBar();
}

void SearchController::init_searchBar()
{
    CAScale9ImageView* searchBackground = CAScale9ImageView::createWithImage(CAImage::create(TABLE_GRAY_BG));
    searchBackground->setFrame(CADipRect(0.0f, 0.0f, m_winSize.width, 75.0f));
    this->getView()->insertSubview(searchBackground, 10);
    
    m_pSearchTextField = CATextField::createWithFrame(CADipRect(20.0f, 10.0F, m_winSize.width-40.0f, 50.0f));
    m_pSearchTextField->setBackgroundView(CAView::createWithColor(CAColor_white));
    m_pSearchTextField->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_SEARCH_CONTENT_TEXT).c_str());
    m_pSearchTextField->setSpaceHolderColor(ccc4(0x96, 0x96, 0x96, 0xff));
    m_pSearchTextField->setFontSize(_px(28.0f));
    m_pSearchTextField->setDelegate(this);
    m_pSearchTextField->setKeyboardReturnType(KEY_BOARD_RETURN_SEARCH);
    searchBackground->addSubview(m_pSearchTextField);
    
}

void SearchController::viewDidUnLoad()
{

}


void SearchController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    //cell点击处理事件
}

void SearchController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* SearchController::tableCellAtIndex(CATableView* table, const CCSize& cellsize, unsigned int section, unsigned int row)
{
    /*cell页面的初始化*/
    cell = table->dequeueReusableCellWithIdentifier("Crossapp");
    CCSize cellSize = CCSizeMake(m_winSize.width, _px(90));
    if(cell == NULL)
    {
        cell = IMTableCell::create(Friend, cellSize);
    }
   
    return cell;
}

/*在section之间添加一个view，就是UI中section之间的灰色地带*/
CAView* SearchController::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    CAView* view = CAView::createWithColor(ccc4(230, 230, 230, 255));
    return view;
}

/*设置每个section含有的cell个数*/
unsigned int SearchController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    return 1;
}

/*设置含有几个section*/
unsigned int SearchController::numberOfSections(CATableView *table)
{
    return 1;
}

unsigned int SearchController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{	/*section的大小设置*/
    return 1;
}

unsigned int SearchController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    return 0;
}

#pragma mark TextFieldDelegate

bool SearchController::onTextFieldAttachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool SearchController::onTextFieldDetachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool SearchController::onTextFieldInsertText(CATextField * sender, const char * text, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(text);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

bool SearchController::onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(delText);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

// 返回按钮
void SearchController:: onButtonBack(CAControl* target, CCPoint point)
{
    RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(this);
    
}
