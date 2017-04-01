#pragma once

#include "math_3d.h"

class Pipeline
{
public:
	Pipeline() :
		_RotateMatrix(glm::mat4(1.0f))
	{
		m_scale       = glm::vec3 (1.0f, 1.0f, 1.0f);
		m_worldPos    = glm::vec3 (0.0f, 0.0f, 0.0f);
		m_rotateInfo  = glm::vec3 (0.0f, 0.0f, 0.0f);
	}

	void Scale(float ScaleX, float ScaleY, float ScaleZ)
	{
		m_scale.x = ScaleX;
		m_scale.y = ScaleY;
		m_scale.z = ScaleZ;
	}

	void WorldPos(float x, float y, float z)
	{
		m_worldPos.x = x;
		m_worldPos.y = y;
		m_worldPos.z = z;
	}

	void Rotate(glm::mat4& RotateMatrix)
	{
		_RotateMatrix = RotateMatrix;
	}

	void SetPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar)
	{
		m_persProj.FOV    = FOV;
		m_persProj.Width  = Width;
		m_persProj.Height = Height;
		m_persProj.zNear  = zNear;
		m_persProj.zFar   = zFar;
	}

	void SetCamera(const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up)
	{
		m_camera.Pos    = Pos;
		m_camera.Target = Target;
		m_camera.Up     = Up;
	}

	void CalculateMatrices();

	const glm::mat4& GetModelMatrix ();
	const glm::mat4& GetViewMatrix  ();
	const glm::mat4& GetProjMatrix  ();

private:
	glm::vec3 m_scale;
	glm::vec3 m_worldPos;
	glm::vec3 m_rotateInfo;

	struct {
		float FOV;
		float Width;
		float Height;
		float zNear;
		float zFar;
	} m_persProj;

	struct {
		glm::vec3 Pos;
		glm::vec3 Target;
		glm::vec3 Up;
	} m_camera;


	glm::mat4 _RotateMatrix;

	glm::mat4 _ModelMatrix, _ViewMatrix, _ProjMatrix;
};