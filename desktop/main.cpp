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

void render()
{
   g_stage->render();
   glutSwapBuffers();
}

void update(int i)
{
   glutTimerFunc(16, &update, 0);
   g_stage->advance();
   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
   if (state == 1) {
      g_stage->addSprite(sprite::ballSprite(*g_stage, x, HEIGHT-y));
   }
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(WIDTH, HEIGHT);

   glutCreateWindow("BallDemo");
   glutDisplayFunc(&render);
   glutTimerFunc(0, &update, 0);
   glutMouseFunc(&mouse);
   
   glewInit();
   if (!GLEW_VERSION_2_0) {
      logError("OpenGL 2.0 not available");
      return 1;
   }

   if (!stage::setupGL(WIDTH, HEIGHT)) {
      logError("sprite::setupGL failed");
      return 1;
   }
   
   g_stage = new stage(WIDTH, HEIGHT);
   g_stage->addSprite(sprite::ballSprite(*g_stage, 400, 240));

   logInfo("entering main loop");
   glutMainLoop();
   
   delete g_stage;

   return 0;
}
