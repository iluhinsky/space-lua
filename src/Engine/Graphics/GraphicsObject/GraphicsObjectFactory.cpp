#include "GraphicsObjectFactory.h"


GraphicsObjectFactory::GraphicsObjectFactory()
{
}


GraphicsObjectFactory::~GraphicsObjectFactory()
{
}

GraphicsObject* GraphicsObjectFactory::CreateObject(GraphicsObjectInfo assetNames)
{
	GraphicsObject* newObject = new GraphicsObject;

	newObject->model_      = modelManager_  .Get(assetNames.modelName_  );
	newObject->texture_    = textureManager_.Get(assetNames.textureName_);
	newObject->shaderProg_ = shaderManager_ .Get(assetNames.shaderNames_);

	return newObject;
}