/*
 * matrix.h
 *
 *  Created on: Mar 30, 2011
 *      Author: josh
 */
#ifndef MATRIX_H_
#define MATRIX_H_

#include "opengl.h"

class matrix3 {
private:
   GLfloat _m[9];

   void init(const GLfloat m[9]);

public:
   static matrix3 identity();
   static matrix3 ortho2d(const GLint left, const GLint right,
         const GLint bottom, const GLint top);

   matrix3();
   matrix3(const GLfloat m[9]);
   matrix3(const matrix3 & other);

   const GLfloat* m() const;

   void scale(const GLfloat sx, const GLfloat sy, const GLfloat sz);

   matrix3 operator*(const matrix3 & other);

   void print() const;
};

#endif /* MATRIX_H_ */
