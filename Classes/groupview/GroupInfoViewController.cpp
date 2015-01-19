//
//  GroupInfoViewController.cpp
//  IM
//
//  Created by chenq on 15-1-16.
//
//

#include "GroupInfoViewController.h"
#include "CrossApp.h"


GroupInfoViewController::GroupInfoViewController()
{
    
    
};

GroupInfoViewController::~GroupInfoViewController()
{

};


GroupInfoViewController* GroupInfoViewController::create()
{
    GroupInfoViewController* controller = new GroupInfoViewController();
    controller->init();
    
    controller->autorelease();
    return controller;
};

bool GroupInfoViewController::init()
{
    if (!CAViewController::init()) {
        
        return true;
    }

    return false;

};


void GroupInfoViewController::viewDidLoad()
{
    

};


void GroupInfoViewController::viewDidUnLoad()
{


};