LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE     := balldemo
LOCAL_C_INCLUDES := ../common
LOCAL_SRC_FILES  := logging.cpp \
   ../../common/glutils.cpp \
   ../../common/matrix.cpp \
   ../../common/tex.cpp \
   ../../common/sprite.cpp \
   ../../common/stage.cpp \
   main.cpp
LOCAL_LDLIBS     := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
