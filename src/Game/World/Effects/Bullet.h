#pragma once

#include "..\..\..\Engine\Graphics\GraphicsObject\GraphicsObject.h"
#include "..\..\..\Engine\Physics\CollisionObject.h"


class Bullet :
	public CollisionObject
{
public:
	Bullet(glm::vec3 direction, glm::vec3 startingPosition);
	~Bullet();

	virtual void InitRigidBody();

	bool isExist();
	void ReduceTime(int dt);

	void Draw(Camera* camera);

private:
	int isExist_;
	int remainingTime_; //! in milliseconds

	btTransform transform_;

	GraphicsObject* graphicsAsset_;
};

