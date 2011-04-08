/*
 * stage.h
 *
 *  Created on: Apr 1, 2011
 *      Author: josh
 */

#ifndef STAGE_H_
#define STAGE_H_

#include "opengl.h"
#include "matrix.h"
#include "list.h"

class sprite;
class b2World;

class stage {
private:
   GLuint _width, _height;
   matrix3 _projection;
   b2World* _world;
   list<sprite> _sprites;

public:
   stage(const GLuint w, const GLuint h);
   ~stage();

   static bool setupGL(const GLuint w, const GLuint h);

   static float s2w(unsigned int i);
   static unsigned int w2s(float f);

   const GLuint width() const;
   const GLuint height() const;

   const matrix3 & projection() const;

   b2World* world() const;

   void addSprite(const sprite * s);

   void render();
};

#endif /* STAGE_H_ */
