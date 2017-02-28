#include "ObjectFactory.h"

#include "../../Application/Application.h"

#include "MicroObjects/Ship.h"

#include "MacroObjects/Planet.h"



ObjectFactory::ObjectFactory()
{
}


ObjectFactory::~ObjectFactory()
{
}


AbstractObject* ObjectFactory::CreateObject (ObjectParameters parameters)
{
	AbstractObject* newObject = nullptr;

	switch (parameters._objectType)
	{
	case SHIP  : newObject = new Ship  ; break;
	case PLANET: newObject = new Planet; break;

	default  : newObject = nullptr;
	}

	ObjectInfo* objectInfo = APPLICATION->_manager->objectManager. Get(parameters._mainParametersPath);

	Model*           model = APPLICATION->_manager->modelManager.  Get (objectInfo->_modelPath);
	GLuint         texture = APPLICATION->_manager->textureManager.Get (objectInfo->_texturePath);
	ShaderProg* shaderProg = APPLICATION->_manager->shaderManager. Get (objectInfo->_shaderPaths);

	newObject->SetModel      (model     );
	newObject->SetTexture    (texture   );
	newObject->SetShaderProg (shaderProg);

	newObject->SetWorldPos   (parameters._worldPos);
	newObject->SetScale      (parameters._scale);

	return newObject;
}