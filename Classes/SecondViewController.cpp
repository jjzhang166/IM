#include "SecondViewController.h"
#include "IMDATA.h"
#include "groupview/GroupInfoViewController.h"
#include "RootWindow.h"
#include "HXSDKController.h"
#include "table/TableLanguagesfontnewHeader.h"
#include "data/TableLanguage.h"
#include "IMTableCell.h"


using namespace CrossApp;

SecondViewController::SecondViewController()
{
    
    
}

SecondViewController::~SecondViewController()
{
    CC_SAFE_RELEASE(m_pNavigationBarItem);
}

bool SecondViewController::init()
{
    if (CAViewController::init())
    {
        CABarButtonItem* addButtonItem = CABarButtonItem::create("", CAImage::create(NAVIGATION_BAR_ITEM_ADD_NORMAL), CAImage::create(NAVIGATION_BAR_ITEM_ADD_SELECTED));
        addButtonItem->setTarget(this, CAControl_selector(SecondViewController::onButtonAdd));
        
        m_pNavigationBarItem = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_NAVIGATION_BAR_ITEM_NAME_2).c_str());
        m_pNavigationBarItem->setShowGoBackButton(false);
        m_pNavigationBarItem->addRightButtonItem(addButtonItem);
        
        m_pNavigationBarItem->retain();
        
        return true;
    }
    return false;
}

void SecondViewController::viewDidLoad()
{
    init_searchBar();
    
    CCRect winRect = this->getView()->getBounds();
    size = this->getView()->getBounds().size;
    m_pWinSize = this->getView()->getBounds().size;
    
    m_pTableView = CATableView::createWithCenter(CCRect(m_pWinSize.width*0.5, m_pWinSize.height*0.5f + 75.0F*0.5f, m_pWinSize.width, m_pWinSize.height - 75.0F));
    m_pTableView->setTableViewDataSource(this);
    m_pTableView->setTableViewDelegate(this);
    m_pTableView->setAllowsSelection(true);
    this->getView()->addSubview(m_pTableView);
}
void SecondViewController::init_searchBar()
{
    CADipSize size = this->getView()->getBounds().size;

    CAScale9ImageView* searchBackground = CAScale9ImageView::createWithImage(CAImage::create(TABLE_GRAY_BG));
    searchBackground->setFrame(CADipRect(0.0f, 0.0f, size.width, 75.0f));
    this->getView()->insertSubview(searchBackground, 10);
    
    m_pSearchTextField = CATextField::createWithFrame(CADipRect(20.0f, 10.0F, size.width-40.0f, 50.0f));
    m_pSearchTextField->setBackgroundView(CAView::createWithColor(CAColor_white));
    m_pSearchTextField->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_SEARCH_CONTENT_TEXT).c_str());
    m_pSearchTextField->setSpaceHolderColor(ccc4(0x96, 0x96, 0x96, 0xff));
    m_pSearchTextField->setFontSize(_px(28.0f));
    m_pSearchTextField->setDelegate(this);
    m_pSearchTextField->setKeyboardReturnType(KEY_BOARD_RETURN_SEARCH);
    searchBackground->addSubview(m_pSearchTextField);
}

void SecondViewController::init_searchResultTable()
{

}

void SecondViewController::viewDidAppear()
{
    this->getTabBarController()->setNavigationBarItem(m_pNavigationBarItem);
}

void SecondViewController::viewDidUnload()
{
    
}

void SecondViewController::onButtonAdd(CAControl* control, CCPoint point)
{

}


#pragma mark TextFieldDelegate

bool SecondViewController::onTextFieldAttachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool SecondViewController::onTextFieldDetachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool SecondViewController::onTextFieldInsertText(CATextField * sender, const char * text, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(text);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

bool SecondViewController::onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(delText);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

#pragma mark CATableViewDelegate
void SecondViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{

}

void SecondViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* SecondViewController::tableCellAtIndex(CATableView* table, const CCSize& cellsize, unsigned int section, unsigned int row)
{
    cell = table->dequeueReusableCellWithIdentifier("Crossapp");
    CCSize cellSize = CCSizeMake(m_pWinSize.width, _px(90));
    switch (section)
    {
        case 0:
        {
            cell = IMTableCell::create(Group, cellSize);
            ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), "", "");
            return cell;
            break;
        }
        case 1:
        {
            cell = IMTableCell::create(Friend, cellSize);
            ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), "", "");
            return cell;
            break;
        }
        case 2:
        {
            cell = IMTableCell::create(Strange, cellSize);
            ((IMTableCell*)cell)->setCellInfo(CAImage::create("IMResources/button_photo Album_normal.png"), "", "");
            return cell;
            break;
        }
        default:
            break;
    }
}

CAView* SecondViewController::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    CAView* view = CAView::createWithFrame(CADipRect(0, 0, m_pWinSize.width, 25.0f), ccc4(230, 230, 230, 255));
    return view;
}


unsigned int SecondViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    return 1;
}


unsigned int SecondViewController::numberOfSections(CATableView *table)
{
    return 3;
}

unsigned int SecondViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{	
    
    return _px(90);
}

unsigned int SecondViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    return _px(5);
}