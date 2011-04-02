/*
 * glutils.h
 *
 *  Created on: Mar 31, 2011
 *      Author: josh
 */
#ifndef GLUTILS_H_
#define GLUTILS_H_

#include "opengl.h"

void glutilCheckError(const char* op);
GLuint glutilLoadShader(GLenum shaderType, const char* source);
GLuint glutilCreateProgram(const char* vshader, const char* fshader);

#endif /* GLUTILS_H_ */
