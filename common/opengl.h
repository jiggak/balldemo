/*
 * opengl.h
 *
 *  Created on: Mar 31, 2011
 *      Author: josh
 */

#ifdef ANDROID

#include <GLES2/gl2.h>

#elif IOS

#include <OpenGLES/ES2/gl.h>

#else

#include <GL/glew.h>

#endif
