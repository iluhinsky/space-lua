#include "GraphicsObject.h"

#include "../../../Application/Application.h"

GraphicsObject::GraphicsObject(): scale_(1)
{
}


GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::SetScale(float scale)
{
	scale_ = scale;
}


void GraphicsObject::Draw(Camera* camera, glm::vec3 worldPos, glm::mat3 rotation, glm::vec3 color)
{
	shaderProg_->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetUniforms(camera, worldPos, rotation, color);

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

	glDisable(GL_BLEND);

	shaderProg_->Detach();


}


void GraphicsObject::SetUniforms(Camera* camera, glm::vec3 worldPos, glm::mat3& rotation, glm::vec3 color)
{
	sf::Vector2u size = APPLICATION->GetWindowSize();



	Pipeline p;

	float time = APPLICATION->getTime().asSeconds();

	if (isInfinite_) {
		SetTranslation(&p, camera, camera->GetPos());
	}
	else {
		SetTranslation(&p, camera, worldPos);
	}

	p.SetPerspectiveProj(60.0f, size.x, size.y, 1.0f, 10000.0f);
	p.Rotate(rotation);

	p.CalculateMatrices();

	glm::mat4 ModelViewMatrix = p.GetViewMatrix() * p.GetModelMatrix();
	glm::mat4 MVPMatrix = p.GetProjMatrix() * ModelViewMatrix;

	shaderProg_->UniformMatrix4x4(shaderProg_->GetUniformLocation("gWVP"), MVPMatrix);
	shaderProg_->UniformMatrix4x4(shaderProg_->GetUniformLocation("gWV"), ModelViewMatrix);

	shaderProg_->UniformInt(shaderProg_->GetUniformLocation("texture"), 0);
	shaderProg_->UniformFloat(shaderProg_->GetUniformLocation("scale"), scale_);
	shaderProg_->UniformFloat(shaderProg_->GetUniformLocation("time"), APPLICATION->getTime().asMicroseconds());
	shaderProg_->UniformVector3D(shaderProg_->GetUniformLocation("lightPos"), 1000.0 * cos(time), 1000.0 * sin(time), 0.0f);
	shaderProg_->UniformVector3D(shaderProg_->GetUniformLocation("eyePos"), camera->GetPos());
	shaderProg_->UniformVector3D(shaderProg_->GetUniformLocation("color"),  color);
}

void GraphicsObject::SetTranslation(Pipeline* p, Camera* camera, glm::vec3 worldPos)
{
	p->WorldPos(worldPos.x, worldPos.y, worldPos.z);
	p->SetCamera(camera->GetPos(), camera->GetTarget(), camera->GetUp());
}
