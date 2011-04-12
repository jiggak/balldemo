LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := balldemo

LOCAL_C_INCLUDES := ../common

LOCAL_SRC_FILES += ../../common/Box2D/Collision/b2BroadPhase.cpp \
   ../../common/Box2D/Collision/b2CollideCircle.cpp \
   ../../common/Box2D/Collision/b2CollidePolygon.cpp \
   ../../common/Box2D/Collision/b2Collision.cpp \
   ../../common/Box2D/Collision/b2Distance.cpp \
   ../../common/Box2D/Collision/b2DynamicTree.cpp \
   ../../common/Box2D/Collision/b2TimeOfImpact.cpp \
   ../../common/Box2D/Collision/Shapes/b2CircleShape.cpp \
   ../../common/Box2D/Collision/Shapes/b2PolygonShape.cpp \
   ../../common/Box2D/Common/b2BlockAllocator.cpp \
   ../../common/Box2D/Common/b2Math.cpp \
   ../../common/Box2D/Common/b2Settings.cpp \
   ../../common/Box2D/Common/b2StackAllocator.cpp \
   ../../common/Box2D/Dynamics/b2Body.cpp \
   ../../common/Box2D/Dynamics/b2ContactManager.cpp \
   ../../common/Box2D/Dynamics/b2Fixture.cpp \
   ../../common/Box2D/Dynamics/b2Island.cpp \
   ../../common/Box2D/Dynamics/b2World.cpp \
   ../../common/Box2D/Dynamics/b2WorldCallbacks.cpp \
   ../../common/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
   ../../common/Box2D/Dynamics/Contacts/b2Contact.cpp \
   ../../common/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
   ../../common/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
   ../../common/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
   ../../common/Box2D/Dynamics/Contacts/b2TOISolver.cpp \
   ../../common/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
   ../../common/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
   ../../common/Box2D/Dynamics/Joints/b2GearJoint.cpp \
   ../../common/Box2D/Dynamics/Joints/b2Joint.cpp \
   ../../common/Box2D/Dynamics/Joints/b2LineJoint.cpp \
   ../../common/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
   ../../common/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
   ../../common/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
   ../../common/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
   ../../common/Box2D/Dynamics/Joints/b2WeldJoint.cpp

LOCAL_SRC_FILES += \
   ../../common/glutils.cpp \
   ../../common/matrix.cpp \
   ../../common/tex.cpp \
   ../../common/sprite.cpp \
   ../../common/stage.cpp \
   main.cpp

LOCAL_LDLIBS := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
