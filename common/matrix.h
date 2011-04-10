/*
 * matrix.h
 *
 *  Created on: Mar 30, 2011
 *      Author: josh
 */
#ifndef MATRIX_H_
#define MATRIX_H_

#include "opengl.h"

#define PI 3.1415926535897932384626433832795f
#define TO_RADIANS(deg) (deg * PI / 180.0f)
#define TO_DEGREES(rad) (rad * 180f / PI)

class matrix4 {
private:
   GLfloat _m[16];

   void init(const GLfloat m[16]);

public:
   static matrix4 identity();

   static matrix4 ortho(const GLint left, const GLint right,
         const GLint bottom, const GLint top,
         const GLint near, const GLint far);

   static matrix4 ortho2d(const GLint left, const GLint right,
         const GLint bottom, const GLint top);

   static matrix4 translation(const GLfloat tx, const GLfloat ty, const GLfloat tz);

   static matrix4 rotation(const GLfloat radians, GLfloat x, GLfloat y, GLfloat z);

   matrix4();
   matrix4(const GLfloat m[16]);
   matrix4(const matrix4 & other);

   const GLfloat* m() const;

   void scale(const GLfloat sx, const GLfloat sy, const GLfloat sz);
   void translate(const GLfloat tx, const GLfloat ty, const GLfloat tz);
   void rotate(const GLfloat radians, GLfloat x, GLfloat y, GLfloat z);

   matrix4 & operator=(const matrix4 & rhs);
   matrix4 operator*(const matrix4 & rhs);

   void print() const;
};

#endif /* MATRIX_H_ */
