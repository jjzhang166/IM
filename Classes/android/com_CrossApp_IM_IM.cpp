//
//  com_CrossApp_IM_IM.cpp
//  IM
//
//  Created by qiaoxin265@126.com on 15-1-15.
//  Copyright (c) 2015 http://www.9miao.com All rights reserved.
//
#include"com_CrossApp_IM_IM.h"
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
//#include "jni/JniHelper.h"
#include "platform/android/jni/JniHelper.h"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"",__VA_ARGS__)
USING_NS_CC;
int sum (int a, int b)
{
    int SUM = a;
    
    return SUM+=b;
    
}//实现 Java_com_CrossApp_IM_IM_getInt.h 的方法
extern "C" {
    
    JNIEXPORT jint JNICALL Java_com_CrossApp_IM_IM_getInt
    (JNIEnv *env, jclass, jint jni_a, jint jni_b)
    {
        return sum(jni_a, jni_b);
    }
    
    
    JNIEXPORT jstring JNICALL Java_com_CrossApp_IM_IM_getString
    (JNIEnv *env, jclass, jstring jni_string)
    {
        const char* charUrl = env->GetStringUTFChars(jni_string, NULL);
        return env->NewStringUTF(charUrl);
    }
    
    /*
     * Class:     com_example_testjni_MainActivity
     * Method:    callAdd
     * Signature: ()I
     */
    JNIEXPORT jint JNICALL Java_com_CrossApp_IM_IM_callAdd
    (JNIEnv *env, jclass)
    {
        jclass cls = env->FindClass("com/example/testjni/MainActivity");
        jmethodID mid = env->GetStaticMethodID(cls, "add", "(II)I");
        jint result = env->CallStaticIntMethod(cls, mid, 43, 55);
        return result;
    }
    
    /*
     * Class:     com_example_testjni_MainActivity
     * Method:    call_judge
     * Signature: ()Z
     */
    JNIEXPORT jboolean JNICALL Java_com_CrossApp_IM_IM_callJudge
    (JNIEnv *, jclass)
    {
        
    }
}

void com_CrossApp_IM_IM::init_android(const char* userName, const char* passWord)
{
    LOGD("qiaoxin jni call init_android");
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "com/CrossApp/IM/IM", "init_android", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        
        LOGD("qiaoxin jni getStaticMethodInfo init_android");
        jstring stringArg1;
        jstring stringArg2;
        stringArg1 = t.env->NewStringUTF(userName);
        stringArg2 = t.env->NewStringUTF(passWord);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2, NULL);
        t.env->DeleteLocalRef(t.classID);
        
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
    }
}

void com_CrossApp_IM_IM::logout_android()
{
    LOGD("qiaoxin jni call logout_android");
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "com/CrossApp/IM/IM", "logout_android", "()V")) {
        
        LOGD("qiaoxin jni getStaticMethodInfo logout_android");
        t.env->CallStaticVoidMethod(t.classID, t.methodID, NULL);
        t.env->DeleteLocalRef(t.classID);
    }
}


