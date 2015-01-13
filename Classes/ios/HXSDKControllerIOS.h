#ifndef __HelloCpp__HXSDKControllerIOS__
#define __HelloCpp__HXSDKControllerIOS__

#include <iostream>
#include "CrossApp.h"


class HXSDKControllerIOS
{
    
public:
    
    HXSDKControllerIOS();
    
    virtual ~HXSDKControllerIOS();
    
    //HXSDKControllerIOS* getInstance();
    
    static bool init_ios();
    
    static bool Login_ios(const char* name, const char* passWord);
    
    static bool RegisTerAccount_ios(const char* name, const char* passWord);
    
    static void Logout_ios();
    
    static void sendMessage_ios(const char* messageText, const char* toUserName);
    
    static void sendMessageWithImage_ios(const char* messageImage, const char* toUserName);
    
protected:
    
};


#endif /* defined(__HelloCpp__HXSDKControllerIOS__) */
