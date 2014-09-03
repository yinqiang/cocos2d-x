LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES := \
cocos2d.cpp \
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
                    $(LOCAL_PATH)/../external/tiff/include/android \
                    $(LOCAL_PATH)/../external/webp/include/android \
                    $(LOCAL_PATH)/base \
                    $(QUICK_V3_LIB) \
                    $(LOCAL_PATH)/../external/nslog

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_3d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_base_static
ifeq ($(CC_USE_PHYSICS),1)
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_physics_static
endif
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dxandroid_static

# define the macro to compile through support/zip_support/ioapi.c
LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat
LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API
LOCAL_EXPORT_CPPFLAGS := -Wno-deprecated-declarations -Wno-extern-c-compat

include $(BUILD_STATIC_LIBRARY)

$(call import-module,2d)
$(call import-module,3d)
$(call import-module,base)
ifeq ($(CC_USE_PHYSICS),1)
$(call import-module,physics)
endif
$(call import-module,platform/android)