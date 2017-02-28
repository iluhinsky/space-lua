#pragma once

#include "../Math/math_3d.h"
#include "AbstractObject.h"

enum ObjectType
{
	ERROR_TYPE = 0,

	SHIP       = 1,
	PLANET     = 2 
};


struct ObjectParameters
{
	ObjectType   _objectType;
	glm::vec3    _worldPos;
	float        _scale;

	std::string  _mainParametersPath;
};


class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	AbstractObject* CreateObject (ObjectParameters parameters);
};

