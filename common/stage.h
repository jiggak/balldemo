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

class sprite;

class stage {
private:
   GLuint _width, _height;
   matrix3 _projection;
   sprite* _sprite;

public:
   stage(const GLuint w, const GLuint h);
   ~stage();

   static bool setupGl(const GLuint w, const GLuint h);

   const GLuint width() const;
   const GLuint height() const;

   const matrix3 & projection() const;

   void render();
};

#endif /* STAGE_H_ */
