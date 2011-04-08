/*
 * sprite.h
 *
 *  Created on: Mar 31, 2011
 *      Author: josh
 */
#ifndef SPRITE_H_
#define SPRITE_H_

#include "opengl.h"

class stage;

class b2Body;
struct b2BodyDef;

struct tex_t;

class sprite {
private:
   /// linked program object handle
   static GLuint s_program;

   /// vertex array attribute handle
   static GLint s_a_position;

   /// uniform handles
   static GLint s_u_texture;
   static GLint s_u_projection;
   static GLint s_u_model_view;
   static GLint s_u_size;

   const stage & _stage;
   b2Body * _body;

   GLuint _width, _height;

   GLfloat _verts[8];
   GLuint _texture;

public:
   static bool setupGL();

   sprite(const stage & s, const tex_t * texture, const b2BodyDef * def);

   void render();

   static sprite * ballSprite(const stage & s, GLuint x, GLuint y);
};

#endif
