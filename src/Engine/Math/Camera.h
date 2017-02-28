#pragma once

#include "math_3d.h"

class Camera
{
friend class Player;

public:

	Camera();

	const glm::vec3& GetPos()    const { return m_pos;    }
	const glm::vec3& GetTarget() const { return m_target; }
	const glm::vec3& GetUp()     const { return m_up;     }

private:
	glm::vec3 m_pos;
	glm::vec3 m_target;
	glm::vec3 m_up;
};