#pragma once

#include "Particle.h"


class ParticleSystem
{
public:
	friend class ParticleSystemFactory;

	ParticleSystem(glm::vec3 position, int numberOfParticles, int flowPerSecond, float lifeTime, glm::vec3 initialSpeed);
	~ParticleSystem();

	void Draw(Camera* camera);

	float dt();

private:

	float		scale_;
	float		lifeTime_;
	glm::vec3	initialSpeed_;
	int			numberOfParticles_;
	int			flowPerSecond_;

	glm::vec3 position_ = {};

	Model*      model_;
	GLuint      texture_;
	ShaderProg* shaderProg_;
	
	Particle*	particles_;

	sf::Time	prevTime_;

	void SetUniforms	(Camera* camera, glm::vec3& particlePos, Particle particle);
	void SetTranslation	(Pipeline* p, Camera* camera, glm::vec4& worldPos);
};

