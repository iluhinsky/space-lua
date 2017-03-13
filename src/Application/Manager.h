#pragma once

#include "../Engine/Graphics/Management/ShaderProgManager.h"
#include "../Engine/Graphics/Management/TextureManager.h"
#include "../Engine/Graphics/Management/ModelManager.h"


class Manager
{
public:
	Manager();
	~Manager();

	ShaderProgManager shaderManager;
	TextureManager	  textureManager;
	ModelManager	  modelManager;
};

