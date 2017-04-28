#pragma once

#include "..\..\Include.h"

#include "..\..\Engine\Physics\CollisionObject.h"
#include "..\World\Effects\Bullet.h"

#include "Blocks\Block.h"
#include "ShipController.h"


class Ship :
	public CollisionObject
{
	friend class ShipFactory;
	friend class ShipController;

	friend class Application; //! remove
public:
	Ship();
	~Ship();

	void Draw(Camera* camera);

	virtual void InitRigidBody();
	void UpdateRigidBody();

	void ReduceTime(int dt);

	void RunLUA();
	void ExecuteLogic();

	btTransform GetTransform();

	void hit(Bullet* bullet, btVector3& pointA, btVector3& pointB);

	btVector3 toWorldPosition(const btVector3& localPosition);
	Block*    getBlockByWorldPosition(const btVector3& position);

private:
	void ConstructShape(btScalar& mass, btVector3& inertia);

	Block* GetNearestBlockTo(const btVector3&  pointA, const btVector3& pointB);

	std::string shipName_;

	btTransform transform_;
	btTransform	principalTransform_;
	btTransform	principalTransformInverse_;

	std::vector<Block*> blocks_;

	ShipController controller_;
};