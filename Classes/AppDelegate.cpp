//
//  AppDelegate.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-9.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//

#include "AppDelegate.h"
#include "RootWindow.h"
#include "data/TableLanguage.h"
#include "HXSDKController.h"
#include "LocalStorageUserData.h"
#include "IMDATA.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)


#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"",__VA_ARGS__)
#endif

USING_NS_CC;

AppDelegate::AppDelegate()
{
    TableLanguage::getInstance()->loadTableFromJsonFile();
}

AppDelegate::~AppDelegate() 
{
    TableLanguage::getInstance()->destroy(); 
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CAApplication* pDirector = CAApplication::getApplication();
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    
    if(DEBUG_SQLITE3)
    {
        std::string fullPath = CCFileUtils::sharedFileUtils()->getWritablePath() + "local_storage_user_data.db";
        localStorageUserDataInit(fullPath.c_str());
    }

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HXSDKController::getInstance();
#endif
    
    // run
    pDirector->runWindow(RootWindow::getInstance());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CAApplication::getApplication()->stopAnimation();
    if(DEBUG_SQLITE3)
    {
        localStorageUserDataFree();
    }

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CAApplication::getApplication()->startAnimation();
    if(DEBUG_SQLITE3)
    {
        std::string fullPath = CCFileUtils::sharedFileUtils()->getWritablePath() + "local_storage_user_data.db";
        localStorageUserDataInit(fullPath.c_str());
    }
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
