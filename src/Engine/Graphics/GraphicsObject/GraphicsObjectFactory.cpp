#include "GraphicsObjectFactory.h"



bool operator< (const GraphicsObjectInfo& left, const GraphicsObjectInfo& right) {
	if (left.modelName_   < right.modelName_) return true;
	if (left.modelName_   > right.modelName_) return false;

	if (left.textureName_ < right.textureName_) return true;
	if (left.textureName_ > right.textureName_) return false;

	if (left.shaderNames_ < right.shaderNames_) return true;
	return false;
}


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