/*
 * gltext.h
 *
 *  Created on: Apr 12, 2011
 *      Author: josh
 */

#ifndef GLTEXT_H_
#define GLTEXT_H_

#include "opengl.h"

class stage;

class gltext {
private:
   /// linked program object handle
   static GLuint s_program;

   /// vertex array attribute handle
   static GLint s_a_position;

   /// uniform handles
   static GLint s_u_texture;
   static GLint s_u_projection;
   static GLint s_u_translation;
   static GLint s_u_char_size;
   static GLint s_u_char_scale;
   static GLint s_u_char_offset;

   const stage & _stage;

   int _cwidth;
   int _cheight;

   GLfloat _verts[8];
   GLuint _texture;

   void beforePrint();
   void _putc(int x, int y, char c);
   void afterPrint();

public:
   gltext(const stage & s) : _stage(s) { }
   ~gltext();

   static bool loadGL();
   static void unloadGL();

   inline int char_width() const { return _cwidth; }
   inline int char_height() const { return _cheight; }

   bool loadTexture(const char * path);

   void putc(int x, int y, char c);

   void print(int x, int y, const char *s);

   void printf(int x, int y, const char *fmt, ...);
};

#endif /* GLTEXT_H_ */
