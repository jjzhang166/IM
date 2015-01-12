
#ifndef __HelloCpp__ViewController__
#define __HelloCpp__ViewController__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class FirstViewController: public CAViewController
{
    
public:

	FirstViewController();
    
	virtual ~FirstViewController();
    
    virtual bool init();
protected:
    
    virtual void viewDidLoad();
    
    virtual void viewDidUnload();
    
    virtual void viewDidAppear();
    
    void onButtonSegmented(CAControl* control, CCPoint point);
    /*
    void onButtonPopular(CAControl* control, CCPoint point);//热门按钮回调
    
    void onButtonNew(CAControl* control, CCPoint point);//最新按钮回调
    */
    void onButtonSearch(CAControl* control, CCPoint point);//搜索按钮回调
    
    void onButtonAdd(CAControl* control, CCPoint point);//添加按钮回调
protected:
    CANavigationBarItem* m_pNavigationBarItem;
    
    CASegmentedControl* m_pTitleView;
};


#endif /* defined(__HelloCpp__ViewController__) */
