#pragma once

#include <btBulletDynamicsCommon.h>

#include "..\..\Game\CollisionObjectTypes.h"

class CollisionObject
{
public:
	CollisionObject();
	~CollisionObject();

	virtual void InitRigidBody() = 0;

protected:
	CollisionObjectType   CollisionType_;

	btCollisionShape*     shape_;
	btDefaultMotionState* motionState_;
	btRigidBody*          body_;
};

