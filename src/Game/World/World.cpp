#include "World.h"

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
}


void World::Load(std::string worldName)
{
	worldLoader_->Load(worldName);
}

void World::ReduceTime(int dt)
{
	for (auto bullet : bullets_)
		bullet->ReduceTime(dt);
}

void World::Draw(Camera* camera)
{
	for (auto ship : ships_)
		ship->Draw(camera);

	for (auto bullet : bullets_)
		bullet->Draw(camera);
}

void World::CreateBullet(glm::vec3 velocity, glm::vec3 startingPosition)
{
	auto newBullet = std::make_shared<Bullet>(velocity, startingPosition);

	bullets_.push_back(newBullet);
}

void World::ClearUnexisingBullets()
{
	bullets_.remove_if([](std::shared_ptr<Bullet> bullet) 
		{ return !(bullet->isExist()); });
}