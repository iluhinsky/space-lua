#include "Pipeline.h"


void Pipeline::CalculateMatrices()
{
	glm::mat4 ScaleTrans, RotateTrans, TranslationTrans, 
		RotateTransPhi, RotateTransTheta, RotateTransCsi;

	ScaleTrans       = glm::scale     (glm::mat4(1.0f), m_scale);

	RotateTransPhi   = glm::rotate    (glm::mat4(1.0f), m_rotateInfo.x, glm::vec3(0.0f, 0.0f, 1.0f));
	RotateTransTheta = glm::rotate    (glm::mat4(1.0f), m_rotateInfo.y, glm::vec3(1.0f, 0.0f, 0.0f));
	RotateTransCsi   = glm::rotate    (glm::mat4(1.0f), m_rotateInfo.z, glm::vec3(0.0f, 0.0f, 1.0f));

	RotateTrans      = RotateTransCsi * RotateTransTheta * RotateTransPhi;

	TranslationTrans = glm::translate (glm::mat4(1.0f), m_worldPos);

	_ModelMatrix     = TranslationTrans * RotateTrans * ScaleTrans;

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