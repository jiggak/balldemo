/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#ifndef STAGE_H_
#define STAGE_H_

#include "opengl.h"
#include "matrix.h"
#include "list.h"

// Box2D uses MKS (meters, kilograms, seconds) units and is tuned to work well
// with moving objects sized between 0.1 and 10.0 (100 cm to 10 m).
// We need a ratio to convert back and forth to screen units.
#define UNIT_RATIO 50.0f


/// Type of action.
typedef enum {
   ACTION_TYPE_TOUCH_DOWN,
   ACTION_TYPE_TOUCH_UP,
   ACTION_TYPE_TOUCH_MOVE,
   ACTION_TYPE_TILT
} action_type_t;


/// Action structure containing the type of action and x,y coordinates.
/// Touch actions use x,y coordinates in screen space. Tilt action uses
/// x,y values to represent a force vector in the range -9.18 to 9.18.
typedef struct action_t {
   action_t(action_type_t t_, float x_, float y_) : type(t_), x(x_), y(y_) { }
   action_type_t type;
   float x, y;
} action_t;


class gltext;
class sprite;
class b2World;

///
/// The stage class manages the Box2D world object, draws sprite objects, and
/// handles input actions.
///
/// The size of the stage and the sprite objects are specified in pixels. The
/// origin of the stage is in the bottom left corner. In OpenGL clip coordinate
/// space the bottom left corner is (-1.0,-1.0) and the top right is (1.0,1.0).
/// The stage class provides a projection matrix used for placing local object
/// coordinates into OpenGL clip coordinates.
///
class stage {
private:
   GLuint _width, _height;
   bool _rotated;

   matrix4 _projection;
   b2World * _world;
   list<sprite> _sprites;

   gltext * _text;

   /// Perform time step in Box2D simulation.
   /// @return time in seconds since last call to step()
   double step();

   double _currentTime, _timeAccumulator;

   list<action_t> _actions;

public:
   /// Create stage with the given dimensions in screen units. Optionally the
   /// stage can be rotated 90 degrees. When rotation is selected, width and
   /// height are swapped automatically.
   /// @param w width in pixels
   /// @param h height in pixels
   /// @param rotate true if stage output should rotate 90 degrees CW
   stage(const GLuint w, const GLuint h, bool rotate=false);
   ~stage();

   /// One-time setup of OpenGL. This method handles calling setupGL()
   /// methods on all other classes that require OpenGL setup.
   /// @return true if setup was successful, false when error occurred
   bool setupGL();

   /// Convert from screen units to Box2D world units.
   inline static float s2w(unsigned int i) { return i / UNIT_RATIO; }

   /// Convert from Box2D world units to screen units.
   inline static unsigned int w2s(float f) { return f * UNIT_RATIO; }

   inline const GLuint width() const { return _width; }
   inline const GLuint height() const { return _height; }

   /// Returns projection matrix used to transform object coordinates
   /// into OpenGL clip coordinates.
   inline const matrix4 & projection() const { return _projection; }

   inline b2World* world() const { return _world; }

   /// Queue new action to be consumed by the render() method. This method does
   /// not perform locking on the action queue and therefore it's important
   /// that queueAction() and render() are called by the same thread.
   void queueAction(action_type_t type, float x, float y);

   /// Advance the simulation, consume actions, and render the frame.
   /// This method will most likely be the only call inside of render/game loop.
   void render();
};

#endif /* STAGE_H_ */
