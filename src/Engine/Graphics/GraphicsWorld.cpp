#include "GraphicsWorld.h"
#include "Particles/ParticleSystemFactory.h"


GraphicsWorld::GraphicsWorld()
{
	manager_ = new GraphicsObjectManager;
}


GraphicsWorld::~GraphicsWorld()
{
	delete particleSystem_;
	delete manager_;

	printf("ENDDDDDD\n\n\n");
}

void GraphicsWorld::Init()
{
	ParticleSystemInfo assets = {};

	//For first design

	assets.initialSpeed_		= 1.0f; 
	assets.lifeTime_			= 1.0f;
	assets.numberOfParticles_	= 1;
	
	assets.modelName_	= "particle.3ds";
	assets.textureName_ = "face.png";
	assets.shaderNames_ = ShaderNames{"block_vertex.glsl", "block_fragment.glsl" };
	
	ParticleSystemFactory factory = ParticleSystemFactory();
	particleSystem_ = factory.CreateParticleSystem(assets);
}

ParticleSystem* GraphicsWorld::GetParticleSystem()
{
	return particleSystem_;
}

GraphicsObjectManager* GraphicsWorld::GetManager()
{
	return manager_;
}