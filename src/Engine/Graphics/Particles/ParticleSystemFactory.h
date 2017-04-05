#pragma once
#include "ParticleSystem.h"

struct ParticleSystemInfo
{
	std::string modelName_;
	std::string textureName_;

	ShaderNames shaderNames_;

	int		numberOfParticles_; 
	float	lifeTime_; 
	float	initialSpeed_;
};

class ParticleSystemFactory
{
public:
	ParticleSystemFactory();
	~ParticleSystemFactory();

	ParticleSystem* CreateParticleSystem(ParticleSystemInfo assets);

private:

	//ShaderProgManager shaderManager_;
	TextureManager	  textureManager_;
	ModelManager	  modelManager_;
};

