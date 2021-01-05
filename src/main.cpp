#include "Application/Application.h"

int main()
{
	Application* application = new Application;

	application->Init();
	application->MainLoop();

	delete application;

	return 0;
}
