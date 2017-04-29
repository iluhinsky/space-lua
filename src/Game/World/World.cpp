#include "World.h"

bool _ContactProcessedCallback(btManifoldPoint& cp, void* body0, void* body1)
{
	CollisionObject* p1 = (CollisionObject*)((btRigidBody*)body0)->getUserPointer();
	CollisionObject* p2 = (CollisionObject*)((btRigidBody*)body1)->getUserPointer();

	assert(p1 && p2);

	if (p1->GetType() == CollidingShip && 
		p2->GetType() == CollidingShip)
		return false;

	if (p1->GetType() == CollidingBullet && 
		p2->GetType() == CollidingBullet)
	{
		((Bullet*)p1)->hit();
		((Bullet*)p2)->hit();

		std::cout << "Bullets damage themselves!" << std::endl;

		return false;
	}

	btVector3 pointA = cp.getPositionWorldOnA();
	btVector3 pointB = cp.getPositionWorldOnB();

	if (p1->GetType() == CollidingShip)
		((Ship*)p1)->hit((Bullet*)p2, pointA, pointB);
	else
		((Ship*)p2)->hit((Bullet*)p1, pointB, pointA);

	return false;
}

World::World()
{

}

World::~World()
{
	bullets_.clear();
}


void World::Init()
{
	worldLoader_ = new WorldLoader(&ships_);
	worldLoader_->Init();

	gContactProcessedCallback = _ContactProcessedCallback;
}


void World::Load(std::string worldName)
{
	worldLoader_->Load(worldName);

//	it is only for testing!
//	shipsID_.push_back(13);
//	shipsID_.push_back(110);
}

void World::ReduceTime(int dt)
{
	for (auto bullet : bullets_)
		bullet->ReduceTime(dt);

	for (auto ship : ships_)
		ship->ReduceTime(dt);
}

void World::Draw(Camera* camera)
{
	for (auto ship : ships_)
		ship->Draw(camera);

	for (auto bullet : bullets_)
		bullet->Draw(camera);
}

void World::CreateBullet(glm::vec3 direction, glm::vec3 startingPosition)
{
	auto newBullet = std::make_shared<Bullet>(direction, startingPosition);

	bullets_.push_back(newBullet);
}

void World::ClearUnexisingBullets()
{
	bullets_.remove_if([](std::shared_ptr<Bullet> bullet) 
		{ return !(bullet->isExist()); });
}

void World::RunLUA()
{
	for (auto ship : ships_)
		ship->RunLUA();
}

void World::ExecuteLogic()
{
	for (auto ship : ships_)
		ship->ExecuteLogic();
}

const std::vector<int>& World::GetShipsID()
{
	return shipsID_;
}
