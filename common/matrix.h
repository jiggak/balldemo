/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#ifndef MATRIX_H_
#define MATRIX_H_

#include "opengl.h"

#define PI 3.1415926535897932384626433832795f
#define TO_RADIANS(deg) (deg * PI / 180.0f)
#define TO_DEGREES(rad) (rad * 180f / PI)


/// A 4x4 matrix stored in column major order.
class matrix4 {
private:
   GLfloat _m[16];

   /// Common initialization method used by constructors.
   void init(const GLfloat m[16]);

public:
   /// Create identity matrix.
   static matrix4 identity();

   /// Create orthographic projection matrix.
   static matrix4 ortho(const GLint left, const GLint right,
         const GLint bottom, const GLint top,
         const GLint near, const GLint far);

   /// Create 2D orthographic projection matrix with near and far planes
   /// set to -1 and 1 respectively.
   static matrix4 ortho2d(const GLint left, const GLint right,
         const GLint bottom, const GLint top);

   /// Create transform matrix that describes a translation.
   static matrix4 translation(const GLfloat tx, const GLfloat ty, const GLfloat tz);

   /// Create transform matrix that describes a rotation.
   static matrix4 rotation(const GLfloat radians, GLfloat x, GLfloat y, GLfloat z);

   /// Create matrix with all cells set to zero.
   matrix4();

   /// Create matrix from an array of 16 values in column major order.
   matrix4(const GLfloat m[16]);

   /// Create matrix by coping of another matrix.
   matrix4(const matrix4 & other);

   /// Return the matrix as an array of 16 values in column major order.
   inline const GLfloat* m() const { return _m; }

   void scale(const GLfloat sx, const GLfloat sy, const GLfloat sz);
   void translate(const GLfloat tx, const GLfloat ty, const GLfloat tz);
   void rotate(const GLfloat radians, GLfloat x, GLfloat y, GLfloat z);

   /// Copy values from another matrix and return reference to current matrix.
   matrix4 & operator=(const matrix4 & rhs);

   /// Multiply this matrix by another and return the result as a new matrix.
   matrix4 operator*(const matrix4 & rhs);

   /// Print this matrix to the log with the LOG_LEVEL_INFO category.
   /// @see logging.h
   void print() const;
};

#endif /* MATRIX_H_ */
