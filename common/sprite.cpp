/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#include "sprite.h"

#include "stage.h"
#include "Box2D/Box2D.h"

#include "matrix.h"
#include "glutils.h"
#include "logging.h"
#include "tex.h"

GLuint sprite::s_program = 0;
GLint sprite::s_a_position = -1;
GLint sprite::s_u_texture = -1;
GLint sprite::s_u_projection = -1;
GLint sprite::s_u_translation = -1;
GLint sprite::s_u_rotation = -1;
GLint sprite::s_u_size = -1;

sprite::sprite(const stage & s, GLuint w, GLuint h)
   : _stage(s), _width(w), _height(h)
{
   GLfloat hw = _width/2.0f;  // half width
   GLfloat hh = _height/2.0f; // half height

   // sprite uses a triangle strip in OpenGL to render a square
   // vertex array consists of bottom left, top left, bottom right, top right
   // vertices centered on the origin (0,0)
   _verts[0] = -hw; _verts[1] = -hh;
   _verts[2] = -hw; _verts[3] = hh;
   _verts[4] = hw;  _verts[5] = -hh;
   _verts[6] = hw;  _verts[7] = hh;
}

sprite::~sprite()
{
   _stage.world()->DestroyBody(_body);
}

bool sprite::loadGL()
{
   s_program = glutilCreateProgram("shaders/sprite.glslv", "shaders/sprite.glslf");
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

   s_u_rotation = glGetUniformLocation(s_program, "u_rotation");
   if (s_u_rotation == -1) {
      logError("uniform 'u_rotation' not found");
      return false;
   }

   s_u_size = glGetUniformLocation(s_program, "u_size");
   if (s_u_size == -1) {
      logError("uniform 'u_size' not found");
      return false;
   }

   s_a_position = glGetAttribLocation(s_program, "a_position");
   if (s_a_position == -1) {
      logError("attribute 'a_position' not found");
      return false;
   }

   return true;
}

void sprite::unloadGL()
{
   glDeleteProgram(s_program);
}

void sprite::render()
{
   GLfloat tx = stage::w2s(_body->GetPosition().x);
   GLfloat ty = stage::w2s(_body->GetPosition().y);
   matrix4 t = matrix4::translation(tx, ty, 0.0f);
   matrix4 r = matrix4::rotation(-_body->GetAngle(), 0.0f, 0.0f, 1.0f);

   glUseProgram(s_program);

   glUniform2f(s_u_size, (GLfloat)_width, (GLfloat)_height);
   glUniformMatrix4fv(s_u_projection, 1, GL_FALSE, _stage.projection().m());
   glUniformMatrix4fv(s_u_translation, 1, GL_FALSE, t.m());
   glUniformMatrix4fv(s_u_rotation, 1, GL_FALSE, r.m());

   glVertexAttribPointer(s_a_position, 2, GL_FLOAT, GL_FALSE, 0, _verts);
   glEnableVertexAttribArray(s_a_position);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, this->texture());
   glUniform1i(s_u_texture, 0);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   glDisableVertexAttribArray(s_a_position);
}

GLuint ball::s_texture = 0;

ball::ball(const stage & s, GLuint x, GLuint y, GLuint w) : sprite(s, w, w)
{
   b2BodyDef ballBodyDef;
   ballBodyDef.type = b2_dynamicBody;
   ballBodyDef.position.Set(stage::s2w(x), stage::s2w(y));

   _body = _stage.world()->CreateBody(&ballBodyDef);

   b2CircleShape circle;
   circle.m_radius = stage::s2w(w / 2);

   b2FixtureDef ballShapeDef;
   ballShapeDef.shape = &circle;
   ballShapeDef.density = 1.0f;
   ballShapeDef.friction = 0.2f;
   ballShapeDef.restitution = 0.8f;

   _body->CreateFixture(&ballShapeDef);
}

bool ball::loadGL()
{
   tex_t *texture = texLoadTGA("textures/ball.tga");
   if (!texture) {
      return false;
   }

   s_texture = glutilLoadTexture(texture);
   texFree(texture);

   return true;
}

void ball::unloadGL()
{
   glDeleteTextures(1, &s_texture);
}
