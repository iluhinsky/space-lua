#include "Camera.h"
#include "../../Application/Application.h"

Camera::Camera()
{
	m_pos    = glm::vec3(0.0f, 0.0f, 0.0f);
	m_target = glm::vec3(1.0f, 0.0f, 0.0f);
	m_up     = glm::vec3(0.0f, 0.0f, 1.0f);

	Init();
}


Camera::Camera(const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up)
{
	m_pos = Pos;

	m_target = Target;
	m_target = glm::normalize(m_target);

	m_up = Up;
	m_up = glm::normalize(m_up);

	Init();
}


void Camera::Init()
{
	glm::vec3 HTarget(m_target.x, m_target.y, 0.0);
	HTarget = glm::normalize(HTarget);

	if (HTarget.y >= 0.0f)
	{
		if (HTarget.x >= 0.0f) m_AngleH = 360.0f - (float)ToDegree(asin(HTarget.y));
		else                   m_AngleH = 180.0f + (float)ToDegree(asin(HTarget.y));
	}
	else
	{
		if (HTarget.x >= 0.0f) m_AngleH =         (float)ToDegree(asin(-HTarget.y));
		else                   m_AngleH = 90.0f + (float)ToDegree(asin(-HTarget.y));
	}

	m_AngleV = -(float)ToDegree(asin(m_target.z));
}


void Camera::Update()
{
	const glm::vec3 Vaxis(0.0f, 0.0f, 1.0f);

	if      (m_AngleV >  90.0f) m_AngleV =  90.0f;
	else if (m_AngleV < -90.0f) m_AngleV = -90.0f;

	// Rotate the view vector by the horizontal angle around the vertical axis
	glm::vec3 View(1.0f, 0.0f, 0.0f);

	View = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)ToRadian(m_AngleH), Vaxis) * glm::vec4(View, 1.0f));
	View = glm::normalize(View);

	// Rotate the view vector by the vertical angle around the horizontal axis
	glm::vec3 Haxis = glm::cross(Vaxis, View);
	Haxis = glm::normalize(Haxis);
	View = glm::vec3(glm::rotate(glm::mat4(1.0f), (float)ToRadian(m_AngleV), Haxis) * glm::vec4(View, 1.0f));

	m_target = View;
	m_target = glm::normalize(m_target);

	m_up = glm::cross(m_target, Haxis);
	m_up = glm::normalize(m_up);
}