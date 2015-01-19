//
//  GroupInfoViewController.h
//  IM
//
//  Created by chenq on 15-1-16.
//
//

#ifndef __IM__GroupInfoViewController__
#define __IM__GroupInfoViewController__

#include <iostream>
#include "crossApp.h"

USING_NS_CC;

class GroupInfoViewController : public CAViewController
{
    public :
    
    GroupInfoViewController();
    virtual ~GroupInfoViewController();
    
    static GroupInfoViewController* create();
    virtual bool init();
    
protected:
    void viewDidLoad();
    void viewDidUnLoad();
    
    
};

#endif /* defined(__IM__GroupInfoViewController__) */
