#pragma once
#include "../GraphicsObject/GraphicsObject.h"

class Particle
{
public:
	Particle();
	~Particle();

	glm::vec3 GetPosition();
	void Update(float dt, int flowPerSecond_, int numberOfParticles_, bool isRepeat);
	void SetVelocity(glm::vec3 initialSpeed);
	void SetLifeTime(float lifeTime);

	void Enable(float dt, int flowPerSecond, int numberOfParticles)
	{
		if (rand() % numberOfParticles < int(dt*flowPerSecond))
		isEnabled = true;
	}

	void Disable()
	{
		isEnabled = false;
	}

	bool isEnable()
	{
		return isEnabled;
	}

	float GetEstimatedTime()
	{
		return estimatedTime_;
	}

private:
	glm::vec3 position_ = {};
	glm::vec3 velocity_;

	float estimatedTime_;
	float lifeTime_;

	bool isEnabled = false;

	glm::vec3 GenRandVector();
};

