#include "matrix.h"
#include "logging.h"

matrix3 matrix3::identity()
{
   const GLfloat m[] = {
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f
   };

   return matrix3(m);
}

matrix3 matrix3::ortho2d(const GLint left, const GLint right,
      const GLint bottom, const GLint top)
{
   const GLfloat m[] = {
         2 / (GLfloat)(right - left), 0.0f, 0.0f,
         0.0f, 2 / (GLfloat)(top - bottom), 0.0f,
         0.0f, 0.0f, -1.0f
   };

   return matrix3(m);
}

matrix3::matrix3()
{
   _m[0] = 0.0f;
   _m[1] = 0.0f;
   _m[2] = 0.0f;
   _m[3] = 0.0f;
   _m[4] = 0.0f;
   _m[5] = 0.0f;
   _m[6] = 0.0f;
   _m[7] = 0.0f;
   _m[8] = 0.0f;
}

matrix3::matrix3(const GLfloat m[9])
{
   init(m);
}

matrix3::matrix3(const matrix3 & other)
{
   init(other.m());
}

void matrix3::init(const GLfloat m[9])
{
   _m[0] = m[0];
   _m[1] = m[1];
   _m[2] = m[2];
   _m[3] = m[3];
   _m[4] = m[4];
   _m[5] = m[5];
   _m[6] = m[6];
   _m[7] = m[7];
   _m[8] = m[8];
}

const GLfloat* matrix3::m() const { return _m; }

void matrix3::scale(const GLfloat sx, const GLfloat sy, const GLfloat sz)
{
   _m[0] *= sx;
   _m[1] *= sx;
   _m[2] *= sx;

   _m[3] *= sy;
   _m[4] *= sy;
   _m[5] *= sy;

   _m[6] *= sz;
   _m[7] *= sz;
   _m[8] *= sz;
}

matrix3 matrix3::operator*(const matrix3 & other)
{
   GLfloat result[9];
   const GLfloat *o = other.m();

   result[0] = (_m[0] * o[0]) + (_m[1] * o[3]) + (_m[2] * o[6]);
   result[1] = (_m[0] * o[1]) + (_m[1] * o[4]) + (_m[2] * o[7]);
   result[2] = (_m[0] * o[2]) + (_m[1] * o[5]) + (_m[2] * o[8]);

   result[3] = (_m[3] * o[0]) + (_m[4] * o[3]) + (_m[5] * o[6]);
   result[4] = (_m[3] * o[1]) + (_m[4] * o[4]) + (_m[5] * o[7]);
   result[5] = (_m[3] * o[2]) + (_m[4] * o[5]) + (_m[5] * o[8]);

   result[6] = (_m[6] * o[0]) + (_m[7] * o[3]) + (_m[8] * o[6]);
   result[7] = (_m[6] * o[1]) + (_m[7] * o[4]) + (_m[8] * o[7]);
   result[8] = (_m[6] * o[2]) + (_m[7] * o[5]) + (_m[8] * o[8]);

   return matrix3(result);
}

void matrix3::print() const
{
   logInfo("[%7.4f, %7.4f, %7.4f]\n[%7.4f, %7.4f, %7.4f]\n[%7.4f, %5.2f, %7.4f]\n",
         _m[0],_m[1],_m[2],_m[3],_m[4],_m[5],_m[6],_m[7],_m[8]);
}
