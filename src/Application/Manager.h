#pragma once

#include "../Engine/Graphics/Management/ShaderProgManager.h"
#include "../Engine/Graphics/Management/TextureManager.h"
#include "../Engine/Graphics/Management/ModelManager.h"
#include "../Engine/Objects/ObjectManager.h"


class Manager
{
public:
	Manager();
	~Manager();

	ShaderProgManager shaderManager;
	TextureManager	  textureManager;
	ModelManager	  modelManager;
	ObjectManager     objectManager;
};

