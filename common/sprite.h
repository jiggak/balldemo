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
struct tex_t;

class sprite {
private:
   static GLuint s_program;
   static GLint s_a_position_loc;
   static GLint s_u_mvp_matrix_loc;
   static GLint s_u_texture_loc;

   const stage & _stage;
   GLuint _width, _height;
   matrix3 _model_view;

   GLfloat _verts[8];
   GLuint _texture;

   void init();

public:
   sprite(const sprite & other);
   sprite(const stage & s, const tex_t * texture);

   static sprite * from_texture(const stage & s, const char * fname);

   static bool setupGl();

   void render();
};

#endif
