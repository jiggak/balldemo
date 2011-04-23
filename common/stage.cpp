/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#include "stage.h"
#include "sprite.h"
#include "gltext.h"
#include "Box2D/Box2D.h"

#include <sys/time.h>
#include <algorithm>
#include <cmath>


// High precision time function returns current time in seconds.
static double now()
{
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_sec + tv.tv_usec/1000000.0;
}


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

      std::swap(_width, _height);

      _projection.translate(-hh, -hw, 0.0f);
   }

   // real life acceleration of gravity
   b2Vec2 gravity(0, -9.81f);

   // create world object that will put objects to "sleep" while at rest
   _world = new b2World(gravity, true);

   // disable auto-clear forces, we will clear them manually after each frame
   _world->SetAutoClearForces(false);

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

   _text->loadTexture("textures/font_green.tga");

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   _currentTime = now();
   _timeAccumulator = 0.0;

   return true;
}

double stage::step()
{
   const double dt = 1/60.0;

   double newTime = now();
   double frameTime = newTime - _currentTime;
   _currentTime = newTime;

   _timeAccumulator += frameTime;

   while (_timeAccumulator >= dt) {
      _world->Step(dt, 10.0f, 10.0f);
      _timeAccumulator -= dt;
   }
   
   _world->ClearForces();

   return frameTime;
}

void stage::queueAction(action_type_t type, float x, float y)
{
   action_t *action = new action_t(type, x, y);

   if (type != ACTION_TYPE_TILT) {
      if (_rotated) {
         std::swap(action->x, action->y);
      } else {
         action->y = _height - action->y;
      }
   }

   _actions.append((const action_t *)action);
}

void stage::render()
{
   glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

   const action_t * a = _actions.shift();
   while (a) {
      switch (a->type) {
      case ACTION_TYPE_TOUCH_UP:
         _sprites.append(new ball(*this, a->x, a->y, 32));
         break;
      case ACTION_TYPE_TILT:
         b2Vec2 gravity(a->x, a->y);
         _world->SetGravity(gravity);
         break;
      }

      delete a;
      a = _actions.shift();
   }

   double ftime = step();

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

   _text->printf(0, _height-_text->char_height(), "%d fps, %.3f s, %d sprites",
         int(1.0 / ftime), ftime, _sprites.count());
}
