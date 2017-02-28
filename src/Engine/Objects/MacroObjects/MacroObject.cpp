#include "MacroObject.h"



MacroObject::MacroObject()
{
}


MacroObject::~MacroObject()
{
}


void MacroObject::SetTranslation(Pipeline* p, Camera* camera)
{
	p->WorldPos(_worldPos.x, _worldPos.y, _worldPos.z);
	p->SetCamera(glm::vec3 (0.0f, 0.0f, 0.0f), camera->GetTarget(), camera->GetUp());
}