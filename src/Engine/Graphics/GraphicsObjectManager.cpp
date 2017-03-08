#include "GraphicsObjectManager.h"



GraphicsObjectManager::GraphicsObjectManager()
{
}


GraphicsObjectManager::~GraphicsObjectManager()
{
}


GraphicsObject* GraphicsObjectManager::Get(GraphicsObjectInfo assetNames)
{
	GraphicsObject* graphicsObject = _graphicsObjectMap[assetNames];

	if (!graphicsObject)
	{
		graphicsObject = LoadGraphicsObject(assetNames);

		_graphicsObjectMap[assetNames] = graphicsObject;
	}

	return graphicsObject;
}


GraphicsObject* GraphicsObjectManager::LoadGraphicsObject(GraphicsObjectInfo assetNames)
{

}