#include <jni.h>
#include "logging.h"
#include "stage.h"

stage *gstage = NULL;

void init(GLuint width, GLuint height) {
   if (gstage) delete gstage;

   logInfo("init(%d, %d)", width, height);

   if (!stage::setupGl(width, height)) {
      logError("sprite::setupGl failed");
      return;
   }

   gstage = new stage(width, height);
}

void drawFrame() {
   gstage->render();
}

extern "C" {
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_init(JNIEnv* env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_jiggak_balldemo_BallDemo_drawFrame(JNIEnv* env, jobject obj);
};

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_init(JNIEnv* env, jobject obj, jint width, jint height) {
   init(width, height);
}

JNIEXPORT void
JNICALL Java_com_jiggak_balldemo_BallDemo_drawFrame(JNIEnv* env, jobject obj) {
   drawFrame();
}
