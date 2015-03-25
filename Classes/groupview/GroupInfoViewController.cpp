//
//  GroupInfoViewController.cpp
//  IM
//
//  Created by chenq on 15-1-16.
//
//

#include "GroupInfoViewController.h"
#include "CrossApp.h"
#include "RootWindow.h"
#include "IMDATA.h"
#include "HXSDKController.h"
#include "AddHeadForgrand.h"
#include "../data/TableLanguage.h"
#include "../table/TableLanguagesfontnewHeader.h"
#include "../groupview/GroupMembersController.h"


GroupInfoViewController::GroupInfoViewController()
{
    
}

GroupInfoViewController::~GroupInfoViewController()
{
    
}

GroupInfoViewController* GroupInfoViewController::create(GroupInfo info,bool joined)
{
    GroupInfoViewController* controller = new GroupInfoViewController();
    controller->init(info,joined);
    controller->autorelease();
    return controller;
}

bool GroupInfoViewController::init(GroupInfo info,bool joined)
{
    if (CAViewController::init()) {
        m_info = info ;
        m_joined = joined;
        
        CABarButtonItem* backItem = CABarButtonItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LOGOUT).c_str(), NULL, NULL);
        backItem->setTarget(this, CAControl_selector(GroupInfoViewController::onButtonBack));
        CANavigationBarItem* navigation = CANavigationBarItem::create(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_31).c_str());
        navigation->setShowGoBackButton(false);
        navigation->addLeftButtonItem(backItem);
        setNavigationBarItem(navigation);
        return true;
    }
    return false;
}

void GroupInfoViewController::viewDidLoad()
{
    CCRect winRect = this->getView()->getBounds();
    
    CAScrollView * scrollView = CAScrollView::createWithFrame(CCRect(0, 0, winRect.size.width, winRect.size.height));
    scrollView->setBackGroundColor(ccc4(240, 240, 240, 255));
    scrollView->setBounceHorizontal(false);
    scrollView->setTouchMovedListenHorizontal(false);
	scrollView->setShowsHorizontalScrollIndicator(false);

    CAView* headView = CAView::createWithFrame(CCRect(0, 0, winRect.size.width, 562), CAColor_white);
    CCRect headCC = headView->getBounds() ;
    m_imgViewHead = CAImageView::createWithCenter(CCRect(headCC.size.width/2, 166, 150, 150));
    m_imgViewHead->setImage(m_info.m_pFaceImg);
    headView->addSubview(m_imgViewHead);
    
    AddHeadForgrand::getInstance()->addHeadForgrand(m_imgViewHead);
    
    CAView* lineView = CAView::createWithFrame(CCRect(_px(40), 336, winRect.size.width-_px(80), _px(1)), ccc4(200, 200, 200, 255));
    headView->addSubview(lineView);
    
    CALabel* topicLabel = CALabel::createWithFrame(CCRect(_px(45),372, 80, 39));
    topicLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_32).c_str());
    topicLabel->setFontSize(_px(38));
    topicLabel->setColor(ccc4(112, 112, 112, 255));
    headView->addSubview(topicLabel);
    
    m_LabelTopic = CALabel::createWithFrame(CCRect(240, 372, 300, 39));
    m_LabelTopic->setText(m_info.m_sTopic);
    m_LabelTopic->setFontSize(_px(38));
    m_LabelTopic->setColor(ccc4(51, 51, 51, 255));
    headView->addSubview(m_LabelTopic);
  
    CAView* lineView2 = CAView::createWithFrame(CCRect(_px(40), 450, winRect.size.width-_px(80), _px(1)), ccc4(200, 200, 200, 255));
    headView->addSubview(lineView2);
    
    CALabel * introduceLabel = CALabel::createWithFrame(CCRect(_px(45),490, 80, 39));
    introduceLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_33).c_str());
    introduceLabel->setFontSize(_px(38));
    introduceLabel->setColor(ccc4(112, 112, 112, 255));
    headView->addSubview(introduceLabel);
    
    m_LabelIntroduce = CALabel::createWithFrame(CCRect(240, 490, 300, 39));
    m_LabelIntroduce->setText(m_info.m_sIntroduce);
    m_LabelIntroduce->setFontSize(_px(38));
    m_LabelIntroduce->setColor(ccc4(51, 51, 51, 255));
    headView->addSubview(m_LabelIntroduce);

    scrollView->addSubview(headView);

    
    CAView* memberView = CAView::createWithFrame(CCRect(0, headCC.size.height+40, winRect.size.width, 226));
    memberView->setColor(CAColor_white);
    
    CALabel* ownerLabel = CALabel::createWithFrame(CCRect(_px(40), 40, 80, 39));
    ownerLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_34).c_str());
    ownerLabel->setColor(ccc4(112, 112, 112, 255));
    ownerLabel->setFontSize(_px(38));
    memberView->addSubview(ownerLabel);
    
    m_LabelOwner = CALabel::createWithFrame(CCRect(240, 40, 200, 39));
    m_LabelOwner->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_34).c_str());
    m_LabelOwner->setText(m_info.m_sOwner);
    m_LabelOwner->setColor(ccc4(51, 51, 51, 255));
    m_LabelOwner->setFontSize(_px(38));
    memberView->addSubview(m_LabelOwner);
    
    
    CAView* _lineView3 = CAView::createWithFrame(CCRect(_px(40), 111, winRect.size.width-_px(80), _px(1)), ccc4(200, 200, 200, 255));
    memberView->addSubview(_lineView3);
    
    CALabel* memberLabel = CALabel::createWithFrame(CCRect(_px(40), 152, 80, 39));
    memberLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_35).c_str());
    memberLabel->setColor(ccc4(112, 112, 112, 255));
    memberLabel->setFontSize(_px(38));
    memberView->addSubview(memberLabel);
    
    m_LabelMember = CALabel::createWithFrame(CCRect(240, 152, 200, 39));
    m_LabelMember->setText( CCString::createWithFormat("%d人",m_info.m_itotal)->getCString());
    m_LabelMember->setColor(ccc4(51, 51, 51, 255));
    m_LabelMember->setFontSize(_px(38));
    memberView->addSubview(m_LabelMember);
    
    scrollView->addSubview(memberView);

    
    CAView * limitView = CAView::createWithFrame(CCRect(0,863, winRect.size.width, 111));
    limitView->setColor(CAColor_white);
    
    CALabel* limitLabel = CALabel::createWithFrame(CCRect(_px(40), 40, 200, 39));
    limitLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_36).c_str());
    limitLabel->setColor(ccc4(112, 112, 112, 255));
    limitLabel->setFontSize(_px(38));
    limitView->addSubview(limitLabel);
    
    m_LabelLimit = CALabel::createWithFrame(CCRect(240, 40, 400, 39));
    m_LabelLimit->setText(m_info.m_sLimit);
    m_LabelLimit->setColor(ccc4(51, 51, 51, 255));
    m_LabelLimit->setFontSize(_px(38));
    limitView->addSubview(m_LabelLimit);
    
    scrollView->addSubview(limitView);

    CAView* noticeView = CAView::createWithFrame(CCRect(0,1015, winRect.size.width, 226));
    noticeView->setColor(CAColor_white);
    
    CALabel* noticeLabel = CALabel::createWithFrame(CCRect(_px(40), 40, 200, 39));
    noticeLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_37).c_str());
    noticeLabel->setColor(ccc4(51, 51, 51, 255));
    noticeLabel->setFontSize(_px(38));
    noticeView->addSubview(noticeLabel);

    m_SwitchNotice = CASwitch::createWithFrame(CCRect(winRect.size.width - 171, 23, 130, 80));
    m_SwitchNotice->setIsOn(m_info.m_bIsNotice, true);
    noticeView->addSubview(m_SwitchNotice);
    
    CAView* _lineView4 = CAView::createWithFrame(CCRect(_px(40), 111, winRect.size.width-_px(80), _px(1)), ccc4(200, 200, 200, 255));
    noticeView->addSubview(_lineView4);
    
    CALabel* gmemberLabel = CALabel::createWithFrame(CCRect(_px(40), 152, 150, 39));
    gmemberLabel->setText(TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_38).c_str());
    gmemberLabel->setColor(ccc4(51, 51, 51, 255));
    gmemberLabel->setFontSize(_px(38));
    noticeView->addSubview(gmemberLabel);
    
    CAButton* groupMenbersButton = CAButton::createWithFrame(CCRect(0, 100, winRect.size.width, 110), CAButtonTypeRoundedRect);
    groupMenbersButton->setBackGroundViewForState(CAControlStateAll,CAImageView::createWithImage(CAImage::create("")));
    groupMenbersButton->addTarget(this, CAControl_selector(GroupInfoViewController::onButtonGroupMenbers), CAControlTouchUpInSide);
    noticeView->addSubview(groupMenbersButton);
    
    scrollView->addSubview(noticeView);

    
    m_ExitButton = CAButton::createWithFrame(CCRect(_px(40), 1572, winRect.size.width-_px(80), 110), CAButtonTypeRoundedRect);
    
    if(m_joined)
    {
        m_ExitButton->setTitleForState(CAControlStateAll, TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_41).c_str());
        CAImage * btnBG = CAImage::create(BUTTON_EXIT_GROUP );
        CAImageView * imgView = CAImageView::create();
        imgView->setImage(btnBG);
        m_ExitButton->setBackGroundViewForState(CAControlStateAll,imgView);
        m_ExitButton->addTarget(this, CAControl_selector(GroupInfoViewController::onButtonExit), CAControlTouchUpInSide);
    }
    else
    {
        m_ExitButton->setTitleForState(CAControlStateAll, TableLanguage::getInstance()->getTableItemByID(LANGUAGESFONTNEW_LANGUAGES_FONT_25).c_str());
        CAImage * btnBG = CAImage::create(BUTTON_JOIN_GROUP );
        CAImageView * imgView = CAImageView::create();
        imgView->setImage(btnBG);
        m_ExitButton->setBackGroundViewForState(CAControlStateAll,imgView);
        m_ExitButton->addTarget(this, CAControl_selector(GroupInfoViewController::onButtonJoin), CAControlTouchUpInSide);
    }
    m_ExitButton->setTitleColorForState(CAControlStateAll, CAColor_white);
    
    scrollView->addSubview(m_ExitButton);

    scrollView->setViewSize(CCSize(winRect.size.width,1737));
    this->getView()->addSubview(scrollView);
}

void GroupInfoViewController::viewDidUnLoad()
{

}

// 群成员按钮
void GroupInfoViewController::onButtonGroupMenbers(CAControl* target, CCPoint point)
{
    std::vector<HXSDKBuddy*> vMembers = HXSDKController::getInstance()->getGroupMemberListByID(m_info.m_sGroupID);
    GroupMembersController* memberController = GroupMembersController::create(vMembers);
    RootWindow::getInstance()->getNavigationController()->pushViewController(memberController, true);
}

// 返回按钮
void GroupInfoViewController:: onButtonBack(CAControl* target, CCPoint point)
{
    RootWindow::getInstance()->getNavigationController()->popViewControllerAnimated(this);
    
}

// 消息提醒
void GroupInfoViewController:: onSwitchChanged(CAControl* target, CCPoint point)
{
    
}

// 加入群按钮
void GroupInfoViewController:: onButtonJoin(CAControl* target, CCPoint point)
{
    HXSDKController::getInstance()->joinNoNeedCheckGroup( m_info.m_sGroupID.c_str());
}

// 退群按钮
void GroupInfoViewController:: onButtonExit(CAControl* target, CCPoint point)
{
    HXSDKController::getInstance()->exitGroup( m_info.m_sGroupID.c_str());
}
