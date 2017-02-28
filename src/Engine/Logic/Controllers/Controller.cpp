#include "Controller.h"


Controller::Controller()
{
}


Controller::~Controller()
{
}


void Controller::BindObject(AbstractObject* object)
{
	_object = object;

	BindCamera(object);
}

void Controller::BindCamera(AbstractObject* object)
{
}