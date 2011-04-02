/*
 * sprite.h
 *
 *  Created on: Mar 31, 2011
 *      Author: josh
 */
#ifndef SPRITE_H_
#define SPRITE_H_

#include "opengl.h"
#include "matrix.h"

class stage;

class sprite {
private:
   GLuint _width, _height;
   const stage & _stage;
   matrix3 _model_view;

   static GLuint s_program;
   static GLuint s_a_position_loc;
   static GLuint s_u_mvp_matrix_loc;

   static const GLfloat s_verts[8];

   void init();

public:
   sprite(const sprite & other);
   sprite(const stage & s, const GLuint w, const GLuint h);

   static bool setupGl();

   void render();
};

#endif
