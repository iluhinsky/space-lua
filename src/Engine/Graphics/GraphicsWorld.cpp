#include "GraphicsWorld.h"



GraphicsWorld::GraphicsWorld()
{
}


GraphicsWorld::~GraphicsWorld()
{
	delete particleSystem_;
}

void GraphicsWorld::Init()
{
	particleSystem_ = new ParticleSystem;
}

ParticleSystem* GraphicsWorld::GetParticleSystem()
{
	return particleSystem_;
}