#include "World.h"

const int borderSize = 25;

const std::vector<Direction> directions =
{
	x_up,
	y_up,
	z_up,
	x_down,
	y_down,
	z_down
};


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
	worldLoader_ = new WorldLoader(&shipsDataBase_);
	worldLoader_->Init();

	gContactProcessedCallback = _ContactProcessedCallback;
}


void World::Load(std::string worldName)
{
	worldLoader_->Load(worldName);

	UpdateShipsIDVector();
}

void World::UpdateShipsIDVector()
{
	shipsID_.clear();

	for (auto elem : shipsDataBase_)
		shipsID_.push_back(elem.first);
}

void World::UpdateAfterPhysicsStep()
{
	for (auto ship : shipsDataBase_)
		ship.second->UpdateAfterPhysicsStep();
}

void World::BorderCheck()
{
	//! Bad code!!!
	for (auto ship : shipsDataBase_)
	{
		btVector3 coords = ship.second->getCoords();

		if (coords.x() > borderSize)
			ship.second->ApplyForce(btVector3(-1.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f));

		if (coords.x() < -borderSize)
			ship.second->ApplyForce(btVector3( 1.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f));

		if (coords.y() > borderSize)
			ship.second->ApplyForce(btVector3(0.0f, -1.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f));

		if (coords.y() < -borderSize)
			ship.second->ApplyForce(btVector3(0.0f, 1.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f));

		if (coords.z() > borderSize)
			ship.second->ApplyForce(btVector3(0.0f, 0.0f, -1.0f), btVector3(0.0f, 0.0f, 0.0f));

		if (coords.z() < -borderSize)
			ship.second->ApplyForce(btVector3(0.0f, 0.0f, 1.0f), btVector3(0.0f, 0.0f, 0.0f));
	}
}

void World::ReduceTime(int dt)
{
	for (auto bullet : bullets_)
		bullet->ReduceTime(dt);

	for (auto ship : shipsDataBase_)
		ship.second->ReduceTime(dt);
}

void World::Draw(Camera* camera)
{
	for (auto ship : shipsDataBase_)
		ship.second->Draw(camera);

	for (auto bullet : bullets_)
		bullet->Draw(camera);
}

void World::CreateBullet(glm::vec3 direction, glm::vec3 startingPosition)
{
	auto newBullet = std::make_shared<Bullet>(direction, startingPosition);

	bullets_.push_back(newBullet);
}

void World::ClearUnexisingObjects()
{
	bullets_.remove_if([](std::shared_ptr<Bullet> bullet) 
		{ return !(bullet->isExist()); });

	std::list<int> deadShipsIDs;

	for (auto ship : shipsDataBase_)
		if (!ship.second->isExist())
		{
			deadShipsIDs.push_back(ship.first);
			delete ship.second;
		}

	for (auto shipID : deadShipsIDs)
		shipsDataBase_.erase(shipID);

	UpdateShipsIDVector();

	for (auto ship : shipsDataBase_)
		ship.second->CleanUpBlocks();
}

void World::RunLUA()
{
	for (auto ship : shipsDataBase_)
		ship.second->RunLUA();
}

void World::ExecuteLogic()
{
	for (auto ship : shipsDataBase_)
		ship.second->ExecuteLogic();
}

Ship* World::GetShipByID(int shipID)
{
	assert(shipID >= 0);

	auto it = shipsDataBase_.find(shipID);

	if (it == shipsDataBase_.end())
		return nullptr;

	return it->second;
}

int World::GetIDByShip(Ship* ship)
{
	assert(ship);

	for (std::map<int, Ship*>::iterator it = shipsDataBase_.begin(); it != shipsDataBase_.end(); ++it)
	{
		if (ship == it->second)
		{
			return it->first;
		}
	}

	return -1;
}

const std::vector<int>& World::GetShipsID()
{
	return shipsID_;
}
