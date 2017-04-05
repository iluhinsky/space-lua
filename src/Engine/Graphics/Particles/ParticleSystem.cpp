#include "ParticleSystem.h"
#include "../../../../src/Application/Application.h"



ParticleSystem::ParticleSystem(glm::vec3 position, int numberOfParticles, int flowPerSecond, float lifeTime, glm::vec3 initialSpeed)
{
	scale_ = 0.1;
	numberOfParticles_ = numberOfParticles;
	lifeTime_ = lifeTime;
	initialSpeed_ = initialSpeed;
	position_ = position;

	if (flowPerSecond > numberOfParticles)
	{
		flowPerSecond_ = numberOfParticles;
	}
	else
	{
		flowPerSecond_ = flowPerSecond;
	}

	particles_ = new Particle[numberOfParticles_];

	for (int i = 0; i < numberOfParticles_; i++)
	{
		particles_[i].SetVelocity(initialSpeed_);
		particles_[i].SetLifeTime(lifeTime_);
	}

	prevTime_ = APPLICATION->getTime();
}


ParticleSystem::~ParticleSystem()
{
	delete[] particles_;
}

void ParticleSystem::Draw(Camera* camera)
{
	shaderProg_->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Mesh currMesh = model_->_meshes[0];
		
	glBindTexture(GL_TEXTURE_2D, texture_);
	glBindBuffer(GL_ARRAY_BUFFER, currMesh._VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, currMesh._offset._stride, (void*)currMesh._offset._vertex);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, currMesh._offset._stride, (void*)currMesh._offset._uvtex);

	float deltaT = dt();

	for (int i = 0; i < numberOfParticles_; i++)
	{
		SetUniforms(camera, position_ + particles_[i].GetPosition(), particles_[i]);
		glDrawArrays(GL_TRIANGLES, 0, model_->_meshes[0]._nVerticles);

		particles_[i].Enable(deltaT, flowPerSecond_, numberOfParticles_);
		particles_[i].Update(deltaT);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDisable(GL_BLEND);
}

void ParticleSystem::SetUniforms(Camera* camera, glm::vec3& particlePos, Particle particle)
{
	sf::Vector2u size = APPLICATION->GetWindowSize();

	Pipeline p;

	SetTranslation(&p, camera, glm::vec4{particlePos, 1});

	p.SetPerspectiveProj(60.0f, size.x, size.y, 1.0f, 10000.0f);
	p.CalculateMatrices();

	glm::mat4 ModelViewMatrix = p.GetViewMatrix() * p.GetModelMatrix();
	glm::mat4 MVPMatrix			= p.GetProjMatrix() * ModelViewMatrix;
	
	glm::mat3 rot = glm::mat3(	ModelViewMatrix[0][0], ModelViewMatrix[1][0], ModelViewMatrix[2][0], 
								ModelViewMatrix[0][1], ModelViewMatrix[1][1], ModelViewMatrix[2][1], 
								ModelViewMatrix[0][2], ModelViewMatrix[1][2], ModelViewMatrix[2][2]);


	
	shaderProg_->UniformMatrix4x4(shaderProg_->GetUniformLocation("gWVP"), MVPMatrix);
	shaderProg_->UniformMatrix3x3(shaderProg_->GetUniformLocation("gRot"), rot);
	//shaderProg_->UniformMatrix4x4(shaderProg_->GetUniformLocation("gWV"), ModelViewMatrix);

	shaderProg_->UniformInt(shaderProg_->GetUniformLocation("texture"), 0);
	shaderProg_->UniformFloat(shaderProg_->GetUniformLocation("scale"), scale_*(0.5 + (lifeTime_ - particle.GetEstimatedTime()) / 3));
	shaderProg_->UniformFloat(shaderProg_->GetUniformLocation("estimatedTime"),particle.GetEstimatedTime());
	shaderProg_->UniformFloat(shaderProg_->GetUniformLocation("lifeTime"), lifeTime_);

	//shaderProg_->UniformVector3D(shaderProg_->GetUniformLocation("eyePos"), camera->GetPos());
}

void ParticleSystem::SetTranslation(Pipeline* p, Camera* camera, glm::vec4& worldPos)
{
	p->WorldPos(worldPos.x, worldPos.y, worldPos.z);
	p->SetCamera(camera->GetPos(), camera->GetTarget(), camera->GetUp());
}

float ParticleSystem::dt()
{
	sf::Time currentTime = APPLICATION->getTime();
	
	float dt = currentTime.asSeconds() - prevTime_.asSeconds();

	prevTime_ = currentTime;

	return dt;
}
