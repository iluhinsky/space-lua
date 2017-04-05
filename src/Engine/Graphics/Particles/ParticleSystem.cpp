#include "ParticleSystem.h"
#include "../../../../src/Application/Application.h"



ParticleSystem::ParticleSystem(int numberOfParticles, float lifeTime = 1.0, float initialSpeed = 1.0)
{
	scale_				= 6.0;
	numberOfParticles_	= numberOfParticles;
	lifeTime_			= lifeTime;
	initialSpeed_		= initialSpeed;

	particles_ = new Particle[numberOfParticles_];
}


ParticleSystem::~ParticleSystem()
{
	delete[] particles_;
}

void ParticleSystem::Draw(Camera* camera)
{
	shaderProg_->Use();

	SetUniforms(camera, glm::vec4{ 1, 1, -3, 1 });

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (int i = 0; i < model_->_amountMesh; i++)
	{
		Mesh currMesh = model_->_meshes[i];
		
		glBindTexture(GL_TEXTURE_2D, texture_);
		glBindBuffer(GL_ARRAY_BUFFER, currMesh._VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, currMesh._offset._stride, (void*)currMesh._offset._vertex);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, currMesh._offset._stride, (void*)currMesh._offset._uvtex);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, currMesh._offset._stride, (void*)currMesh._offset._normal);

		glDrawArrays(GL_TRIANGLES, 0, model_->_meshes[i]._nVerticles);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void ParticleSystem::SetUniforms(Camera* camera, glm::vec4& worldPos)
{
	sf::Vector2u size = APPLICATION->GetWindowSize();

	Pipeline p;

	SetTranslation(&p, camera, worldPos);

	p.SetPerspectiveProj(60.0f, size.x, size.y, 1.0f, 10000.0f);

	p.Rotate(glm::mat4{ 0, 0, 1, 0,
						0, 1, 0, 0,
					   -1, 0, 0, 0,
						0, 0, 0, 1 }
	);


	glm::mat4 rotation = glm::mat4{ 1, 0, 0, 0,
						0, 0, -1, 0,
					    0, 1, 0, 0,
						0, 0, 0, 1 };
	

	p.CalculateMatrices();


	glm::mat4 ModelViewMatrix = p.GetViewMatrix() * p.GetModelMatrix();


	glm::mat4 MVPMatrix = p.GetProjMatrix() *  ModelViewMatrix;
	
	shaderProg_->UniformMatrix4x4(shaderProg_->GetUniformLocation("gWVP"), MVPMatrix);
	shaderProg_->UniformMatrix4x4(shaderProg_->GetUniformLocation("gWV"), ModelViewMatrix);

	shaderProg_->UniformInt(shaderProg_->GetUniformLocation("texture"), 0);
	shaderProg_->UniformFloat(shaderProg_->GetUniformLocation("scale"), scale_);
	//shaderProg_->UniformVector3D(shaderProg_->GetUniformLocation("eyePos"), camera->GetPos());
}

void ParticleSystem::SetTranslation(Pipeline* p, Camera* camera, glm::vec4& worldPos)
{
	p->WorldPos(worldPos.x, worldPos.y, worldPos.z);
	p->SetCamera(camera->GetPos(), camera->GetTarget(), camera->GetUp());
}
