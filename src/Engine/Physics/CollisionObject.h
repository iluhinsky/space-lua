#pragma once

#include <btBulletDynamicsCommon.h>

#include "..\..\Game\CollisionObjectTypes.h"

class CollisionObject
{
public:
	CollisionObject();
	~CollisionObject();

	virtual void InitRigidBody() = 0;

	CollisionObjectType GetType();

protected:
	CollisionObjectType   collisionType_;

	btCollisionShape*     shape_;
	btDefaultMotionState* motionState_;
	btRigidBody*          body_;
};

