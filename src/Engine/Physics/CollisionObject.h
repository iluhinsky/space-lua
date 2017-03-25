#pragma once

#include <btBulletDynamicsCommon.h>

class CollisionObject
{
public:
	CollisionObject();
	~CollisionObject();

	virtual void InitRigidBody() = 0;

protected:
	btCompoundShape*      shape_;
	btDefaultMotionState* motionState_;
	btRigidBody*          body_;
};

