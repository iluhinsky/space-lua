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
	for (auto ship : ships_)
		ship->Draw(camera);
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