//
//  GroupCreateViewController.cpp
//  IM
//
//  Created by lhj on 15/3/23.
//
//

#include "GroupCreateViewController.h"
#include "CrossApp.h"
#include "RootWindow.h"
#include "IMDATA.h"
#include "HXSDKController.h"
#include "AddHeadForgrand.h"
#include "../data/TableLanguage.h"
#include "../table/TableLanguagesfontnewHeader.h"



GroupCreateViewController::GroupCreateViewController()
{
    
}
GroupCreateViewController::~GroupCreateViewController()
{
    
}

GroupCreateViewController* GroupCreateViewController::create()
{
    GroupCreateViewController* controller = new GroupCreateViewController();
    controller->init();
    controller->autorelease();
    return controller;
}

bool GroupCreateViewController::init()
{
    if (CAViewController::init()) {
        CABarButtonItem* backItem = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LOGOUT).c_str(), NULL, NULL);
        backItem->setTarget(this, CAControl_selector(GroupCreateViewController::onButtonBack));
        CANavigationBarItem* navigation = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_26).c_str());
        navigation->setShowGoBackButton(false);
        navigation->addLeftButtonItem(backItem);
        setNavigationBarItem(navigation);
        return true;
    }
    return false;
}

void GroupCreateViewController::viewDidLoad()
{
    CCRect winRect = this->getView()->getBounds();
    
    CAScrollView * scrollView = CAScrollView::createWithFrame(CCRect(0, 0, winRect.size.width, winRect.size.height));
    scrollView->setBackGroundColor(ccc4(240, 240, 240, 255));
    scrollView->setBounceHorizontal(false);
    scrollView->setTouchMovedListenHorizontal(false);
    scrollView->setShowsHorizontalScrollIndicator(false);
    
    CAView* _headView = CAView::createWithFrame(CCRect(0, 0, winRect.size.width, 562), CAColor_white);
    CCRect _headCC = _headView->getBounds() ;
    m_imgViewHead = CAImageView::createWithCenter(CCRect(_headCC.size.width/2, 166, 150, 150));
    m_imgViewHead->setImage(CAImage::create(GROUP));
    _headView->addSubview(m_imgViewHead);
    
    AddHeadForgrand::getInstance()->addHeadForgrand(m_imgViewHead);
    
    CAView* _lineView = CAView::createWithFrame(CCRect(_px(40), 336, winRect.size.width-_px(80), _px(1)), ccc4(200, 200, 200, 255));
    _headView->addSubview(_lineView);
    
    CALabel* topicLabel = CALabel::createWithFrame(CCRect(_px(45),372, 80, 39));
    topicLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_32).c_str());
    topicLabel->setFontSize(_px(38));
    topicLabel->setColor(ccc4(112, 112, 112, 255));
    _headView->addSubview(topicLabel);
    
    m_LabelTopic = CATextField::createWithFrame(CCRect(240, 365, 320, 60));
//    m_LabelTopic->setText(m_info.m_sTopic);
    m_LabelTopic->setFontSize(_px(38));
    m_LabelTopic->setColor(ccc4(51, 51, 51, 255));
    _headView->addSubview(m_LabelTopic);
    
    CAView* _lineView2 = CAView::createWithFrame(CCRect(_px(40), 450, winRect.size.width-_px(80), _px(1)), ccc4(200, 200, 200, 255));
    _headView->addSubview(_lineView2);
    
    CALabel * introduceLabel = CALabel::createWithFrame(CCRect(_px(45),490, 80, 39));
    introduceLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_33).c_str());
    introduceLabel->setFontSize(_px(38));
    introduceLabel->setColor(ccc4(112, 112, 112, 255));
    _headView->addSubview(introduceLabel);
    
    m_LabelIntroduce = CATextField::createWithFrame(CCRect(240, 482, 320, 60));
//    m_LabelIntroduce->setText(m_info.m_sIntroduce);
    m_LabelIntroduce->setFontSize(_px(38));
    m_LabelIntroduce->setColor(ccc4(51, 51, 51, 255));
    _headView->addSubview(m_LabelIntroduce);
    
    scrollView->addSubview(_headView);
    
    
    CAView* _memberView = CAView::createWithFrame(CCRect(0, _headCC.size.height+40, winRect.size.width, 226));
    _memberView->setColor(CAColor_white);
    
    CALabel* ownerLabel = CALabel::createWithFrame(CCRect(_px(40), 40, 80, 39));
    ownerLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_34).c_str());
    ownerLabel->setColor(ccc4(112, 112, 112, 255));
    ownerLabel->setFontSize(_px(38));
    _memberView->addSubview(ownerLabel);
    
    m_LabelOwner = CALabel::createWithFrame(CCRect(240, 40, 200, 39));
    m_LabelOwner->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_34).c_str());
    m_LabelOwner->setText(HXSDKController::getInstance()->getMyName());
    m_LabelOwner->setColor(ccc4(51, 51, 51, 255));
    m_LabelOwner->setFontSize(_px(38));
    _memberView->addSubview(m_LabelOwner);
    
    
    CAView* _lineView3 = CAView::createWithFrame(CCRect(_px(40), 111, winRect.size.width-_px(80), _px(1)), ccc4(200, 200, 200, 255));
    _memberView->addSubview(_lineView3);
    
    CALabel* memberLabel = CALabel::createWithFrame(CCRect(_px(40), 152, 80, 39));
    memberLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_35).c_str());
    memberLabel->setColor(ccc4(112, 112, 112, 255));
    memberLabel->setFontSize(_px(38));
    _memberView->addSubview(memberLabel);
    
    m_LabelMember = CALabel::createWithFrame(CCRect(240, 152, 200, 39));
//    m_LabelMember->setText( CCString::createWithFormat("%d人",m_info.m_itotal)->getCString());
    m_LabelMember->setColor(ccc4(51, 51, 51, 255));
    m_LabelMember->setFontSize(_px(38));
    _memberView->addSubview(m_LabelMember);
    
    
    scrollView->addSubview(_memberView);
    
    
    CAView * _limitView = CAView::createWithFrame(CCRect(0,863, winRect.size.width, 111));
    _limitView->setColor(CAColor_white);
    
    CALabel* limitLabel = CALabel::createWithFrame(CCRect(_px(40), 40, 200, 39));
    limitLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_36).c_str());
    limitLabel->setColor(ccc4(112, 112, 112, 255));
    limitLabel->setFontSize(_px(38));
    _limitView->addSubview(limitLabel);
    
    m_LabelLimit = CALabel::createWithFrame(CCRect(240, 40, 400, 39));
//    m_LabelLimit->setText(m_info.m_sLimit);
    m_LabelLimit->setColor(ccc4(51, 51, 51, 255));
    m_LabelLimit->setFontSize(_px(38));
    _limitView->addSubview(m_LabelLimit);
    
    scrollView->addSubview(_limitView);
    
    CAView* _noticeView = CAView::createWithFrame(CCRect(0,1015, winRect.size.width, 226));
    _noticeView->setColor(CAColor_white);
    
    CALabel* noticeLabel = CALabel::createWithFrame(CCRect(_px(40), 40, 200, 39));
    noticeLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_37).c_str());
    noticeLabel->setColor(ccc4(51, 51, 51, 255));
    noticeLabel->setFontSize(_px(38));
    _noticeView->addSubview(noticeLabel);
    
    m_SwitchNotice = CASwitch::createWithFrame(CCRect(winRect.size.width - 171, 23, 130, 80));
    //    m_SwitchNotice->setOnImage(CAImage::create(SWITCH_ON));
    //    m_SwitchNotice->setOffImage(CAImage::create(SWITCH_OFF));
//    m_SwitchNotice->setIsOn(m_info.m_bIsNotice, true);
    _noticeView->addSubview(m_SwitchNotice);
    
    CAView* _lineView4 = CAView::createWithFrame(CCRect(_px(40), 111, winRect.size.width-_px(80), _px(1)), ccc4(200, 200, 200, 255));
    _noticeView->addSubview(_lineView4);
    
    CALabel* gmemberLabel = CALabel::createWithFrame(CCRect(_px(40), 152, 150, 39));
    gmemberLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_38).c_str());
    gmemberLabel->setColor(ccc4(51, 51, 51, 255));
    gmemberLabel->setFontSize(_px(38));
    _noticeView->addSubview(gmemberLabel);
    
    scrollView->addSubview(_noticeView);
    
    
    m_ExitButton = CAButton::createWithFrame(CCRect(_px(40), 1572, winRect.size.width-_px(80), 110), CAButtonTypeRoundedRect);
//    , TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_25).c_str()
    m_ExitButton->setTitleForState(CAControlStateAll,TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_26).c_str());
    CAImage * btnBG = CAImage::create(BUTTON_JOIN_GROUP );
    CAImageView * imgView = CAImageView::create();
    imgView->setImage(btnBG);
    m_ExitButton->setBackGroundViewForState(CAControlStateAll,imgView);
    m_ExitButton->setTitleColorForState(CAControlStateAll, CAColor_white);
    
    scrollView->addSubview(m_ExitButton);
    
    scrollView->setViewSize(CCSize(winRect.size.width,1737));
    this->getView()->addSubview(scrollView);
}

void GroupCreateViewController::viewDidUnLoad()
{
    
}

void GroupCreateViewController::onCreateBtn(CrossApp::CAControl *pTarget, CrossApp::CCPoint point)
{
    
}

void GroupCreateViewController::onButtonBack(CAControl* control, CCPoint point)
{
    RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(this);
}
