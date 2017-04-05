#pragma once

#include "GraphicsObject.h"

struct GraphicsObjectInfo
{
	std::string modelName_;
	std::string textureName_;

	ShaderNames shaderNames_;
};

bool operator< (const GraphicsObjectInfo& left, const GraphicsObjectInfo& right);

class GraphicsObjectFactory
{
public:
	GraphicsObjectFactory();
	~GraphicsObjectFactory();

	GraphicsObject* CreateObject(GraphicsObjectInfo assetNames);

private:
	//ShaderProgManager shaderManager_;
	TextureManager	  textureManager_;
	ModelManager	  modelManager_;
};

