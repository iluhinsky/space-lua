#include "World.h"

World::World()
{

}

World::~World()
{

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


void World::Draw(Camera* camera)
{
	for (auto it = ships_.begin(); it != ships_.end(); ++it)
		(*it)->Draw(camera);
}