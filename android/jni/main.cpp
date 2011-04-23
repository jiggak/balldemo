/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#include <jni.h>
#include <android/log.h>

#include "logging.h"
#include "assets.h"

#include "stage.h"
#include "sprite.h"

#define LOG_TAG "balldemo"

// pointer to JNI interface and BallDemo activity instance
JNIEnv *g_env;
jobject g_activity;

stage *g_stage = NULL;

///
/// Implementation of the logv() function that calls __android_log_vprint().
///
void logv(log_level_t level, const char *fmt, va_list args) {
   android_LogPriority l;
   switch (level) {
   case LOG_LEVEL_ERROR:
      l = ANDROID_LOG_ERROR; break;
   default:
      l = ANDROID_LOG_INFO;
   }

   __android_log_vprint(l, LOG_TAG, fmt, args);
}

///
/// Implementation of the loadAsset() function that calls back into Java
/// to use Android's asset loading API. This function requires that the
/// global pointers g_env and g_activity are valid.
///
asset_t * loadAsset(const char * path) {
   jstring file = g_env->NewStringUTF(path);

   jclass cls = g_env->GetObjectClass(g_activity);
   jmethodID mid = g_env->GetMethodID(cls, "loadResource", "(Ljava/lang/String;)[B");

   jbyteArray data = (jbyteArray)g_env->CallObjectMethod(g_activity, mid, file);
   g_env->DeleteLocalRef(file);

   if (data) {
      asset_t * asset = new asset_t;

      asset->size = g_env->GetArrayLength(data);
      asset->data = new uint8_t[asset->size];
      g_env->GetByteArrayRegion(data, 0, asset->size, (jbyte*)asset->data);

      return asset;
   }

   return NULL;
}

/// Delete assets data then the asset struct.
void freeAsset(asset_t * asset) {
   delete asset->data;
   delete asset;
}

extern "C" {
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_nativeOnCreate(JNIEnv* env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_nativeOnDestroy(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_setupGL(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_SurfaceView_queueAction(JNIEnv* env, jobject obj, jint type, jfloat x, jfloat y);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_SurfaceViewRenderer_drawFrame(JNIEnv* env, jobject obj);
};

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_nativeOnCreate
(JNIEnv* env, jobject obj, jint width, jint height)
{
   logInfo("onCreate(%d, %d)", width, height);
   g_stage = new stage(width, height);
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_nativeOnDestroy
(JNIEnv* env, jobject obj)
{
   logInfo("onDestroy()");
   delete g_stage;
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_setupGL
(JNIEnv* env, jobject obj)
{
   // stage::setupGL() will call loadAsset() so we need to make sure the global
   // pointer to the BallDemo activity and JNI interface are valid
   g_activity = obj;
   g_env = env;

   if (!g_stage->setupGL()) {
      logError("stage::setupGL failed");
   }
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_SurfaceView_queueAction
(JNIEnv* env, jobject obj, jint type, jfloat x, jfloat y)
{
   g_stage->queueAction((action_type_t)type, x, y);
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_SurfaceViewRenderer_drawFrame
(JNIEnv* env, jobject obj)
{
   g_stage->render();
}
