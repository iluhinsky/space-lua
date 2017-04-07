#include "GraphicsWorld.h"



GraphicsWorld::GraphicsWorld()
{
}


GraphicsWorld::~GraphicsWorld()
{
	delete particleSystem_;
	delete manager_;
}

void GraphicsWorld::Init()
{
	manager_        = new GraphicsObjectManager;
	particleSystem_ = new ParticleSystem;
}

ParticleSystem* GraphicsWorld::GetParticleSystem()
{
	return particleSystem_;
}

GraphicsObjectManager* GraphicsWorld::GetManager()
{
	return manager_;
}