#pragma once

#include <btBulletDynamicsCommon.h>



class CollisionShapesManager
{
public:
	CollisionShapesManager();
	~CollisionShapesManager();

	btCollisionShape* Get(std::string ModelFileName);

private:
	btCollisionShape* LoadModel(std::string ModelFileName);


};

