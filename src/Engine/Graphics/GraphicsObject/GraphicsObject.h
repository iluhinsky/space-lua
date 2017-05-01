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

	void SetScale(float scale);

	void Draw(Camera* camera, glm::vec3 worldPos, glm::mat3 rotation);

private:
	void SetUniforms(Camera* camera, glm::vec3& worldPos, glm::mat3& rotation);
	void SetTranslation(Pipeline* p, Camera* camera, glm::vec3& worldPos);

	float t; // temp
	float       scale_;

	Model*      model_;
	GLuint      texture_;
	ShaderProg* shaderProg_;
};

