#include "Camera.h"
#include "../../Application/Application.h"

Camera::Camera()
{
	m_pos           = glm::vec3(0.0f, 0.0f, 0.0f);
	
	m_target        = glm::vec3(1.0f, 0.0f, 0.0f);
	m_up            = glm::vec3(0.0f, 0.0f, 1.0f);
}