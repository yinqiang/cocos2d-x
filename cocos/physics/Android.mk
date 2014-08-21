LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_physics_static

LOCAL_MODULE_FILENAME := libcocos2dxphysics

LOCAL_SRC_FILES := \
        CCPhysicsBody.cpp \
        CCPhysicsContact.cpp \
        CCPhysicsJoint.cpp \
        CCPhysicsShape.cpp \
        CCPhysicsWorld.cpp \
        chipmunk/CCPhysicsBodyInfo_chipmunk.cpp \
        chipmunk/CCPhysicsContactInfo_chipmunk.cpp \
        chipmunk/CCPhysicsJointInfo_chipmunk.cpp \
        chipmunk/CCPhysicsShapeInfo_chipmunk.cpp \
        chipmunk/CCPhysicsWorldInfo_chipmunk.cpp \
        

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
                    $(LOCAL_PATH)/../../external \
                    $(LOCAL_PATH)/../base \
                    $(QUICK_V3_LIB) \
                    $(LOCAL_PATH)/../../external/nslog

ifneq ($(QUICK_NO_CHIPMUNK),1)
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
endif

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat
LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat

include $(BUILD_STATIC_LIBRARY)

ifneq ($(QUICK_NO_CHIPMUNK),1)
$(call import-module,chipmunk)
endif