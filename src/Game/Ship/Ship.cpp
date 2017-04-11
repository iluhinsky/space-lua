#include "Ship.h"
#include "Blocks/BlockShield.h"

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