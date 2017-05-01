#include "Bullet.h"

#include "..\..\..\Application\Application.h"

const float     BULLET_MASS           = 0.1f;
const btVector3 BULLET_INERTIA        = btVector3(1.0f, 1.0f, 1.0f);
const int       BULLET_TIME           = 10000;
const int       BULLET_VELOCITY       = 10;
const float     BULLET_GRAPHICS_SCALE = 0.005f;


Bullet::Bullet(glm::vec3 direction, glm::vec3 startingPosition)
{
	btMatrix3x3 rotation;
	rotation.setIdentity();

	btVector3 vel = toBT(direction);
	btVector3 pos = toBT(startingPosition);

	transform_ = btTransform(rotation, pos);

	GraphicsObjectInfo bulletInfo;

	bulletInfo.modelName_   = "ball.3ds";
	bulletInfo.textureName_ = "Nekit.png";
	bulletInfo.shaderNames_._vertexShaderName   = "block_vertex.glsl";
	bulletInfo.shaderNames_._fragmentShaderName = "block_fragment.glsl";

	graphicsAsset_ = APPLICATION->GetGraphicsWorld()->GetManager()->Get(bulletInfo);
	graphicsAsset_->SetScale(BULLET_GRAPHICS_SCALE);

	isExist_       = true;
	collisionType_ = CollidingBullet;

	InitRigidBody();

	body_->setLinearVelocity(vel * BULLET_VELOCITY);

	remainingTime_ = BULLET_TIME;
}

Bullet::~Bullet()
{
	PHYSICSWORLD->RemoveRigidBody(body_);

	delete motionState_;
	delete body_;

	std::cout << "Bullet destroyed!" << std::endl; //TODO: remove!
}

void Bullet::InitRigidBody()
{
	btScalar  mass    = BULLET_MASS;
	btVector3 inertia = BULLET_INERTIA;

	shape_ = PHYSICSWORLD->sphereShape_;

	motionState_ = new btDefaultMotionState(transform_);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState_, shape_, inertia);
	body_ = new btRigidBody(rbInfo);

	body_->setUserPointer(this);

	PHYSICSWORLD->AddRigidBody(body_);
}

bool Bullet::isExist()
{
	return (isExist_ &&
		remainingTime_ > 0.0f);
}

void Bullet::ReduceTime(int dt)
{
	remainingTime_ -= dt;
}

void Bullet::hit()
{
	isExist_ = false;
}

void Bullet::Draw(Camera* camera)
{
	transform_ = body_->getWorldTransform();

	glm::vec3 globalCoord = toGLM(transform_.getOrigin());
	glm::mat3 rotation    = glm::mat3(1.0f);

	graphicsAsset_->Draw(camera, globalCoord, rotation);
}