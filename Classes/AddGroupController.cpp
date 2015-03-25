//
//  AddGroupController.h
//  IM
//
//  Created by qiaoxin on 15-3-25.
//
//

#include "AddGroupController.h"
#include "CrossApp.h"
#include "RootWindow.h"
#include "IMDATA.h"
#include "HXSDKController.h"
#include "AddHeadForgrand.h"
#include "data/TableLanguage.h"
#include "table/TableLanguagesfontnewHeader.h"
#include "IMTableCell.h"


AddGroupController::AddGroupController()
:m_winSize(CCSizeZero)
{
    
}

AddGroupController::~AddGroupController()
{
    
}

AddGroupController* AddGroupController::create()
{
    AddGroupController* controller = new AddGroupController();
    if(controller->init())
    {
        controller->autorelease();
        return controller;
    }
    return false;
}

bool AddGroupController::init()
{
    if (CAViewController::init()) {
        CABarButtonItem* backItem = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LOGOUT).c_str(), NULL, NULL);
        backItem->setTarget(this, CAControl_selector(AddGroupController::onButtonBack));
        CANavigationBarItem* navigation = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_25).c_str());
        navigation->setShowGoBackButton(false);
        navigation->addLeftButtonItem(backItem);
        setNavigationBarItem(navigation);
        return true;
    }
    return false;
}

void AddGroupController::viewDidLoad()
{
    m_winSize = this->getView()->getBounds().size;

    CAScale9ImageView* searchBackground = CAScale9ImageView::createWithImage(CAImage::create(TABLE_GRAY_BG));
    searchBackground->setFrame(CADipRect(0.0f, 0.0f, m_winSize.width, m_winSize.height));
    this->getView()->addSubview(searchBackground);
    
    m_pNameTextField = CATextField::createWithFrame(CADipRect(20.0f, 10.0F, m_winSize.width-40.0f, 50.0f));
    m_pNameTextField->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_11).c_str());
    m_pNameTextField->setSpaceHolderColor(ccc4(0x96, 0x96, 0x96, 0xff));
    m_pNameTextField->setFontSize(_px(28.0f));
    m_pNameTextField->setDelegate(this);
    m_pNameTextField->setKeyboardReturnType(KEY_BOARD_RETURN_SEARCH);
    this->getView()->addSubview(m_pNameTextField);
    
    m_pMessageTextField = CATextField::createWithFrame(CADipRect(20.0f, 70.0F, m_winSize.width-40.0f, 150.0f));
    m_pMessageTextField->setPlaceHolder(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_49).c_str());
    m_pMessageTextField->setSpaceHolderColor(ccc4(0x96, 0x96, 0x96, 0xff));
    m_pMessageTextField->setFontSize(_px(28.0f));
    m_pMessageTextField->setDelegate(this);
    m_pMessageTextField->setKeyboardReturnType(KEY_BOARD_RETURN_SEARCH);
    this->getView()->addSubview(m_pMessageTextField);
    
    CAButton* addButton = CAButton::createWithFrame(CADipRect(70, 250, m_winSize.width-140.0f, 90.0f), CAButtonTypeRoundedRect);
    addButton->setTitleForState(CAControlStateAll, TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_25).c_str());
    addButton->setBackGroundViewForState(CAControlStateAll,CAImageView::createWithImage(CAImage::create(BUTTON_JOIN_GROUP)));
    addButton->setTitleColorForState(CAControlStateAll, CAColor_white);
    addButton->addTarget(this, CAControl_selector(AddGroupController::onButtonAddGroup), CAControlTouchUpInSide);
    this->getView()->addSubview(addButton);
}

void AddGroupController::viewDidUnLoad()
{

}

#pragma mark TextFieldDelegate

bool AddGroupController::onTextFieldAttachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool AddGroupController::onTextFieldDetachWithIME(CATextField * sender)
{
    CC_UNUSED_PARAM(sender);
    
    return false;
}

bool AddGroupController::onTextFieldInsertText(CATextField * sender, const char * text, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(text);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

bool AddGroupController::onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(delText);
    CC_UNUSED_PARAM(nLen);
    
    return false;
}

// 返回按钮
void AddGroupController:: onButtonBack(CAControl* target, CCPoint point)
{
    RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(this);
}

void AddGroupController:: onButtonAddGroup(CAControl* target, CCPoint point)
{
    HXSDKController::getInstance()->joinNoNeedCheckGroup(m_pNameTextField->getText().c_str());
    RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(this);
}

