#include "AbstractObject.h"

#include "../../Application/Application.h"


AbstractObject::AbstractObject()
{
	_target = glm::vec3(1.0f, 0.0f, 0.0f);
	_up     = glm::vec3(0.0f, 0.0f, 1.0f);

	_eulerAngles._phi = 0;
	_eulerAngles._theta = 0;
	_eulerAngles._csi = 0;
}


AbstractObject::~AbstractObject()
{
}

void AbstractObject::Draw(Camera* camera)
{
	_shaderProg->Use();

	UpdateAngles();
	SetUniforms (camera);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (int i = 0; i < _model->_amountMesh; i++)
	{
		Mesh currMesh = _model->_meshes[i];

		glBindTexture(GL_TEXTURE_2D,  _texture);
		glBindBuffer(GL_ARRAY_BUFFER, currMesh._VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, currMesh._offset._stride, (void*)currMesh._offset._vertex);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, currMesh._offset._stride, (void*)currMesh._offset._uvtex );
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, currMesh._offset._stride, (void*)currMesh._offset._normal);

		glDrawArrays(GL_TRIANGLES, 0, _model->_meshes[i]._nVerticles);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void AbstractObject::UpdateAngles()
{
	_eulerAngles = ToEulerAngles (_target, _up);
}

void AbstractObject::SetUniforms(Camera* camera)
{
	sf::Vector2u size = APPLICATION->GetWindowSize();

	Pipeline p;

	SetTranslation (&p, camera);
	
	p.Rotate(_eulerAngles._phi, _eulerAngles._theta, _eulerAngles._csi);
	p.SetPerspectiveProj(60.0f, size.x, size.y, 1.0f, 10000.0f);

	t += 0.01f;

	p.CalculateMatrices();

	glm::mat4 ModelViewMatrix = p.GetViewMatrix() * p.GetModelMatrix();
	glm::mat4 MVPMatrix       = p.GetProjMatrix() * ModelViewMatrix;

	_shaderProg->UniformMatrix4x4(_shaderProg->GetUniformLocation("gWVP"), MVPMatrix      );
	_shaderProg->UniformMatrix4x4(_shaderProg->GetUniformLocation("gWV" ), ModelViewMatrix);

	_shaderProg->UniformInt      (_shaderProg->GetUniformLocation("texture"), 0);
	_shaderProg->UniformFloat    (_shaderProg->GetUniformLocation("scale"), _scale);
	_shaderProg->UniformVector3D (_shaderProg->GetUniformLocation("lightPos"), 1000.0 * cos(t), 10000.0 * sin(t), 0.0f);
	_shaderProg->UniformVector3D (_shaderProg->GetUniformLocation("eyePos"), camera->GetPos());
}

void AbstractObject::SetWorldPos   (glm::vec3   worldPos  )
{
	_worldPos = worldPos;
}

void AbstractObject::SetModel      (Model*      model     )
{
	_model = model;
}

void AbstractObject::SetTexture    (GLuint      texture   )
{
	_texture = texture;
}

void AbstractObject::SetShaderProg (ShaderProg* shaderProg)
{
	_shaderProg = shaderProg;
}

void AbstractObject::SetScale      (float       scale     )
{
	_scale = scale;
}