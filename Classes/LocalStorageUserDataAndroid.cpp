//
//  LocalStorageUserDataAndroid.cpp
//  BabyGenius
//
//  Created by Chydison on 14/11/28.
//
//

#include "LocalStorageUserData.h"
#include "CrossApp.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include "jni.h"
#include "jni/JniHelper.h"

USING_NS_CC;
static int _initialized_userData = 0;

static void splitFilename (std::string& str)
{
    size_t found = 0;
    found=str.find_last_of("/\\");
    if (found != std::string::npos)
    {
        str = str.substr(found+1);
    }
}

void localStorageUserDataInit( const char *fullpath)
{
    if (fullpath == NULL || strlen(fullpath) == 0) return;
    
    if( ! _initialized_userData ) {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, "org/CrossApp/lib/Cocos2dxLocalStorage", "init", "(Ljava/lang/String;Ljava/lang/String;)Z")) {
            std::string strDBFilename = fullpath;
            splitFilename(strDBFilename);
            jstring jdbName = t.env->NewStringUTF(strDBFilename.c_str());
            jstring jtableName = t.env->NewStringUTF("data");
            jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, jdbName, jtableName);
            t.env->DeleteLocalRef(jdbName);
            t.env->DeleteLocalRef(jtableName);
            t.env->DeleteLocalRef(t.classID);
            if (ret) {
                _initialized_userData = 1;
            }
        }
        
    }
}

void localStorageUserDataFree()
{
    if( _initialized_userData ) {
        
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, "org/CrossApp/lib/Cocos2dxLocalStorage", "destory", "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
        
        _initialized_userData = 0;
    }
}

/** sets an item in the LS */
void localStorageUserDataSetItem( const char *key, const char *value)
{
    assert( _initialized_userData );
    
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "org/CrossApp/lib/Cocos2dxLocalStorage", "setItem", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jkey = t.env->NewStringUTF(key);
        jstring jvalue = t.env->NewStringUTF(value);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jkey, jvalue);
        t.env->DeleteLocalRef(jkey);
        t.env->DeleteLocalRef(jvalue);
        t.env->DeleteLocalRef(t.classID);
    }
}

/** gets an item from the LS */
const char* localStorageUserDataGetItem( const char *key )
{
    assert( _initialized_userData );
    JniMethodInfo t;
    CCString* pStr = NULL;
    if (JniHelper::getStaticMethodInfo(t, "org/CrossApp/lib/Cocos2dxLocalStorage", "getItem", "(Ljava/lang/String;)Ljava/lang/String;")) {
        jstring jkey = t.env->NewStringUTF(key);
        jstring ret = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, jkey);
        pStr = CCString::create(JniHelper::jstring2string(ret));
        t.env->DeleteLocalRef(ret);
        t.env->DeleteLocalRef(jkey);
        t.env->DeleteLocalRef(t.classID);
    }
    return pStr ? pStr->getCString() : NULL;
}

/** removes an item from the LS */
void localStorageUserDataRemoveItem( const char *key )
{
    assert( _initialized_userData );
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, "org/CrossApp/lib/Cocos2dxLocalStorage", "removeItem", "(Ljava/lang/String;)V")) {
        jstring jkey = t.env->NewStringUTF(key);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jkey);
        t.env->DeleteLocalRef(jkey);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

