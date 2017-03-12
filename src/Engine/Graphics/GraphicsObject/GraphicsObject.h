#pragma once

#include "../../Math/Camera.h"
#include "../../Math/Pipeline.h"
#include "..\Management\ModelManager.h"
#include "..\Management\ShaderProgManager.h"
#include "..\Management\TextureManager.h"

class GraphicsObject
{
public:
	friend class GraphicsObjectFactory;

	GraphicsObject();
	~GraphicsObject();

	void Draw(Camera* camera, glm::vec3& worldPos);

private:
	void SetUniforms(Camera* camera, glm::vec3& worldPos);
	void SetTranslation(Pipeline* p, Camera* camera, glm::vec3& worldPos);

	float t; // temp
	float       scale_;

	Model*      model_;
	GLuint      texture_;
	ShaderProg* shaderProg_;
};
