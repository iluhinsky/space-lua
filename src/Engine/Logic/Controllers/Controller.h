#pragma once

#include "../../Objects/AbstractObject.h"

class Controller
{
public:
	Controller();
	~Controller();

	virtual void BindObject (AbstractObject* object);

	virtual void OnKeyboard  (int key)                = 0;
	virtual void OnMouse     (int x, int y)           = 0;
	virtual void OnMouseMove (int DeltaX, int DeltaY) = 0;

protected:
	virtual void BindCamera(AbstractObject* object);

	AbstractObject* _object;
};

