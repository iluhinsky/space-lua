#pragma once


#include "../../Include.h"
#define _USE_MATH_DEFINES

#include <math.h>

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

struct EulerAngles
{
	float _phi;
	float _theta;
	float _csi;
};

EulerAngles ToEulerAngles(glm::vec3 target, glm::vec3 up);