#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "logging.h"
#include "assets.h"

#include "stage.h"
#include "sprite.h"

#define WIDTH  800
#define HEIGHT 480

stage *g_stage = NULL;

void logv(log_level_t level, const char *fmt, va_list args) {
   switch (level) {
   case LOG_LEVEL_ERROR:
      printf("ERROR: "); break;
   default:
      printf("INFO: ");
   }

   vprintf(fmt, args);
   printf("\n");
}

asset_t * loadAsset(const char * path) {
   logInfo("loadAsset(%s)", path);

   string file("../assets/");
   file.append(path);

   ifstream f(file.c_str(), ios::in|ios::binary);
   if (!f.is_open()) {
      logError("file not found: %s", file.c_str());
      return NULL;
   }

   asset_t * asset = new asset_t;

   asset->size = f.rdbuf()->in_avail();
   asset->data = new uint8_t[asset->size];

   if (f.read((char*)asset->data, asset->size).eof()) {
      logError("eof reached before end of asset");
   }

   return asset;
}

void freeAsset(asset_t * asset) {
   delete asset->data;
   delete asset;
}

void render()
{
   g_stage->render();
   glutSwapBuffers();
}

void update(int i)
{
   glutTimerFunc(16, &update, 0);
   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
   if (state == 1) {
      g_stage->touchUp(x, y);
   }
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(WIDTH, HEIGHT);

   glutCreateWindow("Ball Demo");
   glutDisplayFunc(&render);
   glutTimerFunc(0, &update, 0);
   glutMouseFunc(&mouse);

   glewInit();
   if (!GLEW_VERSION_2_0) {
      logError("OpenGL 2.0 not available");
      return 1;
   }

   g_stage = new stage(WIDTH, HEIGHT);
   if (!g_stage->setupGL()) {
      logError("stage::setupGL failed");
      return 1;
   }

   logInfo("entering main loop");
   glutMainLoop();

   delete g_stage;

   return 0;
}
