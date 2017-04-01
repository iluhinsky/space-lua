#pragma once


#include "../../Include.h"
#define _USE_MATH_DEFINES

#include <math.h>

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

glm::vec3 toGLM(btVector3& vector);
glm::vec4 toVec4(glm::vec3& vector);

glm::mat4 toGLM(btMatrix3x3& matrix);