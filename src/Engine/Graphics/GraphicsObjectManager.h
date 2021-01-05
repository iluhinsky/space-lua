#pragma once

#include "GraphicsObject/GraphicsObjectFactory.h"

class GraphicsObjectManager
{
public:
	GraphicsObjectManager();
	~GraphicsObjectManager();

	GraphicsObject* Get(GraphicsObjectInfo assetNames);

private:
	GraphicsObject* LoadGraphicsObject(GraphicsObjectInfo assetNames);

	GraphicsObjectFactory factory;

	std::map <GraphicsObjectInfo, GraphicsObject*> _graphicsObjectMap;
};

