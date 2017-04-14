#pragma once

#include "..\..\Include.h"

#include "..\..\Engine\Physics\CollisionObject.h"

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

private:
	void ConstructShape(btScalar& mass, btVector3& inertia);

	std::string shipName_;
	
	btTransform transform_;
	btTransform	principalTransform_;
	btTransform	principalTransformInverse_;

	std::vector<Block*> blocks_;

	ShipController controller_;
};