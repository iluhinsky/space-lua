#pragma once

#include "../../Math/Camera.h"
#include "../../Math/Pipeline.h"
#include "../Management/ModelManager.h"
#include "../Management/ShaderProgManager.h"
#include "../Management/TextureManager.h"

class GraphicsObject
{
public:
	friend class GraphicsObjectFactory;

	GraphicsObject();
	~GraphicsObject();

	void SetScale(float scale);

	void Draw(Camera* camera, glm::vec3 worldPos, glm::mat3 rotation,
		glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f));

private:
	void SetUniforms(Camera* camera, glm::vec3 worldPos, glm::mat3& rotation, glm::vec3 color);
	void SetTranslation(Pipeline* p, Camera* camera, glm::vec3 worldPos);

	float       scale_;
	bool		isInfinite_;

	Model*      model_;
	GLuint      texture_;
	ShaderProg* shaderProg_;
};

