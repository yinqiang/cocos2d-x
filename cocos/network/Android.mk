LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_network_static

LOCAL_MODULE_FILENAME := libnetwork

LOCAL_SRC_FILES := 

ifneq ($(QUICK_NO_WEBSOCKET),1)
LOCAL_SRC_FILES += WebSocket.cpp
endif

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../.. \
					$(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/../platform/android \
				    $(QUICK_V3_LIB)

LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

ifneq ($(QUICK_NO_WEBSOCKET),1)
LOCAL_WHOLE_STATIC_LIBRARIES += libwebsockets_static
endif

include $(BUILD_STATIC_LIBRARY)

ifneq ($(QUICK_NO_WEBSOCKET),1)
$(call import-module,websockets/prebuilt/android)
endif
