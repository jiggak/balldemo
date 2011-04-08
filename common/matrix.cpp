#include "matrix.h"
#include "logging.h"

#include <cmath>

#define PI 3.1415926535897932384626433832795f
#define TO_RADIANS(deg) (deg * PI / 180.0f)
#define TO_DEGREES(rad) (rad * 180f / PI)

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

matrix4 matrix4::translation(const GLfloat tx, const GLfloat ty, const GLfloat tz)
{
   const GLfloat m[] = {
         1.0f, 0.0f, 0.0f, tx,
         0.0f, 1.0f, 0.0f, ty,
         0.0f, 0.0f, 1.0f, tz,
         0.0f, 0.0f, 0.0f, 1.0f
   };

   return matrix4(m);
}

matrix4 matrix4::rotation(const GLfloat radians, GLfloat x, GLfloat y, GLfloat z)
{
   GLfloat mag = sqrt(x * x + y * y + z * z);
   GLfloat sinAngle = sin(radians);
   GLfloat cosAngle = cos(radians);

   x /= mag;
   y /= mag;
   z /= mag;

   GLfloat xx = x * x;
   GLfloat yy = y * y;
   GLfloat zz = z * z;
   GLfloat xy = x * y;
   GLfloat yz = y * z;
   GLfloat zx = z * x;
   GLfloat xs = x * sinAngle;
   GLfloat ys = y * sinAngle;
   GLfloat zs = z * sinAngle;
   GLfloat oneMinusCos = 1.0f - cosAngle;

   const GLfloat m[] = {
         (oneMinusCos * xx) + cosAngle, (oneMinusCos * xy) + zs, (oneMinusCos * zx) - ys, 0.0f,
         (oneMinusCos * xy) - zs, (oneMinusCos * yy) + cosAngle, (oneMinusCos * yz) + xs, 0.0f,
         (oneMinusCos * zx) + ys, (oneMinusCos * yz) - xs, (oneMinusCos * zz) + cosAngle, 0.0f,
         0.0f, 0.0f, 0.0f, 1.0f
   };

   return matrix4(m);
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
   *this = *this * matrix4::translation(tx, ty, tz);
}

void matrix4::rotate(const GLfloat radians, GLfloat x, GLfloat y, GLfloat z)
{
   *this = *this * matrix4::rotation(radians, x, y, z);
}

matrix4 matrix4::operator*(const matrix4 & rhs)
{
   GLfloat result[16];
   const GLfloat *r = rhs.m();

   result[0] = (_m[0] * r[0]) + (_m[1] * r[4]) + (_m[2] * r[8])  + (_m[3] * r[12]);
   result[1] = (_m[0] * r[1]) + (_m[1] * r[5]) + (_m[2] * r[9])  + (_m[3] * r[13]);
   result[2] = (_m[0] * r[2]) + (_m[1] * r[6]) + (_m[2] * r[10]) + (_m[3] * r[14]);
   result[3] = (_m[0] * r[3]) + (_m[1] * r[7]) + (_m[2] * r[11]) + (_m[3] * r[15]);

   result[4] = (_m[4] * r[0]) + (_m[5] * r[4]) + (_m[6] * r[8])  + (_m[7] * r[12]);
   result[5] = (_m[4] * r[1]) + (_m[5] * r[5]) + (_m[6] * r[9])  + (_m[7] * r[13]);
   result[6] = (_m[4] * r[2]) + (_m[5] * r[6]) + (_m[6] * r[10]) + (_m[7] * r[14]);
   result[7] = (_m[4] * r[3]) + (_m[5] * r[7]) + (_m[6] * r[11]) + (_m[7] * r[15]);

   result[8]  = (_m[8] * r[0]) + (_m[9] * r[4]) + (_m[10] * r[8])  + (_m[11] * r[12]);
   result[9]  = (_m[8] * r[1]) + (_m[9] * r[5]) + (_m[10] * r[9])  + (_m[11] * r[13]);
   result[10] = (_m[8] * r[2]) + (_m[9] * r[6]) + (_m[10] * r[10]) + (_m[11] * r[14]);
   result[11] = (_m[8] * r[3]) + (_m[9] * r[7]) + (_m[10] * r[11]) + (_m[11] * r[15]);

   result[12] = (_m[12] * r[0]) + (_m[13] * r[4]) + (_m[14] * r[8])  + (_m[15] * r[12]);
   result[13] = (_m[12] * r[1]) + (_m[13] * r[5]) + (_m[14] * r[9])  + (_m[15] * r[13]);
   result[14] = (_m[12] * r[2]) + (_m[13] * r[6]) + (_m[14] * r[10]) + (_m[15] * r[14]);
   result[15] = (_m[12] * r[3]) + (_m[13] * r[7]) + (_m[14] * r[11]) + (_m[15] * r[15]);

   return matrix4(result);
}

matrix4 & matrix4::operator=(const matrix4 & rhs)
{
   const GLfloat *r = rhs.m();
   for (int i=0; i<16; i++) {
      _m[i] = r[i];
   }

   return *this;
}

void matrix4::print() const
{
   logInfo("[%7.4f, %7.4f, %7.4f, %7.4f]\n"
           "[%7.4f, %7.4f, %7.4f, %7.4f]\n"
           "[%7.4f, %5.2f, %7.4f, %7.4f]\n"
           "[%7.4f, %5.2f, %7.4f, %7.4f]",
         _m[0],_m[1],_m[2],_m[3],
         _m[4],_m[5],_m[6],_m[7],
         _m[8],_m[9],_m[10],_m[11],
         _m[12],_m[13],_m[14],_m[15]);
}
