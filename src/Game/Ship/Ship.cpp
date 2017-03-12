#include "Ship.h"


Ship::Ship()
{

}


Ship::~Ship()
{

}


void Ship::Draw(Camera* camera)
{
	for (auto it = blocks_.begin(); it != blocks_.end(); ++it)
		(*it)->Draw(camera);
}