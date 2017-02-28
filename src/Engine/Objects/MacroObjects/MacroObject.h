#pragma once

#include "..\AbstractObject.h"

class MacroObject :
	public AbstractObject
{
public:
	MacroObject();
	~MacroObject();

private:
	virtual void SetTranslation (Pipeline* p, Camera* camera);
};

