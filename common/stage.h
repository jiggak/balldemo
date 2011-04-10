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
   bool _rotated;

   matrix4 _projection;
   b2World* _world;
   list<sprite> _sprites;

public:
   stage(const GLuint w, const GLuint h, bool rotate=false);
   ~stage();

   static bool setupGL();

   static float s2w(unsigned int i);
   static unsigned int w2s(float f);

   const GLuint width() const;
   const GLuint height() const;

   const matrix4 & projection() const;

   b2World* world() const;

   void addSprite(const sprite * s);

   void advance();
   void render();

   void touchUp(int x, int y);
};

#endif /* STAGE_H_ */
