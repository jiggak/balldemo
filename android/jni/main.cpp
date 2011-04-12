#include <jni.h>
#include <android/log.h>

#include "logging.h"
#include "assets.h"

#include "stage.h"
#include "sprite.h"

#define LOG_TAG "balldemo"

JNIEnv *g_env;
jobject g_activity;

stage *g_stage = NULL;

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

void freeAsset(asset_t * asset) {
   delete asset->data;
   delete asset;
}

void create(GLuint width, GLuint height) {
   logInfo("create(%d, %d)", width, height);
   g_stage = new stage(width, height);
}

void load() {
   if (!stage::setupGL()) {
      logError("sprite::setupGL failed");
   }
}

void destroy() {
   delete g_stage;
}

void drawFrame() {
   g_stage->advance();
   g_stage->render();
}

void touchUp(int x, int y) {
   g_stage->touchUp(x, y);
}

extern "C" {
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_nativeOnCreate(JNIEnv* env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_nativeOnDestroy(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_load(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_drawFrame(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_touchUp(JNIEnv* env, jobject obj, jint x, jint y);
};

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_nativeOnCreate(JNIEnv* env, jobject obj, jint width, jint height) {
   create(width, height);

   g_env = env;
   g_activity = obj;
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_nativeOnDestroy(JNIEnv* env, jobject obj) {
   destroy();
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_load(JNIEnv* env, jobject obj) {
   load();
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_drawFrame(JNIEnv* env, jobject obj) {
   drawFrame();
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_touchUp(JNIEnv* env, jobject obj, jint x, jint y) {
   touchUp(x, y);
}
