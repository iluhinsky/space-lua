#include "Ship.h"
#include "Blocks/BlockShield.h"
#include "Blocks\BlockWeapon.h"

#include "..\..\Application\Application.h"

Ship::Ship() : controller_(this)
{
	
}


Ship::~Ship()
{
	PHYSICSWORLD->RemoveRigidBody(body_);

	delete motionState_;
	delete shape_;
	delete body_;
}


void Ship::Draw(Camera* camera)
{
	transform_ = body_->getWorldTransform() * principalTransformInverse_;

	glm::vec4 globalCoord = glm::vec4 (toGLM(transform_.getOrigin()), 1.0f);
	glm::mat4 rotation    = toGLM(transform_.getBasis());

	glm::mat4 rotation_inv = glm::inverse(rotation);

	for (auto block : blocks_)
		block->Draw(camera, globalCoord, rotation_inv);
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

	body_->setCollisionShape(shape_);
	body_->setMassProps(mass, inertia);
	body_->updateInertiaTensor();

	PHYSICSWORLD->AddRigidBody(body_);
}

void Ship::ReduceTime(int dt)
{
	for (auto block : blocks_)
		if (block->GetType() == BlockTypeWeapon)
			((BlockWeapon*)block)->ReduceTime(dt);
}

Block*  Ship::GetBlock(glm::vec3 relatedCoords)
{
	auto it = std::find_if(blocks_.begin(), blocks_.end(), [relatedCoords](Block* block)
	{ 
		return isEqual(relatedCoords, block->GetRelatedCoords()); 
	});

	if (it == blocks_.end())
		return nullptr;

	return *it;
}

void Ship::MakeHomiesLinked(int currentBlockNumber)
{
	if (currentBlockNumber == -1)
		return;

	if (blocks_[currentBlockNumber]->isLinked() == true)
		return;

	blocks_[currentBlockNumber]->Link();
	glm::vec3 curBlockCoords = blocks_[currentBlockNumber]->GetRelatedCoords();

	MakeHomiesLinked(GetBlockNumber(curBlockCoords + glm::vec3( 1.0f,  0.0f,  0.0f)));
	MakeHomiesLinked(GetBlockNumber(curBlockCoords + glm::vec3(-1.0f,  0.0f,  0.0f)));
	MakeHomiesLinked(GetBlockNumber(curBlockCoords + glm::vec3( 0.0f,  1.0f,  0.0f)));
	MakeHomiesLinked(GetBlockNumber(curBlockCoords + glm::vec3( 0.0f, -1.0f,  0.0f)));
	MakeHomiesLinked(GetBlockNumber(curBlockCoords + glm::vec3( 0.0f,  0.0f,  1.0f)));
	MakeHomiesLinked(GetBlockNumber(curBlockCoords + glm::vec3( 0.0f,  0.0f, -1.0f)));
}

void Ship::RemoveUnlinkedBlocks()
{	
	for (auto block : blocks_)
		block->Unlink();
	
	MakeHomiesLinked(GetBlockNumber(glm::vec3(0.0f, 0.0f, 0.0f)));

	for (auto block : blocks_)
	{
		if (block->isLinked() == false)
		{
			//Deleting this block
		}
	}
}

void Ship::RunLUA()
{
	for (auto block : blocks_)
		block->SetStandartCommand();

	controller_.Run();
}

void Ship::ExecuteLogic()
{
	for (auto block : blocks_)
		block->ExecuteCommand();
}

void Ship::hit(Bullet* bullet, btVector3& pointA, btVector3& pointB)
{
	std::cout << "Ship was hitten!" << std::endl;

	bullet->hit();

	Block* damagedBlock = GetNearestBlockTo(pointA, pointB);

	if (damagedBlock->GetType() == BlockTypeShield)
		std::cout << "Block " << ((BlockShield*)damagedBlock)->GetName() << " was beated!" << std::endl;

	damagedBlock->hit(10);

	/*
	if (damagedBlock->isExist())
		return;
	
	blocks_.remove(damagedBlock);
	*/

	RemoveUnlinkedBlocks();
}

btTransform Ship::GetTransform()
{
	return transform_;
}

void Ship::ConstructShape(btScalar& mass, btVector3& inertia)
{
	mass = 0.0f;
	std::vector<btScalar> blockMasses;

	btCompoundShape* tempShape = new btCompoundShape();

	for (auto block : blocks_)
	{
		float blockMass = block->GetMass();
		blockMasses.push_back(blockMass);
		mass += blockMass;

		glm::vec3 glm_relatedCoords = block->GetRelatedCoords();
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

	for (auto block : blocks_)
		if (block->GetRelatedCoords() == blockPosition)
			currBlock = block;

	return currBlock;;
}