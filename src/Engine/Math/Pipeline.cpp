#include "Pipeline.h"


void Pipeline::CalculateMatrices()
{
	glm::mat4 ScaleTrans, TranslationTrans;

	ScaleTrans       = glm::scale     (glm::mat4(1.0f), m_scale);

	TranslationTrans = glm::translate (glm::mat4(1.0f), m_worldPos);

	_ModelMatrix     = TranslationTrans * _RotateMatrix * ScaleTrans;

	_ViewMatrix      = glm::lookAt    (m_camera.Pos, m_camera.Pos + m_camera.Target, m_camera.Up);

	_ProjMatrix      = glm::perspective(glm::radians(m_persProj.FOV), 
		m_persProj.Width / m_persProj.Height, m_persProj.zNear, m_persProj.zFar);

}

const glm::mat4& Pipeline::GetModelMatrix()
{
	return _ModelMatrix;
}

const glm::mat4& Pipeline::GetViewMatrix()
{
	return _ViewMatrix;
}

const glm::mat4& Pipeline::GetProjMatrix()
{
	return _ProjMatrix;
}

void Pipeline::Rotate(glm::mat3& RotateMatrix)
{
	_RotateMatrix = glm::mat4(RotateMatrix);
}