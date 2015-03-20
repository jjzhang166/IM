LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := CrossApp_cpp_shared

LOCAL_MODULE_FILENAME := libCrossApp_cpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/RootWindow.cpp \
../../Classes/FirstViewController.cpp \
../../Classes/SecondViewController.cpp \
../../Classes/HXSDKController.cpp \
../../Classes/HXSDKBuddy.cpp \
../../Classes/groupview/GroupInfoViewController.cpp \
../../Classes/AddHeadForgrand.cpp \
../../Classes/AddFriendView.cpp \
../../Classes/IMLoginRegister.cpp \
../../Classes/IMMyInfo.cpp \
../../Classes/IMMyController.cpp \
../../Classes/IMSetInfomation.cpp \
../../Classes/IMTableCell.cpp \
../../Classes/IMSettingClassify.cpp \
../../Classes/IMSetting.cpp \
../../Classes/android/com_CrossApp_IM_IM.cpp \
../../Classes/data/TableBase.cpp \
../../Classes/data/TableLanguage.cpp \
../../Classes/LocalStorageUserDataAndroid.cpp

#define all-cpp-files
#$(patsubst jni/%,%, $(shell find $(LOCAL_PATH)/../../Classes/ $(LOCAL_PATH) -name #"*.cpp"))  
#endef
#LOCAL_SRC_FILES := $(call all-cpp-files)
LOCAL_CFLAGS += -DCOCOS2D_DEBUG=1 			
			
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes


LOCAL_WHOLE_STATIC_LIBRARIES += CrossApp_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += CrossApp_extension_static

include $(BUILD_SHARED_LIBRARY)
$(call import-add-path, D:/CrossApp)
$(call import-add-path, D:/CrossApp/CrossApp/platform/third_party/android/prebuilt)
$(call import-module,CrossApp)
$(call import-module,CrossApp/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
