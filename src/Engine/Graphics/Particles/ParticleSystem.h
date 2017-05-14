#pragma once

#include "Particle.h"


class ParticleSystem
{
public:
	friend class ParticleSystemFactory;

	ParticleSystem(glm::vec3 position, int numberOfParticles, int flowPerSecond, float lifeTime, glm::vec3 initialSpeed, glm::vec3 color, bool isRepeat, float scale);
	~ParticleSystem();

	void SetPosition(glm::vec3 position) {
		position_ = position;
	}

	glm::vec3 GetPosition() {
		return position_;
	}

	void SetVelocity(glm::vec3 velocity) {
		initialSpeed_ = velocity;
	}

	glm::vec3 GetVelocity() {
		return initialSpeed_;
	}


	void Draw(Camera* camera);

	float dt();

private:

	float		scale_;
	float		lifeTime_;
	glm::vec3	initialSpeed_;
	glm::vec3	color_;
	int			numberOfParticles_;
	int			flowPerSecond_;
	bool		isRepeat_;

	glm::vec3 position_ = {};

	Model*      model_;
	GLuint      texture_;
	ShaderProg* shaderProg_;
	
	Particle*	particles_;

	sf::Time	prevTime_;

	void SetUniforms(Camera* camera);
	void SetTranslation	(Pipeline* p, Camera* camera, glm::vec4& worldPos);
};

