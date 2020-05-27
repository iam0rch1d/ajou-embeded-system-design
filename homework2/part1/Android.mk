LOCAL_PATH:=$(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -fPIE
LOCAL_LDFLAGS += -fPIE -pie

LOCAL_MODULE:=combine
LOCAL_SRC_FILES:=combine.c

include $(BUILD_EXECUTABLE)

