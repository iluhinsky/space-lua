#include "Bullet.h"

#include "..\..\..\Application\Application.h"

const float     BULLET_MASS    = 0.1f;
const btVector3 BULLET_INERTIA = btVector3(1.0f, 1.0f, 1.0f);
const int       BULLET_TIME    = 10000;


Bullet::Bullet(glm::vec3 velocity, glm::vec3 startingPosition)
{
	btMatrix3x3 rotation;
	rotation.setIdentity();

	btVector3 vel = toBT(velocity);
	btVector3 pos = toBT(startingPosition);

	transform_ = btTransform(rotation, pos);

	GraphicsObjectInfo bulletInfo;

	bulletInfo.modelName_   = "ball.3ds";
	bulletInfo.textureName_ = "Nekit.png";
	bulletInfo.shaderNames_._vertexShaderName   = "block_vertex.glsl";
	bulletInfo.shaderNames_._fragmentShaderName = "block_fragment.glsl";

	graphicsAsset_ = APPLICATION->GetGraphicsWorld()->GetManager()->Get(bulletInfo);
	graphicsAsset_->SetScale(0.005f);

	isExist_ = true;

	InitRigidBody();

	body_->setLinearVelocity(vel);

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

void Bullet::Draw(Camera* camera)
{
	transform_ = body_->getWorldTransform();

	glm::vec4 globalCoord = glm::vec4(toGLM(transform_.getOrigin()), 1.0f);
	glm::mat4 rotation = toGLM(transform_.getBasis());

	graphicsAsset_->Draw(camera, globalCoord, rotation);
}