#pragma once


#include "../../Include.h"
#define _USE_MATH_DEFINES

#include <math.h>

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

enum Direction
{
	x_up,
	x_down,
	y_up,
	y_down,
	z_up,
	z_down
};

template < typename T >
T max(T a, T b)
{
	return a > b ? a : b;
}

Direction oppositeTo(Direction);

bool isEqual(glm::vec3 vec1, glm::vec3 vec2);

btVector3 toBT(glm::vec3 vector);

glm::vec3 toGLM(btVector3& vector);
glm::vec4 toVec4(glm::vec3& vector);

glm::mat4 toGLM(btMatrix3x3& matrix);
glm::mat3 toGLM_M3x3(btMatrix3x3& matrix);