/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#ifndef SPRITE_H_
#define SPRITE_H_

#include "opengl.h"

class stage;
class b2Body;

///
/// Sprite class represents a body in Box2D and can be drawn
/// using OpenGL from a 2D texture. Subclasses of sprite class should
/// define the Box2D body and load their texture into video memory.
///
class sprite {
private:
   /// linked program object handle
   static GLuint s_program;

   /// vertex array attribute handle
   static GLint s_a_position;

   /// uniform handles
   static GLint s_u_texture;
   static GLint s_u_projection;
   static GLint s_u_translation;
   static GLint s_u_rotation;
   static GLint s_u_size;

   GLfloat _verts[8];

protected:
   const stage & _stage;
   b2Body * _body;

   /// width and height of sprite in pixels
   GLuint _width, _height;

   /// Return the initialized OpenGL texture handle. Subclasses must provide
   /// an implementation and some way to load the texture.
   virtual GLuint texture() const { return 0; };

public:
   /// One-time setup of OpenGL. Compile shader program and get program handles.
   /// @return true if loading was successful, false when error occurred
   static bool loadGL();

   /// Teardown OpenGL shader program.
   static void unloadGL();

   /// Create new sprite on the stage with the given width and height in pixels.
   sprite(const stage & s, GLuint w, GLuint h);
   virtual ~sprite();

   inline b2Body* body() const { return _body; }

   ///
   /// Draw the sprite using the sprite shader program. The position and
   /// rotation of the Box2D body is used to create translation and rotation
   /// transformation matrices which are passed into the shader program.
   /// A projection matrix is fetched from the stage instance to transform
   /// the vertices of the triangle strip into OpenGL coordinate system.
   ///
   void render();
};

///
/// Subclass of sprite for simulating and drawing a bouncing ball.
///
class ball : public sprite {
private:
   static GLuint s_texture;

protected:
   inline GLuint texture() const { return s_texture; }

public:
   /// One-time loading of ball texture into OpenGL context.
   static bool loadGL();

   /// Remove ball texture from OpenGL context.
   static void unloadGL();

   /// Create a new ball sprite on the stage at the given position and setup
   /// the Box2D body definition.
   /// @param x x coordinate in pixels
   /// @param y y coordinate in pixels
   /// @param w diameter of the ball in pixels
   ball(const stage & s, GLuint x, GLuint y, GLuint w);
};

#endif
