#pragma once

#include "../Math/Camera.h"
#include "../Math/Pipeline.h"

#include "../Graphics/Model/Model.h"
#include "../Graphics/Shaders/ShaderProg.h"

class AbstractObject
{
friend class Player;

public:
	AbstractObject();
	~AbstractObject();

	void Draw (Camera* camera);

	void SetWorldPos   (glm::vec3 worldPos);

	void SetModel      (Model*      model     );
	void SetTexture    (GLuint      texture   );
	void SetShaderProg (ShaderProg* shaderProg);
	void SetScale      (float       scale     );

protected:
	glm::vec3    _worldPos;

	glm::vec3    _target;
	glm::vec3    _up;

private:
	void UpdateAngles           ();
	void SetUniforms            (Camera* camera);
	virtual void SetTranslation (Pipeline* p, Camera* camera) = 0;

	float       _scale;

	float       t = 0; // temp

	EulerAngles _eulerAngles;

	Model*      _model;
	GLuint      _texture;
	ShaderProg* _shaderProg;
};

