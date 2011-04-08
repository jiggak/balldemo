#include "sprite.h"

#include "stage.h"
#include "Box2D/Box2D.h"

#include "matrix.h"
#include "glutils.h"
#include "logging.h"
#include "shaders.h"
#include "tex.h"

#include "assets.h"

GLuint sprite::s_program = 0;
GLint sprite::s_a_position = -1;
GLint sprite::s_u_texture = -1;
GLint sprite::s_u_projection = -1;
GLint sprite::s_u_model_view = -1;
GLint sprite::s_u_size = -1;

sprite::sprite(const stage & s, const tex_t * texture, const b2BodyDef * def)
   : _stage(s), _width(texture->width), _height(texture->height)
{
   _texture = glutilLoadTexture(texture);

   _body = _stage.world()->CreateBody(def);

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

bool sprite::setupGL()
{
   s_program = glutilCreateProgram(sprite_glslv, sprite_glslf);
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

   s_u_model_view = glGetUniformLocation(s_program, "u_model_view");
   if (s_u_model_view == -1) {
      logError("uniform 'u_model_view' not found");
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

void sprite::render()
{
   matrix4 modelView = matrix4::identity();

   modelView.translate(stage::w2s(_body->GetPosition().x),
         stage::w2s(_body->GetPosition().y), 0.0f);

   glUseProgram(s_program);

   glUniform2f(s_u_size, (GLfloat)_width, (GLfloat)_height);
   glUniformMatrix4fv(s_u_projection, 1, GL_FALSE, _stage.projection().m());
   glUniformMatrix4fv(s_u_model_view, 1, GL_FALSE, modelView.m());

   glVertexAttribPointer(s_a_position, 2, GL_FLOAT, GL_FALSE, 0, _verts);
   glEnableVertexAttribArray(s_a_position);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, _texture);
   glUniform1i(s_u_texture, 0);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   glDisableVertexAttribArray(s_a_position);
}

sprite * sprite::ballSprite(const stage & s, GLuint x, GLuint y)
{
   tex_t *texture = texLoadTGA(ball_tga, ball_tga_size);
   if (!texture) {
      return NULL;
   }

   b2BodyDef ballBodyDef;
   ballBodyDef.type = b2_dynamicBody;
   ballBodyDef.position.Set(stage::s2w(x), stage::s2w(y));

   sprite *result = new sprite(s, texture, &ballBodyDef);

   texFree(texture);

   b2CircleShape circle;
   circle.m_radius = stage::s2w(result->_width / 2);

   b2FixtureDef ballShapeDef;
   ballShapeDef.shape = &circle;
   ballShapeDef.density = 1.0f;
   ballShapeDef.friction = 0.2f;
   ballShapeDef.restitution = 0.8f;
   result->_body->CreateFixture(&ballShapeDef);

   return result;
}
