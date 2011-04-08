#include "matrix.h"
#include "logging.h"

matrix4 matrix4::identity()
{
   const GLfloat m[] = {
         1.0f, 0.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f, 0.0f,
         0.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
   };

   return matrix4(m);
}

matrix4 matrix4::ortho(const GLint left, const GLint right,
      const GLint bottom, const GLint top,
      const GLint near, const GLint far)
{
   const GLfloat m[] = {
         2 / (GLfloat)(right - left), 0.0f, 0.0f, -(GLfloat)(right + left)/(right - left),
         0.0f, 2 / (GLfloat)(top - bottom), 0.0f, -(GLfloat)(top + bottom)/(top - bottom),
         0.0f, 0.0f, -2.0f / (far - near), -(GLfloat)(far + near)/(far - near),
         0.0f, 0.0f, 0.0f, 1.0f
   };

   return matrix4(m);
}

matrix4 matrix4::ortho2d(const GLint left, const GLint right,
      const GLint bottom, const GLint top)
{
   const GLfloat m[] = {
         2 / (GLfloat)(right - left), 0.0f, 0.0f, -1.0f,
         0.0f, 2 / (GLfloat)(top - bottom), 0.0f, -1.0f,
         0.0f, 0.0f, -1.0f, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
   };

   return matrix4(m);
   //return matrix4::ortho(left, right, bottom, top, -1, 1);
}

matrix4::matrix4()
{
   for (int i=0; i<16; i++) {
      _m[i] = 0.0f;
   }
}

matrix4::matrix4(const GLfloat m[16])
{
   init(m);
}

matrix4::matrix4(const matrix4 & other)
{
   init(other.m());
}

void matrix4::init(const GLfloat m[16])
{
   for (int i=0; i<16; i++) {
      _m[i] = m[i];
   }
}

const GLfloat* matrix4::m() const { return _m; }

void matrix4::scale(const GLfloat sx, const GLfloat sy, const GLfloat sz)
{
   _m[0]  *= sx;
   _m[4]  *= sx;
   _m[8]  *= sx;
   _m[12] *= sx;

   _m[1]  *= sy;
   _m[5]  *= sy;
   _m[9]  *= sy;
   _m[13] *= sy;

   _m[2]  *= sz;
   _m[9]  *= sz;
   _m[10] *= sz;
   _m[14] *= sz;
}

void matrix4::translate(const GLfloat tx, const GLfloat ty, const GLfloat tz)
{
   _m[3]  += (_m[0] * tx)  + (_m[1] * ty)  + (_m[2] * tz);
   _m[7]  += (_m[4] * tx)  + (_m[5] * ty)  + (_m[6] * tz);
   _m[11] += (_m[8] * tx)  + (_m[9] * ty)  + (_m[10] * tz);
   _m[15] += (_m[12] * tx) + (_m[13] * ty) + (_m[14] * tz);
}

matrix4 matrix4::operator*(const matrix4 & other)
{
   GLfloat result[16];
   const GLfloat *o = other.m();

   result[0] = (_m[0] * o[0]) + (_m[1] * o[4]) + (_m[2] * o[8])  + (_m[3] * o[12]);
   result[1] = (_m[0] * o[1]) + (_m[1] * o[5]) + (_m[2] * o[9])  + (_m[3] * o[13]);
   result[2] = (_m[0] * o[2]) + (_m[1] * o[6]) + (_m[2] * o[10]) + (_m[3] * o[14]);
   result[3] = (_m[0] * o[3]) + (_m[1] * o[7]) + (_m[2] * o[11]) + (_m[3] * o[15]);

   result[4] = (_m[4] * o[0]) + (_m[5] * o[4]) + (_m[6] * o[8])  + (_m[7] * o[12]);
   result[5] = (_m[4] * o[1]) + (_m[5] * o[5]) + (_m[6] * o[9])  + (_m[7] * o[13]);
   result[6] = (_m[4] * o[2]) + (_m[5] * o[6]) + (_m[6] * o[10]) + (_m[7] * o[14]);
   result[7] = (_m[4] * o[3]) + (_m[5] * o[7]) + (_m[6] * o[11]) + (_m[7] * o[15]);

   result[8]  = (_m[8] * o[0]) + (_m[9] * o[4]) + (_m[10] * o[8])  + (_m[11] * o[12]);
   result[9]  = (_m[8] * o[1]) + (_m[9] * o[5]) + (_m[10] * o[9])  + (_m[11] * o[13]);
   result[10] = (_m[8] * o[2]) + (_m[9] * o[6]) + (_m[10] * o[10]) + (_m[11] * o[14]);
   result[11] = (_m[8] * o[3]) + (_m[9] * o[7]) + (_m[10] * o[11]) + (_m[11] * o[15]);

   result[12] = (_m[12] * o[0]) + (_m[13] * o[4]) + (_m[14] * o[8])  + (_m[15] * o[12]);
   result[13] = (_m[12] * o[1]) + (_m[13] * o[5]) + (_m[14] * o[9])  + (_m[15] * o[13]);
   result[14] = (_m[12] * o[2]) + (_m[13] * o[6]) + (_m[14] * o[10]) + (_m[15] * o[14]);
   result[15] = (_m[12] * o[3]) + (_m[13] * o[7]) + (_m[14] * o[11]) + (_m[15] * o[15]);

   return matrix4(result);
}

void matrix4::print() const
{
   logInfo("[%7.4f, %7.4f, %7.4f, %7.4f]\n[%7.4f, %7.4f, %7.4f, %7.4f]\n[%7.4f, %5.2f, %7.4f, %7.4f]\n[%7.4f, %5.2f, %7.4f, %7.4f]\n",
         _m[0],_m[1],_m[2],_m[3],_m[4],_m[5],_m[6],_m[7],_m[8], _m[9],_m[10],_m[11],_m[12],_m[13],_m[14],_m[15]);
}
