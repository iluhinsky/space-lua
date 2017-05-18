#include "Ship.h"
#include "Blocks/BlockShield.h"
#include "Blocks/BlockWeapon.h"
#include "Blocks/BlockEngine.h"

#include "../../Application/Application.h"


std::vector<Direction> directions =
{
	x_up,  
	y_up,  
	z_up, 
	x_down,
	y_down,
	z_down
};


Ship::Ship() : controller_(this)
{
	
}


Ship::~Ship()
{
	std::cout << "Ship " << shipName_ << " was punished!" << std::endl;

	for (auto block : blocksDataBase_)
		delete block.second;

	blocksDataBase_.clear();

	PHYSICSWORLD->RemoveRigidBody(body_);

	delete motionState_;
	delete shape_;
	delete body_;
}


void Ship::Draw(Camera* camera)
{
	for (auto block : blocksDataBase_)
		block.second->Draw(camera, color_);
}

void Ship::InitRigidBody()
{
	/*XXX: updateChildTransform is too slow, so we recreate the shape*/
	btScalar mass;
	btVector3 inertia;

	ConstructShape(mass, inertia);

	motionState_ = new btDefaultMotionState(transform_ * principalTransform_);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState_, shape_, inertia);
	body_ = new btRigidBody(rbInfo);

	body_->setUserPointer(this);

	PHYSICSWORLD->AddRigidBody(body_);
}

void Ship::UpdateRigidBody()
{
	PHYSICSWORLD->RemoveRigidBody(body_);
	delete shape_;

	btScalar mass;
	btVector3 inertia;

	ConstructShape(mass, inertia);

	body_->setWorldTransform(transform_ * principalTransform_);
	body_->setCollisionShape(shape_);
	body_->setMassProps(mass, inertia);
	body_->updateInertiaTensor();

	PHYSICSWORLD->AddRigidBody(body_);
}

void Ship::ReduceTime(int dt)
{
	for (auto block : blocksDataBase_)
	{
		if (block.second->GetType() == BlockTypeWeapon)
			((BlockWeapon*)block.second)->ReduceTime(dt);

		if (block.second->GetType() == BlockTypeEngine)
			((BlockEngine*)block.second)->ReduceTime(dt);
	}
}
		

void Ship::UpdateBlocksIDVector()
{
	blocksID_.clear();

	for (auto elem : blocksDataBase_)
		blocksID_.push_back(elem.first);
}

void Ship::FindUnlinkedBlocks()
{	
	for (auto block : blocksDataBase_)
		block.second->UnlinkfromMain();

	std::queue<Block*> BFSqueue;
	Block* currBlock     = nullptr;
	Block* neighborBlock = nullptr;

	if (blockMain != nullptr)
	{
		BFSqueue.push(blockMain);
		blockMain->LinktoMain();
	}

	while (!BFSqueue.empty())
	{
		currBlock = BFSqueue.front();
		BFSqueue.pop();

		for (auto direction : directions)
		{
			neighborBlock = currBlock->GetBlockBy(direction);

			if (neighborBlock != nullptr &&
				neighborBlock->isExist() &&
				!neighborBlock->isLinkedtoMain())
			{
				BFSqueue.push(neighborBlock);
				neighborBlock->LinktoMain();
			}
		}
	}
}

void Ship::RunLUA()
{
	for (auto block : blocksDataBase_)
		block.second->SetStandartCommand();
	
	//! Only for testing!!
	for (auto block : blocksDataBase_)
		if (block.second->GetType() == BlockTypeEngine)
		{
			((BlockEngine*)block.second)->SetPower(1);
			((BlockEngine*)block.second)->SetDirection(glm::vec3(0.0f, 0.0f, -1.0f));

			((BlockEngine*)block.second)->SetCommand(GasCommand);
		}

	controller_.Run();
}

void Ship::ExecuteLogic()
{
	for (auto block : blocksDataBase_)
		block.second->ExecuteCommand();
}

void Ship::UpdateAfterPhysicsStep()
{
	transform_ = body_->getWorldTransform() * principalTransformInverse_;

	globalCoords_        = toGLM(transform_.getOrigin());
	currRotation_        = toGLM_M3x3(transform_.getBasis());
	currRotationInverse_ = glm::inverse(currRotation_);

	for (auto block : blocksDataBase_)
		block.second->UpdateAfterPhysicsStep(globalCoords_, currRotationInverse_);
}

void Ship::hit(Bullet* bullet, btVector3& pointA, btVector3& pointB)
{
	std::cout << "Ship was hitten!" << std::endl;

	bullet->hit();

	Block* damagedBlock = GetNearestBlockTo(pointA, pointB);

	if (damagedBlock->GetType() == BlockTypeShield)
		std::cout << "Block " << ((BlockShield*)damagedBlock)->GetName() << " was beated!" << std::endl;

	damagedBlock->hit(10);

	if (damagedBlock->isExist())
		return;

	if (damagedBlock->GetType() == BlockTypeMain)
	{
		isExist_  = false;
		return;
	}
	
	FindUnlinkedBlocks();
}

bool Ship::isExist()
{
	return isExist_;
}

void Ship::CleanUpBlocks()
{
	std::list<int> deletingBlocks;

	for (auto block : blocksDataBase_)
		if (!block.second->isLinkedtoMain() ||
			!block.second->isExist())
			deletingBlocks.push_back(block.first);

	if (deletingBlocks.size() == 0)
		return;

	Block* currBlock = nullptr;

	for (auto blockID : deletingBlocks)
	{
		currBlock = blocksDataBase_[blockID];

		delete currBlock;
		blocksDataBase_.erase(blockID);
	}

	UpdateBlocksIDVector();
	UpdateRigidBody();
}

btTransform Ship::GetTransform()
{
	return transform_;
}

btVector3 Ship::getCoords()
{
	return transform_.getOrigin();
}

btVector3 Ship::getVelocity()
{
	return body_->getVelocityInLocalPoint(principalTransform_.getOrigin());
}

void Ship::ConstructShape(btScalar& mass, btVector3& inertia)
{
	mass = 0.0f;
	std::vector<btScalar> blockMasses;

	btCompoundShape* tempShape = new btCompoundShape();

	for (auto block : blocksDataBase_)
	{
		float blockMass = block.second->GetMass();
		blockMasses.push_back(blockMass);
		mass += blockMass;

		glm::vec3 glm_relatedCoords = block.second->GetRelatedCoords();
		btVector3 bt_relatedCoords  = btVector3(glm_relatedCoords.x, glm_relatedCoords.y, glm_relatedCoords.z);

		btTransform blockTransform(btQuaternion::getIdentity(), bt_relatedCoords);
		tempShape->addChildShape(blockTransform, PHYSICSWORLD->boxShape_);
	}

	tempShape->calculatePrincipalAxisTransform(blockMasses.data(), principalTransform_, inertia);
	principalTransformInverse_ = principalTransform_.inverse();

	shape_ = new btCompoundShape();

	for (int i = 0; i < tempShape->getNumChildShapes(); i++)
		((btCompoundShape*) shape_)->addChildShape(principalTransformInverse_ * tempShape->getChildTransform(i), 
			tempShape->getChildShape(i));

	delete tempShape;
}

Block* Ship::GetNearestBlockTo(const btVector3&  pointA, const btVector3& pointB)
{
	btScalar inf = 1.0e+2f;
	btScalar dist = +inf;
	btVector3 closestBlock;

	btCompoundShape* compoundShape = (btCompoundShape*)shape_;

	for (int i = 0; i < compoundShape->getNumChildShapes(); i++)
	{
		btCollisionShape* childShape = compoundShape->getChildShape(i);

		btVector3 localA = principalTransform_ * body_->getWorldTransform().inverse() * pointA;
		btVector3 localB = principalTransform_ * body_->getWorldTransform().inverse() * pointB;

		btVector3 block = principalTransform_ * compoundShape->getChildTransform(i).getOrigin();

		btVector3 dA = localA - block;
		btVector3 dB = localB - block;

		btScalar d = max(abs(dA.getX()), max(abs(dA.getY()), max(abs(dA.getZ()),
			max(abs(dB.getX()), max(abs(dB.getY()), abs(dB.getZ()))))));

		if (d < dist)
		{
			dist = d;
			closestBlock = block;
		}
	}

	if (dist < +inf)
		return getBlockByWorldPosition(toWorldPosition(closestBlock));

	return NULL;
}

void Ship::ApplyForce(btVector3& force, btVector3& relPos)
{
	body_->applyForce(force, relPos);
}

void Ship::ReduceVelocity(float factor)
{
	body_->setLinearVelocity(getVelocity() * factor);
}

btVector3 Ship::toWorldPosition(const btVector3& localPosition)
{
	return body_->getWorldTransform() * principalTransformInverse_ * localPosition;
}

Block* Ship::getBlockByWorldPosition(const btVector3& position)
{
	btVector3 localPosition = principalTransform_ * body_->getCenterOfMassTransform().inverse() * position;
	glm::vec3 blockPosition(
		int(round(localPosition.getX())),
		int(round(localPosition.getY())),
		int(round(localPosition.getZ())));

	Block* currBlock = nullptr;

	for (auto block : blocksDataBase_)
		if (block.second->GetRelatedCoords() == blockPosition)
			currBlock = block.second;

	return currBlock;;
}

int Ship::GetidOf(Block* block)
{
	auto it = std::find_if(blocksDataBase_.begin(), blocksDataBase_.end(),
		[block](std::pair<int, Block*> currBlock)
	{
		return currBlock.second == block;
	});

	if (it == blocksDataBase_.end())
		return -1;

	return it->first;
}