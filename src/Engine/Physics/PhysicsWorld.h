#pragma once

#include <btBulletDynamicsCommon.h>

class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void Init();
	void Destroy();

	void proc(int mSeconds);

	void AddRigidBody(btRigidBody* rigidBody);
	void RemoveRigidBody(btRigidBody* rigidBody);

	btDiscreteDynamicsWorld* dynamicsWorld_;
	btAlignedObjectArray<btCollisionShape*> collisionShapes_;

	btCollisionShape* boxShape_;
	btCollisionShape* sphereShape_;

private:
	btDefaultCollisionConfiguration*     collisionConfiguration_;
	btCollisionDispatcher*               dispatcher_;
	btBroadphaseInterface*               overlappingPairCache_;
	btSequentialImpulseConstraintSolver* solver_;
};

