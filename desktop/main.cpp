#include <GL/glew.h>
#include <GL/glut.h>

#include "logging.h"
#include "stage.h"

#define WIDTH  800
#define HEIGHT 480

stage *gstage = NULL;

void render() {
   gstage->render();
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
   
   gstage = new stage(WIDTH, HEIGHT);
   
   if (!stage::setupGl(WIDTH, HEIGHT)) {
      logError("sprite::setupGl failed");
      return 1;
   }
   
   logInfo("entering main loop");
   glutMainLoop();
   
   delete gstage;

   return 0;
}
