#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}


void GameObject::Draw(Camera* camera)
{
	graphicsAsset_->Draw(camera, coordinates_);
}