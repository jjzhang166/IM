//
//  HomeTabBarController.h
//  BabyGenius
//
//  Created by 栗元峰 on 14-9-5.
//
//

#ifndef __BabyGenius__HomeTabBarController__
#define __BabyGenius__HomeTabBarController__

#include <iostream>
#include "CrossApp.h"

class HomeTabBarController: public CATabBarController
{
    
public:
    
    HomeTabBarController();
    
    virtual ~HomeTabBarController();
    
    bool initWithTabBarController();
    
    virtual void viewDidLoad();
    
    virtual void viewDidAppear();
    
    virtual void viewDidDisappear();
    
protected:
    
    void onButton(CAControl* control, CCPoint point);
    
    virtual void tabBarSelectedItem(CATabBar* tabBar, CATabBarItem* item, unsigned int index);

    virtual void tabBarClickToForbidSelectedItem(CATabBar* tabBar, CATabBarItem* item, unsigned int index);
    
    virtual void getSelectedImage(CAImage *image);
    
    CATabBar* m_pNewTabBar;
    
};


#endif /* defined(__BabyGenius__HomeTabBarController__) */
