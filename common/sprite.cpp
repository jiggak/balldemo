#include "sprite.h"

#include "stage.h"
#include "glutils.h"
#include "logging.h"
#include "shaders.h"
#include "tex.h"

GLuint sprite::s_program = 0;
GLint sprite::s_a_position_loc = -1;
GLint sprite::s_u_mvp_matrix_loc = -1;
GLint sprite::s_u_texture_loc = -1;

sprite::sprite(const sprite & other)
   : _stage(other._stage), _width(other._width), _height(other._height)
{
   init();
}

sprite::sprite(const stage & s, const tex_t * texture)
   : _stage(s), _width(texture->width), _height(texture->height)
{
   _texture = glutilLoadTexture(texture);

   init();
}

sprite * sprite::from_texture(const stage & s, const char * fname)
{
   tex_t *texture = texLoadTGA(fname);
   if (!texture) {
      return NULL;
   }

   sprite *result = new sprite(s, texture);

   texFree(texture);

   return result;
}

void sprite::init()
{
   _verts[0] = -1.0f; _verts[1] = -1.0f;
   _verts[2] = -1.0f; _verts[3] = 1.0f;
   _verts[4] = 1.0f;  _verts[5] = -1.0f;
   _verts[6] = 1.0f;  _verts[7] = 1.0f;

   _model_view = matrix3::identity();

   // I don't know why this works
   _model_view.scale(_width / 2, _height / 2, 1.0f);
}

bool sprite::setupGl()
{
   s_program = glutilCreateProgram(sprite_glslv, sprite_glslf);
   if (!s_program)
      return false;

   s_u_mvp_matrix_loc = glGetUniformLocation(s_program, "u_mvp_matrix");
   if (s_u_mvp_matrix_loc == -1) {
      logError("uniform 'u_mvp_matrix' not found");
      return false;
   }

   s_u_texture_loc = glGetUniformLocation(s_program, "u_texture");
   if (s_u_texture_loc == -1) {
      logError("uniform 'u_texture' not found");
      return false;
   }

   s_a_position_loc = glGetAttribLocation(s_program, "a_position");
   if (s_a_position_loc == -1) {
      logError("attribute 'a_position' not found");
      return false;
   }

   return true;
}

void sprite::render()
{
   glUseProgram(s_program);

   matrix3 mvp = _model_view * _stage.projection();
   glUniformMatrix3fv(s_u_mvp_matrix_loc, 1, GL_FALSE, mvp.m());

   glVertexAttribPointer(s_a_position_loc, 2, GL_FLOAT, GL_FALSE, 0, _verts);
   glEnableVertexAttribArray(s_a_position_loc);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, _texture);
   glUniform1i(s_u_texture_loc, 0);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   glDisableVertexAttribArray(s_a_position_loc);
}
