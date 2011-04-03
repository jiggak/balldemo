/*
 * glutils.h
 *
 *  Created on: Mar 31, 2011
 *      Author: josh
 */
#include "opengl.h"

#ifndef GLUTILS_H_
#define GLUTILS_H_

struct tex_t;

void glutilCheckError(const char* op);
GLuint glutilLoadShader(GLenum shaderType, const char* source);
GLuint glutilCreateProgram(const char* vshader, const char* fshader);
GLuint glutilLoadTexture(const tex_t * texture);

#endif /* GLUTILS_H_ */
