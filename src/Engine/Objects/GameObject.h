#pragma once

#include "../Graphics/GraphicsObject/GraphicsObject.h"
#include "../Physics/CollisionObject.h"
#include "../Math/Camera.h"

class GameObject : 
	public CollisionObject
{
public:
	GameObject();
	~GameObject();

	virtual void Draw(Camera* camera, glm::vec3 coords) const = 0;

protected:
	GraphicsObject*  graphicsAsset_;
};

