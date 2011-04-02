/*
 * stage.cpp
 *
 *  Created on: Apr 1, 2011
 *      Author: josh
 */
#include "stage.h"
#include "sprite.h"

stage::stage(const GLuint w, const GLuint h)
   : _width(w), _height(h)
{
   _projection = matrix3::ortho2d(0, w, 0, h);

   // TODO create a list of sprites
   _sprite = new sprite(*this, 50, 50);
}

stage::~stage()
{
   delete _sprite;
}

bool stage::setupGl(const GLuint w, const GLuint h)
{
   if (!sprite::setupGl())
      return false;

   glViewport(0, 0, w, h);

   return true;
}

const GLuint stage::width() const { return _width; }
const GLuint stage::height() const { return _height; }

const matrix3 & stage::projection() const { return _projection; }

void stage::render()
{
   glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

   _sprite->render();
}
