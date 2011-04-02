#include "sprite.h"

#include "stage.h"
#include "glutils.h"
#include "logging.h"
#include "shaders.h"

const GLfloat sprite::s_verts[8] = {
      -1.0f, -1.0f,
      -1.0f,  1.0f,
       1.0f, -1.0f,
       1.0f,  1.0f
};

GLuint sprite::s_program = 0;
GLint sprite::s_a_position_loc = -1;
GLint sprite::s_u_mvp_matrix_loc = -1;

sprite::sprite(const sprite & other)
   : _stage(other._stage), _width(other._width), _height(other._height)
{
   init();
}

sprite::sprite(const stage & s, const GLuint w, const GLuint h)
   : _stage(s), _width(w), _height(h)
{
   init();
}

void sprite::init()
{
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

   glVertexAttribPointer(s_a_position_loc, 2, GL_FLOAT, GL_FALSE, 0, s_verts);
   glEnableVertexAttribArray(s_a_position_loc);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
