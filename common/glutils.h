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
struct asset_t;

void glutilCheckError(const char* op);
GLuint glutilLoadShader(GLenum shaderType, const asset_t * source);
GLuint glutilCreateProgram(const char* vsPath, const char* fsPath);
GLuint glutilLoadTexture(const tex_t * texture);

#endif /* GLUTILS_H_ */
