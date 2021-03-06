UNAME=$(shell uname)
CC=g++

ifeq ($(UNAME),Linux)
   LDFLAGS=-lGL -lGLEW -lglut
   CFLAGS=-g -Wall -I../common
endif
ifeq ($(UNAME),Darwin)
   LDFLAGS=-framework GLUT -framework OpenGL -L/opt/local/lib -lGLEW
   CFLAGS=-g -Wall -I../common -I/opt/local/include
endif
ifneq (,$(findstring MINGW,$(UNAME)))
   # to distribute .exe add -static-libgcc -static-libstdc++ flags to avoid
   # having to distribute gcc and stdc++ .dll's
   LDFLAGS=-lglew32 -lglut -lglu32 -lopengl32
   CFLAGS=-g -Wall -I../common
endif

OUTPUT=balldemo

SRC+=../common/Box2D/Collision/b2BroadPhase.cpp \
   ../common/Box2D/Collision/b2CollideCircle.cpp \
   ../common/Box2D/Collision/b2CollidePolygon.cpp \
   ../common/Box2D/Collision/b2Collision.cpp \
   ../common/Box2D/Collision/b2Distance.cpp \
   ../common/Box2D/Collision/b2DynamicTree.cpp \
   ../common/Box2D/Collision/b2TimeOfImpact.cpp \
   ../common/Box2D/Collision/Shapes/b2CircleShape.cpp \
   ../common/Box2D/Collision/Shapes/b2PolygonShape.cpp \
   ../common/Box2D/Common/b2BlockAllocator.cpp \
   ../common/Box2D/Common/b2Math.cpp \
   ../common/Box2D/Common/b2Settings.cpp \
   ../common/Box2D/Common/b2StackAllocator.cpp \
   ../common/Box2D/Dynamics/b2Body.cpp \
   ../common/Box2D/Dynamics/b2ContactManager.cpp \
   ../common/Box2D/Dynamics/b2Fixture.cpp \
   ../common/Box2D/Dynamics/b2Island.cpp \
   ../common/Box2D/Dynamics/b2World.cpp \
   ../common/Box2D/Dynamics/b2WorldCallbacks.cpp \
   ../common/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
   ../common/Box2D/Dynamics/Contacts/b2Contact.cpp \
   ../common/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
   ../common/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
   ../common/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
   ../common/Box2D/Dynamics/Contacts/b2TOISolver.cpp \
   ../common/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
   ../common/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
   ../common/Box2D/Dynamics/Joints/b2GearJoint.cpp \
   ../common/Box2D/Dynamics/Joints/b2Joint.cpp \
   ../common/Box2D/Dynamics/Joints/b2LineJoint.cpp \
   ../common/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
   ../common/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
   ../common/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
   ../common/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
   ../common/Box2D/Dynamics/Joints/b2WeldJoint.cpp

SRC+= \
   ../common/logging.cpp \
   ../common/glutils.cpp \
   ../common/matrix.cpp \
   ../common/tex.cpp \
   ../common/gltext.cpp \
   ../common/sprite.cpp \
   ../common/stage.cpp \
   main.cpp

OBJ=$(SRC:.cpp=.o)

all: $(SRC) $(OUTPUT)

# mingw for some crazzy reason has a ton of linker errors if the object files
# appear after LDFLAGS, so swap them (doesn't seems to effect Linux or OSX)

$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OUTPUT) $(OBJ)
