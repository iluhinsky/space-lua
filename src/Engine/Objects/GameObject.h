#pragma once

#include "..\Graphics\GraphicsObject\GraphicsObject.h"
#include "..\Physics\CollisionObject.h"
#include "..\Math\Camera.h"

class GameObject : 
	public CollisionObject
{
public:
	GameObject();
	~GameObject();

	void Draw(Camera* camera);

private:
	GraphicsObject*  graphicsAsset_;

	glm::vec3 coordinates_;
};

