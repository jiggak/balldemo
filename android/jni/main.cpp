#include <jni.h>
#include "logging.h"
#include "stage.h"
#include "sprite.h"

stage *g_stage = NULL;

void init(GLuint width, GLuint height) {
   if (g_stage) delete g_stage;

   logInfo("init(%d, %d)", width, height);

   if (!stage::setupGL(width, height)) {
      logError("sprite::setupGL failed");
      return;
   }

   g_stage = new stage(width, height);
   g_stage->addSprite(sprite::ballSprite(*g_stage, 400, 400));
}

void drawFrame() {
   g_stage->advance();
   g_stage->render();
}

void touchUp(int x, int y) {
   g_stage->addSprite(sprite::ballSprite(*g_stage, x, y));
}

extern "C" {
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_init(JNIEnv* env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_drawFrame(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_touchUp(JNIEnv* env, jobject obj, jint x, jint y);
};

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_init(JNIEnv* env, jobject obj, jint width, jint height) {
   init(width, height);
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_drawFrame(JNIEnv* env, jobject obj) {
   drawFrame();
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_touchUp(JNIEnv* env, jobject obj, jint x, jint y) {
   touchUp(x, y);
}
