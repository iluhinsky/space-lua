#include "ShaderProg.h"



ShaderProg::ShaderProg(GLuint program)
{
	_shaderProgram = program;
}


ShaderProg::~ShaderProg()
{
	glDeleteProgram(_shaderProgram);
}

void ShaderProg::Use()
{
	glUseProgram(_shaderProgram);
}

int  ShaderProg::GetUniformLocation(const char* name)
{
	int location = glGetUniformLocation(_shaderProgram, name);
	
	//assert(location != -1);
	return location;
}

void ShaderProg::UniformInt       (GLuint location, int I)
{
	glUniform1i(location, I);
}

void ShaderProg::UniformFloat     (GLuint location, float F)
{
	glUniform1f(location, F);
}

void ShaderProg::UniformMatrix4x4(GLuint location, glm::mat4 M)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat*)&M[0][0]);
}

void ShaderProg::UniformMatrix3x3(GLuint location, glm::mat3 M)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, (const GLfloat*)&M[0][0]);
}

void ShaderProg::UniformVector3D  (GLuint location, glm::vec3 V)
{
	UniformVector3D(location, V.x, V.y, V.z);
}

void ShaderProg::UniformVector2D  (GLuint location, float x, float y)
{
	glUniform2f(location, x, y);
}

void ShaderProg::UniformVector3D  (GLuint location, float x, float y, float z)
{
	glUniform3f(location, x, y, z);
}

void ShaderProg::UniformVector4D  (GLuint location, float x, float y, float z, float w)
{
	glUniform4f(location, x, y, z, w);
}

void ShaderProg::Detach()
{
	glDetachShader(_shaderProgram, _shaderProgram);
}
