#include "PhysicsWorld.h"

#include <iostream>


PhysicsWorld::PhysicsWorld()
{
}


PhysicsWorld::~PhysicsWorld()
{
}


void PhysicsWorld::Init()
{
	collisionConfiguration_ = new btDefaultCollisionConfiguration();
	dispatcher_             = new btCollisionDispatcher(collisionConfiguration_);
	overlappingPairCache_   = new btDbvtBroadphase();
	solver_                 = new btSequentialImpulseConstraintSolver;

	dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_, overlappingPairCache_, solver_, collisionConfiguration_);

	boxShape_    = new btBoxShape(btVector3(btScalar(0.5f), btScalar(0.5f), btScalar(0.5f))); //Size of block
	sphereShape_ = new btSphereShape(0.2f); // Bullet radius

	dynamicsWorld_->setGravity(btVector3(btScalar(0.0f), btScalar(0.0f), btScalar(0.0f)));
}

void PhysicsWorld::Destroy()
{
	delete boxShape_;
	delete sphereShape_;

	delete dynamicsWorld_;

	delete solver_;
	delete overlappingPairCache_;
	delete dispatcher_;
	delete collisionConfiguration_;
}

void PhysicsWorld::proc(int mSeconds)
{
	try { 
		dynamicsWorld_->stepSimulation(mSeconds);
	}
	catch (...) {
		std::cout << "Physics error" << std::endl;
	}
}

void PhysicsWorld::AddRigidBody(btRigidBody* rigidBody)
{
	dynamicsWorld_->addRigidBody(rigidBody);
}

void PhysicsWorld::RemoveRigidBody(btRigidBody* rigidBody)
{
	dynamicsWorld_->removeRigidBody(rigidBody);
}