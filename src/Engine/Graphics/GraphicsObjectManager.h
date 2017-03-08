#pragma once

#include "GraphicsObject\GraphicsObjectFactory.h"

class GraphicsObjectManager
{
public:
	GraphicsObjectManager();
	~GraphicsObjectManager();

	GraphicsObject* Get(GraphicsObjectInfo assetNames);

private:
	GraphicsObject* LoadGraphicsObject(GraphicsObjectInfo assetNames);

	std::unordered_map <GraphicsObjectInfo, GraphicsObject*> _graphicsObjectMap;
};

