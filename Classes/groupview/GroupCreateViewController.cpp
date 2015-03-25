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
//        TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_31).c_str()
        CANavigationBarItem* navigation = CANavigationBarItem::create(UTF8("创建群"));
        
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
    
    
    CAView* _memberView = CAView::createWithFrame(CCRect(0, _headCC.size.height+40, winRect.size.width, 113));
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
    
    scrollView->addSubview(_memberView);
    
    
    CAView * _limitView = CAView::createWithFrame(CCRect(0,750, winRect.size.width, 111));
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
    
    CAView* _noticeView = CAView::createWithFrame(CCRect(0,902, winRect.size.width, 113));
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
    
    scrollView->addSubview(_noticeView);
    
    
    m_btnCreate = CAButton::createWithFrame(CCRect(_px(40), 1460, winRect.size.width-_px(80), 110), CAButtonTypeRoundedRect);
//    , TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_25).c_str()
    m_btnCreate->setTitleForState(CAControlStateAll,UTF8("创建群"));
    CAImage * btnBG = CAImage::create(BUTTON_JOIN_GROUP );
    CAImageView * imgView = CAImageView::create();
    imgView->setImage(btnBG);
    m_btnCreate->setBackGroundViewForState(CAControlStateAll,imgView);
    m_btnCreate->setTitleColorForState(CAControlStateAll, CAColor_white);
    m_btnCreate->addTarget(this, CAControl_selector(GroupCreateViewController::onCreateBtn), CAControlEventTouchUpInSide);
    
    scrollView->addSubview(m_btnCreate);
    
    scrollView->setViewSize(CCSize(winRect.size.width,1737));
    this->getView()->addSubview(scrollView);
}

void GroupCreateViewController::viewDidUnLoad()
{
    
}

void GroupCreateViewController::onCreateBtn(CrossApp::CAControl *pTarget, CrossApp::CCPoint point)
{
    const char* gName = m_LabelTopic->getText().c_str();
    const char* gDescription = m_LabelIntroduce->getText().c_str();
    HXSDKController::getInstance()->createGroup(eHXSDKGroupStyle_PublicJoinNeedApproval, gName, gDescription);
    
}

