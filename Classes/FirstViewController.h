
#ifndef __HelloCpp__ViewController__
#define __HelloCpp__ViewController__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class FirstViewController: public CAViewController, public CATextFieldDelegate
{
    
public:

	FirstViewController();
    
	virtual ~FirstViewController();
    
    virtual bool init();
protected:
    
    virtual void viewDidLoad();
    
    virtual void viewDidUnload();
    
    virtual void viewDidAppear();
    
    void init_searchBar();
    
    void onButtonSegmented(CAControl* control, CCPoint point);
    /*
    void onButtonPopular(CAControl* control, CCPoint point);//热门按钮回调
    
    void onButtonNew(CAControl* control, CCPoint point);//最新按钮回调
    */
    void onButtonSearch(CAControl* control, CCPoint point);//搜索按钮回调
    
    void onButtonAdd(CAControl* control, CCPoint point);//添加按钮回调
    /*textFieldDelegate*/
    bool onTextFieldAttachWithIME(CATextField * sender);
    bool onTextFieldDetachWithIME(CATextField * sender);
    virtual bool onTextFieldInsertText(CATextField * sender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CATextField * sender, const char * delText, int nLen);
    
protected:
    CANavigationBarItem* m_pNavigationBarItem;
    
    CASegmentedControl* m_pTitleView;
    
    CATextField* m_pSearchTextField;
};


#endif /* defined(__HelloCpp__ViewController__) */
