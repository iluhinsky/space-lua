#include "GraphicsObject.h"

#include "../../../Application/Application.h"

GraphicsObject::GraphicsObject():
	t(0),
	scale_(1)
{
}


GraphicsObject::~GraphicsObject()
{
}


void GraphicsObject::Draw(Camera* camera, glm::vec4& worldPos, glm::mat4& rotation)
{
	shaderProg_->Use();

	SetUniforms(camera, worldPos, rotation);

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


void GraphicsObject::SetUniforms(Camera* camera, glm::vec4& worldPos, glm::mat4& rotation)
{
	sf::Vector2u size = APPLICATION->GetWindowSize();

	Pipeline p;

	SetTranslation(&p, camera, worldPos);

	p.SetPerspectiveProj(60.0f, size.x, size.y, 1.0f, 10000.0f);
	p.Rotate(rotation);

	t += 0.01f;

	p.CalculateMatrices();

	glm::mat4 ModelViewMatrix = p.GetViewMatrix() * p.GetModelMatrix();
	glm::mat4 MVPMatrix       = p.GetProjMatrix() * ModelViewMatrix;

	shaderProg_->UniformMatrix4x4(shaderProg_->GetUniformLocation(    "gWVP"), MVPMatrix);
	shaderProg_->UniformMatrix4x4(shaderProg_->GetUniformLocation(     "gWV"), ModelViewMatrix);

	shaderProg_->UniformInt      (shaderProg_->GetUniformLocation( "texture"),      0);
	shaderProg_->UniformFloat    (shaderProg_->GetUniformLocation(   "scale"), scale_);
	shaderProg_->UniformVector3D (shaderProg_->GetUniformLocation("lightPos"), 1000.0 * cos(t), 10000.0 * sin(t), 0.0f);
	shaderProg_->UniformVector3D (shaderProg_->GetUniformLocation(  "eyePos"), camera->GetPos());
}

void GraphicsObject::SetTranslation(Pipeline* p, Camera* camera, glm::vec4& worldPos)
{
	p->WorldPos(worldPos.x, worldPos.y, worldPos.z);
	p->SetCamera(camera->GetPos(), camera->GetTarget(), camera->GetUp());
}
