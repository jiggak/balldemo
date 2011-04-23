/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#ifndef GLTEXT_H_
#define GLTEXT_H_

#include "opengl.h"

class stage;

///
/// Class for drawing fixed width text from a texture with OpenGL ES 2.0.
/// Font texture files must contain horizontal series of characters in ASCII
/// order starting with space (char 32) to tilde (char 126).
///
/// All text printing functions assume x,y coordinates are screen relative
/// pixel coordinates with the origin in the bottom left corner.
///
class gltext {
private:
   /// linked program object handle
   static GLuint s_program;

   /// vertex array attribute handle
   static GLint s_a_position;

   /// uniform handles
   static GLint s_u_texture;
   static GLint s_u_projection;
   static GLint s_u_translation;
   static GLint s_u_char_size;
   static GLint s_u_char_scale;
   static GLint s_u_char_offset;

   const stage & _stage;

   /// character width
   int _cwidth;

   /// character height
   int _cheight;

   GLfloat _verts[8];
   GLuint _texture;

   /// Prepare OpenGL context for printing characters from texture.
   void beforePrint();

   /// Print single character from texture at the given coordinate.
   /// @param x x coordinate
   /// @param y y coordiante
   /// @param c character to print
   void _putc(int x, int y, char c);

   /// Cleanup OpenGL context.
   void afterPrint();

public:
   /// Create instance. Instances must be further initialized before use.
   /// @param s stage where text will be printed
   /// @see loadTexture()
   /// @see loadGL()
   gltext(const stage & s) : _stage(s) { }

   ~gltext();

   /// One-time setup of OpenGL. Compile shader program and get program handles.
   /// @return true if loading was successful, false when error occurred
   static bool loadGL();

   /// Teardown OpenGL shader program.
   static void unloadGL();

   inline int char_width() const { return _cwidth; }
   inline int char_height() const { return _cheight; }

   /// Load font texture asset and upload to graphics memory.
   /// @param path font texture file as asset relative path
   /// @return returns false if texture asset was not found
   bool loadTexture(const char * path);

   /// Print single character at the coordinate.
   void putc(int x, int y, char c);

   /// Print string of characters at the coordinate.
   void print(int x, int y, const char *s);

   /// Print string using printf style formatting.
   void printf(int x, int y, const char *fmt, ...);
};

#endif /* GLTEXT_H_ */
