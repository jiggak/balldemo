/*
 * stage.h
 *
 *  Created on: Apr 1, 2011
 *      Author: josh
 */

#ifndef STAGE_H_
#define STAGE_H_

#include "opengl.h"
#include "matrix.h"
#include "list.h"

// box2d uses MKS (meters, kilograms, seconds) units
// we need a ratio to convert back and forth to screen units
#define UNIT_RATIO 40.0f

typedef enum {
   ACTION_TYPE_TOUCH_DOWN,
   ACTION_TYPE_TOUCH_UP,
   ACTION_TYPE_TOUCH_MOVE,
   ACTION_TYPE_TILT
} action_type_t;

typedef struct action_t {
   action_t(action_type_t t_, float x_, float y_) : type(t_), x(x_), y(y_) { }
   action_type_t type;
   float x, y;
} action_t;

class gltext;
class sprite;
class b2World;

class stage {
private:
   GLuint _width, _height;
   bool _rotated;

   matrix4 _projection;
   b2World * _world;
   list<sprite> _sprites;

   gltext * _text;

   double step();
   double _currentTime, _timeAccumulator;

   list<action_t> _actions;

public:
   stage(const GLuint w, const GLuint h, bool rotate=false);
   ~stage();

   bool setupGL();

   inline static float s2w(unsigned int i) { return i / UNIT_RATIO; }
   inline static unsigned int w2s(float f) { return f * UNIT_RATIO; }

   inline const GLuint width() const { return _width; }
   inline const GLuint height() const { return _height; }

   inline const matrix4 & projection() const { return _projection; }

   inline b2World* world() const { return _world; }

   void queueAction(action_type_t type, float x, float y);

   void render();
};

#endif /* STAGE_H_ */
