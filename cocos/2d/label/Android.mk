LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_label_static

LOCAL_MODULE_FILENAME := libcocoslabel

ifneq ($(QUICK_NO_FREETYPE),1)
    LOCAL_SRC_FILES := \
        ../CCFont.cpp \
        ../CCFontAtlas.cpp \
        ../CCFontAtlasCache.cpp \
        ../CCFontCharMap.cpp \
        ../CCFontFNT.cpp \
        ../CCFontFreeType.cpp \
        ../CCLabel.cpp \
        ../CCLabelAtlas.cpp \
        ../CCLabelTextFormatter.cpp \

else
    LOCAL_SRC_FILES := 
endif

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../.. \
                    $(LOCAL_PATH)/../../platform/android \
                    $(QUICK_V3_LIB) \
                    $(LOCAL_PATH)/../../../external/edtaa3func


ifneq ($(QUICK_NO_FREETYPE),1)
LOCAL_WHOLE_STATIC_LIBRARIES := cocos_freetype2_static
endif

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat
LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat

include $(BUILD_STATIC_LIBRARY)

$(call import-module,freetype2/prebuilt/android)