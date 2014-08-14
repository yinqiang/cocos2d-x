LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES := \
cocos2d.cpp \
3d/CCAnimate3D.cpp \
3d/CCAnimation3D.cpp \
3d/CCBundle3D.cpp \
3d/CCBundleReader.cpp \
3d/CCMesh.cpp \
3d/CCMeshSkin.cpp \
3d/CCSprite3DMaterial.cpp \
3d/CCObjLoader.cpp \
3d/CCSprite3D.cpp \
platform/CCGLViewProtocol.cpp \
platform/CCFileUtils.cpp \
platform/CCSAXParser.cpp \
platform/CCThread.cpp \
platform/CCImage.cpp \
math/CCAffineTransform.cpp \
math/CCGeometry.cpp \
math/CCVertex.cpp \
math/Mat4.cpp \
math/MathUtil.cpp \
math/Quaternion.cpp \
math/TransformUtils.cpp \
math/Vec2.cpp \
math/Vec3.cpp \
math/Vec4.cpp \
base/CCAutoreleasePool.cpp \
base/CCConfiguration.cpp \
base/CCConsole.cpp \
base/CCData.cpp \
base/CCDirector.cpp \
base/CCEvent.cpp \
base/CCEventAcceleration.cpp \
base/CCEventCustom.cpp \
base/CCEventDispatcher.cpp \
base/CCEventFocus.cpp \
base/CCEventKeyboard.cpp \
base/CCEventController.cpp \
base/CCEventListener.cpp \
base/CCEventListenerController.cpp \
base/CCEventListenerAcceleration.cpp \
base/CCEventListenerCustom.cpp \
base/CCEventListenerFocus.cpp \
base/CCEventListenerKeyboard.cpp \
base/CCEventListenerMouse.cpp \
base/CCEventListenerTouch.cpp \
base/CCEventMouse.cpp \
base/CCEventTouch.cpp \
base/CCIMEDispatcher.cpp \
base/CCNS.cpp \
base/CCProfiling.cpp \
base/CCRef.cpp \
base/CCScheduler.cpp \
base/CCScriptSupport.cpp \
base/CCTouch.cpp \
base/CCUserDefault.cpp \
base/CCUserDefaultAndroid.cpp \
base/CCValue.cpp \
base/TGAlib.cpp \
base/ZipUtils.cpp \
base/atitc.cpp \
base/base64.cpp \
base/ccCArray.cpp \
base/ccFPSImages.c \
base/ccTypes.cpp \
base/ccUTF8.cpp \
base/ccUtils.cpp \
base/etc1.cpp \
base/s3tc.cpp \
base/CCController.cpp \
base/CCController-android.cpp \
base/ObjectFactory.cpp \
renderer/CCBatchCommand.cpp \
renderer/CCCustomCommand.cpp \
renderer/CCGLProgram.cpp \
renderer/CCGLProgramCache.cpp \
renderer/CCGLProgramState.cpp \
renderer/CCGLProgramStateCache.cpp \
renderer/CCGroupCommand.cpp \
renderer/CCQuadCommand.cpp \
renderer/CCMeshCommand.cpp \
renderer/CCRenderCommand.cpp \
renderer/CCRenderer.cpp \
renderer/CCTexture2D.cpp \
renderer/CCTextureAtlas.cpp \
renderer/CCTextureCache.cpp \
renderer/ccGLStateCache.cpp \
renderer/ccShaders.cpp \
physics/CCPhysicsBody.cpp \
physics/CCPhysicsContact.cpp \
physics/CCPhysicsJoint.cpp \
physics/CCPhysicsShape.cpp \
physics/CCPhysicsWorld.cpp \
physics/chipmunk/CCPhysicsBodyInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsContactInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsJointInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsShapeInfo_chipmunk.cpp \
physics/chipmunk/CCPhysicsWorldInfo_chipmunk.cpp \
../external/ConvertUTF/ConvertUTFWrapper.cpp \
../external/ConvertUTF/ConvertUTF.c \
../external/tinyxml2/tinyxml2.cpp \
../external/unzip/ioapi.cpp \
../external/unzip/unzip.cpp \
../external/unzip/ioapi_mem.cpp \
../external/edtaa3func/edtaa3func.cpp \
../external/xxhash/xxhash.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/. \
                    $(LOCAL_PATH)/3d \
                    $(LOCAL_PATH)/math \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/../external/tinyxml2 \
                    $(LOCAL_PATH)/../external \
                    $(LOCAL_PATH)/../external/unzip \
                    $(LOCAL_PATH)/../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../external/xxhash \
                    $(QUICK_V3_LIB) \
                    $(LOCAL_PATH)/../external/nslog

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/. \
                    $(LOCAL_PATH)/platform/android \
                    $(LOCAL_PATH)/../external/tinyxml2 \
                    $(LOCAL_PATH)/../external/unzip \
                    $(LOCAL_PATH)/../external/chipmunk/include/chipmunk \
                    $(LOCAL_PATH)/../external/edtaa3func \
                    $(LOCAL_PATH)/../external/xxhash \
                    $(LOCAL_PATH)/../external/ConvertUTF \
                    $(LOCAL_PATH)/../external \
                    $(LOCAL_PATH)/../external/freetype2/include/android \
                    $(LOCAL_PATH)/../external/freetype2/include/android/freetype2 \
                    $(LOCAL_PATH)/base \
                    $(QUICK_V3_LIB) \
                    $(LOCAL_PATH)/../external/nslog


LOCAL_LDLIBS := -lGLESv2 \
                -llog \
                -lz \
                -landroid

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz \
                       -landroid

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dxandroid_static

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat
LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat

include $(BUILD_STATIC_LIBRARY)

$(call import-module,2d)
$(call import-module,chipmunk)
$(call import-module,platform/android)
