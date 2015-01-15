//
//  HXSDKControllerAndroid.h
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-14.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#ifndef __HelloCpp__HXSDKControllerAndroid__
#define __HelloCpp__HXSDKControllerAndroid__

#include <iostream>
#include "CrossApp.h"


class HXSDKControllerAndroid
{
    
public:
    
    HXSDKControllerAndroid();
    
    virtual ~HXSDKControllerAndroid();
    
    //HXSDKControllerAndroid* getInstance();
    
    static bool init_android();
    
    static bool Login_android(const char* name, const char* passWord);
    
    static bool RegisTerAccount_android(const char* name, const char* passWord);
    
    static void Logout_android();
    
    static void sendMessage_android(const char* messageText, const char* toUserName);
    
    static void sendMessageWithImage_android(const char* messageImage, const char* toUserName);
    
protected:
    
};


#endif /* defined(__HelloCpp__HXSDKControllerAndroid__) */
