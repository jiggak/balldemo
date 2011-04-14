/*
 * gltext.cpp
 *
 *  Created on: Apr 12, 2011
 *      Author: josh
 */
#include "gltext.h"

#include <cstring>
#include <cstdarg>
#include <cstdio>

#include "logging.h"
#include "glutils.h"
#include "stage.h"
#include "assets.h"
#include "tex.h"

#define ASCII_MIN 32
#define ASCII_MAX 126

GLuint gltext::s_program = 0;
GLint gltext::s_a_position = -1;
GLint gltext::s_u_texture = -1;
GLint gltext::s_u_projection = -1;
GLint gltext::s_u_translation = -1;
GLint gltext::s_u_char_size = -1;
GLint gltext::s_u_char_scale = -1;
GLint gltext::s_u_char_offset = -1;

bool gltext::loadGL()
{
   s_program = glutilCreateProgram("shaders/text.glslv", "shaders/text.glslf");
   if (!s_program)
      return false;

   s_u_texture = glGetUniformLocation(s_program, "u_texture");
   if (s_u_texture == -1) {
      logError("uniform 'u_texture' not found");
      return false;
   }

   s_u_projection = glGetUniformLocation(s_program, "u_projection");
   if (s_u_projection == -1) {
      logError("uniform 'u_projection' not found");
      return false;
   }

   s_u_translation = glGetUniformLocation(s_program, "u_translation");
   if (s_u_translation == -1) {
      logError("uniform 'u_translation' not found");
      return false;
   }

   s_u_char_size = glGetUniformLocation(s_program, "u_char_size");
   if (s_u_char_size == -1) {
      logError("uniform 'u_char_size' not found");
      return false;
   }

   s_u_char_scale = glGetUniformLocation(s_program, "u_char_scale");
   if (s_u_char_scale == -1) {
      logError("uniform 'u_char_scale' not found");
      return false;
   }

   s_u_char_offset = glGetUniformLocation(s_program, "u_char_offset");
   if (s_u_char_offset == -1) {
      logError("uniform 'u_char_offset' not found");
      return false;
   }

   s_a_position = glGetAttribLocation(s_program, "a_position");
   if (s_a_position == -1) {
      logError("attribute 'a_position' not found");
      return false;
   }

   return true;
}

void gltext::unloadGL()
{
   glDeleteProgram(s_program);
}

gltext::~gltext()
{
   glDeleteTextures(1, &_texture);
}

bool gltext::loadTexture(const char * path)
{
   tex_t *texture = texLoadTGA(path);
   if (!texture) {
      return false;
   }

   _cwidth = texture->width / (ASCII_MAX-ASCII_MIN-1);
   _cheight = texture->height;

   _texture = glutilLoadTexture(texture);
   texFree(texture);

   GLfloat hw = _cwidth / 2.0f;
   GLfloat hh = _cheight / 2.0f;

   _verts[0] = -hw; _verts[1] = -hh;
   _verts[2] = -hw; _verts[3] = hh;
   _verts[4] = hw;  _verts[5] = -hh;
   _verts[6] = hw;  _verts[7] = hh;

   return true;
}

void gltext::beforePrint()
{
   glUseProgram(s_program);

   glUniform2f(s_u_char_size, (GLfloat)_cwidth, (GLfloat)_cheight);
   glUniform1f(s_u_char_scale, (GLfloat)_cwidth / (_cwidth * (ASCII_MAX-ASCII_MIN+1)));
   glUniformMatrix4fv(s_u_projection, 1, GL_FALSE, _stage.projection().m());

   glVertexAttribPointer(s_a_position, 2, GL_FLOAT, GL_FALSE, 0, _verts);
   glEnableVertexAttribArray(s_a_position);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, _texture);
   glUniform1i(s_u_texture, 0);
}

void gltext::_putc(int x, int y, char c)
{
   GLfloat offset = c - ASCII_MIN;

   matrix4 t = matrix4::translation(x, y, 0.0f);

   glUniformMatrix4fv(s_u_translation, 1, GL_FALSE, t.m());
   glUniform1f(s_u_char_offset, offset);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void gltext::afterPrint()
{
   glDisableVertexAttribArray(s_a_position);
}

void gltext::putc(int x, int y, char c)
{
   beforePrint();

   _putc(x, y, c);

   afterPrint();
}

void gltext::print(int x, int y, const char *s)
{
   beforePrint();

   int len = strlen(s);
   for (int i=0; i<len; i++) {
      _putc(x + (i*_cwidth), y, s[i]);
   }

   afterPrint();
}

void gltext::printf(int x, int y, const char *fmt, ...)
{
   va_list argp;
   va_start(argp, fmt);

   // 100 characters wide seems reasonable
   char buffer[100];
   vsprintf(buffer, fmt, argp);

   print(x, y, buffer);

   va_end(argp);
}
