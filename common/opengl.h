/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */

///
/// Preprocessor macros for selecting the platform specific OpenGL headers.
/// For Android and iOS include OpenGL ES 2 headers, for all other platforms
/// use the GLEW library to get desktop OpenGL 2.
///

#ifdef ANDROID
  #include <GLES2/gl2.h>
#elif __IPHONE_OS_VERSION_MIN_REQUIRED
  #include <OpenGLES/ES2/gl.h>
#else
  #include <GL/glew.h>
#endif
