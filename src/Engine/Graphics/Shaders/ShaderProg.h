#pragma once

#include "../../../Include.h"
#include "../../Math/math_3d.h"

class ShaderProg
{
public:
	ShaderProg(GLuint program);
	~ShaderProg();

	void Use();

	int GetUniformLocation(const char* Name);

	void UniformInt       (GLuint location, int I);
	void UniformFloat     (GLuint location, float F);
	void UniformMatrix4x4 (GLuint location, glm::mat4 M);
	void UniformVector3D  (GLuint location, glm::vec3 V);
	void UniformVector2D  (GLuint location, float x, float y);
	void UniformVector3D  (GLuint location, float x, float y, float z);
	void UniformVector4D  (GLuint location, float x, float y, float z, float w);

private:
	GLuint _shaderProgram;
};

