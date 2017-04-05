#include "ParticleSystemFactory.h"
#include "../../../src/Application/Application.h"

ParticleSystemFactory::ParticleSystemFactory()
{

}

ParticleSystemFactory::~ParticleSystemFactory()
{

}

ParticleSystem* ParticleSystemFactory::CreateParticleSystem(ParticleSystemInfo assets)
{
	ParticleSystem* particleSystem = new ParticleSystem(assets.numberOfParticles_, assets.lifeTime_, assets.initialSpeed_);
	
	particleSystem->model_		= modelManager_.Get	 (assets.modelName_);
	particleSystem->texture_	= textureManager_.Get(assets.textureName_);
	particleSystem->shaderProg_ = APPLICATION->shaderManager_.Get(assets.shaderNames_);

	return particleSystem;
}