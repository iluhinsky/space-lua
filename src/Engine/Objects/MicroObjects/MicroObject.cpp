#include "MicroObject.h"



MicroObject::MicroObject()
{
}


MicroObject::~MicroObject()
{
}

void MicroObject::SetTranslation(Pipeline* p, Camera* camera)
{
	p -> WorldPos(_worldPos.x, _worldPos.y, _worldPos.z);
	p -> SetCamera (camera->GetPos(), camera->GetTarget(), camera->GetUp());
}