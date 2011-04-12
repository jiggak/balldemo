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

class sprite {
private:
   /// linked program object handle
   static GLuint s_program;

   /// vertex array attribute handle
   static GLint s_a_position;

   /// uniform handles
   static GLint s_u_texture;
   static GLint s_u_projection;
   static GLint s_u_translation;
   static GLint s_u_rotation;
   static GLint s_u_size;

   GLfloat _verts[8];

protected:
   const stage & _stage;
   b2Body * _body;

   GLuint _width, _height;

   virtual GLuint texture() const { return 0; };

public:
   static bool setupGL();
   static void teardownGL();

   sprite(const stage & s, GLuint w, GLuint h);
   virtual ~sprite();

   b2Body* body() const;

   void render();
};

class ball : public sprite {
private:
   static GLuint s_texture;

protected:
   GLuint texture() const { return s_texture; }

public:
   ball(const stage & s, GLuint x, GLuint y, GLuint w);

   static bool load();
   static void unload();
};

#endif
