#include "CollisionObject.h"



CollisionObject::CollisionObject()
{
}

CollisionObject::~CollisionObject()
{
}

CollisionObjectType CollisionObject::GetType()
{
	return collisionType_;
}