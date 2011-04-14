/*
 * stage.cpp
 *
 *  Created on: Apr 1, 2011
 *      Author: josh
 */
#include "stage.h"
#include "sprite.h"
#include "gltext.h"
#include "Box2D/Box2D.h"


stage::stage(const GLuint w, const GLuint h, bool rotate)
   : _width(w), _height(h), _rotated(false)
{
   _text = new gltext(*this);

   _projection = matrix4::ortho2d(0, _width, 0, _height);

   if (rotate) {
      _rotated = true;

      GLfloat hw = _width/2.0f;
      GLfloat hh = _height/2.0f;

      _projection.translate(hw, hh, 0.0f);
      _projection.rotate(PI/2.0f, 0.0f, 0.0f, 1.0f);

      GLuint t = _width;
      _width = _height;
      _height = t;

      _projection.translate(-hh, -hw, 0.0f);
   }

   // real life acceleration of gravity
   b2Vec2 gravity(0, -9.81f);

   // create world object that will put objects to "sleep" while at rest
   _world = new b2World(gravity, true);

   b2BodyDef groundBodyDef;
   groundBodyDef.position.Set(0,0);

   b2Body *groundBody = _world->CreateBody(&groundBodyDef);
   b2PolygonShape groundBox;
   b2FixtureDef boxShapeDef;
   boxShapeDef.shape = &groundBox;

   b2Vec2 bottomLeft(0, 0);
   b2Vec2 bottomRight(stage::s2w(_width), 0);
   b2Vec2 topLeft(0, stage::s2w(_height));
   b2Vec2 topRight(stage::s2w(_width), stage::s2w(_height));

   // bottom edge
   groundBox.SetAsEdge(bottomLeft, bottomRight);
   groundBody->CreateFixture(&boxShapeDef);

   // left edge
   groundBox.SetAsEdge(bottomLeft, topLeft);
   groundBody->CreateFixture(&boxShapeDef);

   // top edge
   groundBox.SetAsEdge(topLeft, topRight);
   groundBody->CreateFixture(&boxShapeDef);

   // right edge
   groundBox.SetAsEdge(topRight, bottomRight);
   groundBody->CreateFixture(&boxShapeDef);
}

stage::~stage()
{
   sprite::unloadGL();
   ball::unloadGL();
   gltext::unloadGL();

   list<sprite>::cursor c = _sprites.iterate();
   while (c.more()) {
      delete c.next();
   }

   delete _text;
   delete _world;
}

bool stage::setupGL()
{
   if (!sprite::loadGL())
      return false;

   if (!ball::loadGL()) {
      return false;
   }

   if (!gltext::loadGL()) {
      return false;
   }

   _text->loadTexture("textures/font.tga");

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   return true;
}

void stage::addSprite(const sprite * s)
{
   _sprites.add(s);
}

void stage::advance()
{
   _world->Step(0.016f, 10.0f, 10.0f);
}

void stage::render()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

   list<sprite>::cursor c = _sprites.iterate();
   while (c.more()) {
      sprite * s = (sprite*)c.next();
      if (s->body()->IsAwake()) {
         s->render();
      } else {
         if (_sprites.remove(s)) {
            delete s;
         }
      }
   }
}

void stage::touchUp(int x, int y)
{
   if (_rotated) {
      int t = x;
      x = y;
      y = t;
   } else {
      y = _height - y;
   }

   this->addSprite(new ball(*this, x, y, 40));
}
