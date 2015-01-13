
#include "HXSDKController.h"
#include "IMDATA.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "HXSDKControllerIOS.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#endif

static HXSDKController* HXsdkController = NULL;

HXSDKController::HXSDKController()
{
    
}

HXSDKController::~HXSDKController()
{
    CC_SAFE_DELETE(HXsdkController);
}

HXSDKController* HXSDKController::getInstance()
{
    if(!HXsdkController)
    {
        HXsdkController = new HXSDKController();
        if(HXsdkController->initSDK())
        {
            CCLog("HXSDK init success!!!");
            return HXsdkController;
        }
    }
    CCLog("HXSDK init fail!!!");
    return NULL;
}

/*初始化sdk*/
bool HXSDKController::initSDK()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return (HXSDKControllerIOS::init_ios());
    
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    return true;
#endif
    
    return true;
}

void HXSDKController::LoginBefore(CrossApp::CAObject *target, SEL_CallFuncO selector,CrossApp::CAObject *obj)
{
    CANotificationCenter::sharedNotificationCenter()->addObserver(target, selector, KNOTIFICATION_LOGINCHANGE, obj);
}

void HXSDKController::Login(const char* name, const char* passWord)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::Login_ios(name, passWord);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
#endif
}

void HXSDKController::RegisterAccount(const char* name, const char* passWord)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::RegisTerAccount_ios(name, passWord);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
#endif
}

void HXSDKController::Logout()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    HXSDKControllerIOS::Logout_ios();
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
#endif
}

void HXSDKController::sendMessage(const char *messageText, const char *toUserName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //HXSDKControllerIOS::sendMessage_ios(messageText, toUserName);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
#endif
}
 
 void HXSDKController::sendMessageWithImage(const char *messageText, const char *toUserName)
 {
 #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
 //HXSDKControllerIOS::sendMessageWithImage_ios(messageText, toUserName);
 
 #elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
 
 #endif
 }






























