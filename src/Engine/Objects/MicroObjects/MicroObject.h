#pragma once

#include "../AbstractObject.h"

class MicroObject :
	public AbstractObject
{
public:
	MicroObject();
	~MicroObject();

private:
		virtual void SetTranslation(Pipeline* p, Camera* camera);
};

