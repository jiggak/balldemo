#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "logging.h"
#include "stage.h"
#include "sprite.h"

#define WIDTH  800
#define HEIGHT 480

stage *g_stage = NULL;

void render() {
   g_stage->render();
   glutSwapBuffers();
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(WIDTH, HEIGHT);

   glutCreateWindow("BallDemo");
   glutDisplayFunc(&render);
   
   glewInit();
   if (!GLEW_VERSION_2_0) {
      logError("OpenGL 2.0 not available");
      return 1;
   }
   
   if (!stage::setupGL(WIDTH, HEIGHT)) {
      logError("sprite::setupGl failed");
      return 1;
   }
   
   g_stage = new stage(WIDTH, HEIGHT);
   g_stage->addSprite(sprite::ballSprite(*g_stage, 100, 100));

   logInfo("entering main loop");
   glutMainLoop();
   
   delete g_stage;

   return 0;
}
