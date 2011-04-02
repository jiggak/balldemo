/*
 * glutils.cpp
 *
 *  Created on: Mar 31, 2011
 *      Author: josh
 */
#include "glutils.h"
#include "logging.h"
#include <stdlib.h>

void glutilCheckError(const char* op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        logError("%s() glError (0x%x)\n", op, error);
    }
}

GLuint glutilLoadShader(GLenum shaderType, const char* source) {
	// create shader object
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0)
    	return 0;

    // load shader source and compile
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	// verify shader was compiled successfully
	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen) {
			char* buf = (char*) malloc(infoLen);
			if (buf) {
				glGetShaderInfoLog(shader, infoLen, NULL, buf);
				logError("Could not compile shader %d:\n%s\n", shaderType, buf);
				free(buf);
			}

			glDeleteShader(shader);
			return 0;
		}
	}

    return shader;
}

GLuint glutilCreateProgram(const char* vshader, const char* fshader) {
    GLuint vertexShader = glutilLoadShader(GL_VERTEX_SHADER, vshader);
    if (!vertexShader) {
        return 0;
    }

    GLuint fragmentShader = glutilLoadShader(GL_FRAGMENT_SHADER, fshader);
    if (!fragmentShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (!program)
    	return 0;

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	// verify program was linked successfully
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (!linked) {
		GLint bufLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
		if (bufLength) {
			char* buf = (char*) malloc(bufLength);
			if (buf) {
				glGetProgramInfoLog(program, bufLength, NULL, buf);
				logError("Could not link program:\n%s\n", buf);
				free(buf);
			}
		}

		glDeleteProgram(program);
		return 0;
    }

    return program;
}
