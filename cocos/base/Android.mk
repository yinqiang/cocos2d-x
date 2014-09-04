LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_base_static

LOCAL_MODULE_FILENAME := libcocos2dxbase

LOCAL_SRC_FILES := \
                CCAutoreleasePool.cpp \
                CCConfiguration.cpp \
                CCConsole.cpp \
                CCData.cpp \
                CCDirector.cpp \
                CCEvent.cpp \
                CCEventAcceleration.cpp \
                CCEventCustom.cpp \
                CCEventDispatcher.cpp \
                CCEventFocus.cpp \
                CCEventKeyboard.cpp \
                CCEventController.cpp \
                CCEventListener.cpp \
                CCEventListenerController.cpp \
                CCEventListenerAcceleration.cpp \
                CCEventListenerCustom.cpp \
                CCEventListenerFocus.cpp \
                CCEventListenerKeyboard.cpp \
                CCEventListenerMouse.cpp \
                CCEventListenerTouch.cpp \
                CCEventMouse.cpp \
                CCEventTouch.cpp \
                CCIMEDispatcher.cpp \
                CCNS.cpp \
                CCProfiling.cpp \
                CCRef.cpp \
                CCScheduler.cpp \
                CCScriptSupport.cpp \
                CCTouch.cpp \
                CCUserDefault.cpp \
                CCUserDefaultAndroid.cpp \
                CCValue.cpp \
                ZipUtils.cpp \
                atitc.cpp \
                base64.cpp \
                ccCArray.cpp \
                ccFPSImages.c \
                ccTypes.cpp \
                ccUTF8.cpp \
                ccUtils.cpp \
                etc1.cpp \
                s3tc.cpp \
                CCController.cpp \
                CCController-android.cpp \
                ObjectFactory.cpp

ifeq ($(CC_USE_TGA),1)
    LOCAL_SRC_FILES += TGAlib.cpp
endif                

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/.

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/../platform/android \
                    $(LOCAL_PATH)/../../external/tinyxml2 \
                    $(LOCAL_PATH)/../../external/unzip \
                    $(LOCAL_PATH)/../../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../../external/edtaa3func \
                    $(LOCAL_PATH)/../../external/xxhash \
                    $(LOCAL_PATH)/../../external/ConvertUTF \
                    $(LOCAL_PATH)/../../external/freetype2/include/android/freetype2 \
                    $(LOCAL_PATH)/../../external \
                    $(LOCAL_PATH)/../base \
                    $(QUICK_V3_LIB) \
                    $(LOCAL_PATH)/../../external/nslog

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_freetype2_static

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat
LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat

include $(BUILD_STATIC_LIBRARY)

$(call import-module,freetype2/prebuilt/android)