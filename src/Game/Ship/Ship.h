#pragma once

#include "../../Include.h"

#include "../../Engine/Physics/CollisionObject.h"
#include "../World/Effects/Bullet.h"

#include "Blocks\Block.h"
#include "ShipController.h"
#include <queue>


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
	void UpdateBlocksIDVector(); //! Call after every death of any block

	void RunLUA();
	void ExecuteLogic();

	void UpdateAfterPhysicsStep();

	btTransform GetTransform();

	void hit(Bullet* bullet, btVector3& pointA, btVector3& pointB);

	btVector3 toWorldPosition(const btVector3& localPosition);
	Block*    getBlockByWorldPosition(const btVector3& position);

private:
	void ConstructShape(btScalar& mass, btVector3& inertia);
	void RemoveUnlinkedBlocks();

	Block* GetNearestBlockTo(const btVector3&  pointA, const btVector3& pointB);

	std::string shipName_;

	btTransform transform_;
	btTransform	principalTransform_;
	btTransform	principalTransformInverse_;

	glm::vec3   globalCoords_;
	glm::mat3   currRotation_;
	glm::mat3   currRotationInverse_;

	std::map   <int, Block*> blocksDataBase_;
	std::vector<int>         blocksID_;
	std::list<Block*> blocks_;
	Block* blockMain;

	bool isExist_;

	ShipController controller_;
};
