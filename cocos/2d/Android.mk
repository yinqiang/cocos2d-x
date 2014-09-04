LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_2d_static

LOCAL_MODULE_FILENAME := libcocos2dx2d

LOCAL_SRC_FILES := \
    CCAction.cpp \
    CCActionCamera.cpp \
    CCActionCatmullRom.cpp \
    CCActionEase.cpp \
    CCActionGrid.cpp \
    CCActionGrid3D.cpp \
    CCActionInstant.cpp \
    CCActionInterval.cpp \
    CCActionManager.cpp \
    CCActionPageTurn3D.cpp \
    CCActionProgressTimer.cpp \
    CCActionTiledGrid.cpp \
    CCActionTween.cpp \
    CCAnimation.cpp \
    CCAnimationCache.cpp \
    CCAtlasNode.cpp \
    CCClippingNode.cpp \
    CCClippingRegionNode.cpp \
    CCComponent.cpp \
    CCComponentContainer.cpp \
    CCDrawNode.cpp \
    CCDrawingPrimitives.cpp \
    CCGLBufferedNode.cpp \
    CCGrabber.cpp \
    CCGrid.cpp \
    CCLayer.cpp \
    CCMotionStreak.cpp \
    CCNode.cpp \
    CCNodeGrid.cpp \
    CCParallaxNode.cpp \
    CCParticleBatchNode.cpp \
    CCParticleExamples.cpp \
    CCParticleSystem.cpp \
    CCParticleSystemQuad.cpp \
    CCProgressTimer.cpp \
    CCRenderTexture.cpp \
    CCScene.cpp \
    CCSprite.cpp \
    CCSpriteBatchNode.cpp \
    CCSpriteFrame.cpp \
    CCSpriteFrameCache.cpp \
    CCTMXLayer.cpp \
    CCFastTMXLayer.cpp \
    CCTMXObjectGroup.cpp \
    CCTMXTiledMap.cpp \
    CCFastTMXTiledMap.cpp \
    CCTMXXMLParser.cpp \
    CCTransition.cpp \
    CCTransitionPageTurn.cpp \
    CCTransitionProgress.cpp \
    CCTweenFunction.cpp \

ifeq ($(CC_USE_TGA),1)
    LOCAL_SRC_FILES += CCTileMapAtlas.cpp
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
                    $(LOCAL_PATH)/../../external \
                    $(LOCAL_PATH)/../base \
                    $(QUICK_V3_LIB) \
                    $(LOCAL_PATH)/../../external/nslog


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_label_static

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat
LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat

include $(BUILD_STATIC_LIBRARY)

$(call import-module,2d/label)