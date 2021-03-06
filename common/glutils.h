/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#include "opengl.h"

#ifndef GLUTILS_H_
#define GLUTILS_H_

struct tex_t;
struct asset_t;

///
/// Print the error code(s) generated by the last OpenGL call.
/// @param op name of operation that caused the error
///
void glutilCheckError(const char* op);

///
/// Compile shader source code from asset. If shader fails to compile an
/// error code and reason for compile failure is printed to the error log.
/// @param shaderType type of shader: GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
/// @param source shader source code asset
/// @return compiled shader handle, or zero if compile failed
///
GLuint glutilLoadShader(GLenum shaderType, const asset_t * source);

///
/// Compile vertex shader and fragment shader and link into shader program.
/// @param vsPath relative asset path to vertex shader file
/// @param fsPath relative asset path to fragment shader file
/// @return linked shader program handle, or zero if
///
GLuint glutilCreateProgram(const char* vsPath, const char* fsPath);

///
/// Load 2D texture into video memory. Format is assumed to be 32bit RGBA.
/// @param texture asset loaded through texture functions
/// @return texture handle
/// @see tex.h
///
GLuint glutilLoadTexture(const tex_t * texture);

#endif /* GLUTILS_H_ */
