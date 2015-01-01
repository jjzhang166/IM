
#ifndef __SECOND_VIEW_CONTROLLER__
#define __SECOND_VIEW_CONTROLLER__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class SecondViewController: public CAViewController
{
    
public:

	SecondViewController();
    
	virtual ~SecondViewController();
    
    virtual bool init();
protected:
    
    virtual void viewDidLoad();
    
    virtual void viewDidUnload();
    
    virtual void viewDidAppear();
        
    void onButtonSearch(CAControl* control, CCPoint point);//搜索按钮回调
    
    void onButtonAdd(CAControl* control, CCPoint point);//添加按钮回调
    
};


#endif /* defined(__SECOND_VIEW_CONTROLLER__) */
