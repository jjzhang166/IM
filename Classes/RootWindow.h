

#ifndef __HelloCpp__RootWindow__
#define __HelloCpp__RootWindow__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class RootWindow: public CAWindow
{
    
public:

	static RootWindow* getInstance();
    
	RootWindow();
    
	virtual ~RootWindow();
    
    virtual bool init();
    
    CANavigationController* getNavigationController();

protected:
    CATabBarController*  init_tabelBarController();
    
    CANavigationController* init_navigationController(CATabBarController* tableBarController);
    
protected:
    CATabBarController* m_pTabelBarController;
    
    CANavigationController* m_pNavigationController;
    
};


#endif /* defined(__HelloCpp__ViewController__) */
