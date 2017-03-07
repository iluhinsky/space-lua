#include "Application.h"

#include "../Engine/World/World.h"

Application* Application::_instance = nullptr;


Application::Application()
{
}

Application::~Application() 
{
	delete _world;
	delete _player;
	delete _manager;
}

void Application::Init()
{
	_instance = this;

	if (!InitWindow(sf::Vector2u(800, 600), "Out of Space"))
	{
		fprintf(stderr, "Error: Can't open window\n");
		exit(-1);
	}

	ClipCursorInWindow();
	ShowCursor(false);

	_currentState = Game;

	_manager      = new Manager;
	_player       = new Player;
	_world        = new World;

	_world->Load("../bin/resources/worlds/Mustafar.txt");

	_world->BindController (_player);
}


void Application::DisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_player->UpdateCamera();

	_world->Draw(_player->GetCamera());

	_window->display();
}


void Application::ReshapeFunc(int width, int height)
{
	glViewport(0, 0, width, height);
}

void Application::CloseFunction()
{
	StopLoop();
}

void Application::KeyboardFunc()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) StopLoop();

	for (auto it = _keys.begin(); it != _keys.end(); ++it) 
		if (sf::Keyboard::isKeyPressed(*it)) _player->OnKeyboard(*it);
}

void Application::PassiveMotionFunc(int x, int y)
{
	if      (_currentState == Game) GameMouseFunc (x, y);
	else if (_currentState == Menu) MenuMouseFunc (x, y);
}

void Application::GameMouseFunc(int x, int y)
{
	const int DeltaX = x - _prevMousePos.x;
	const int DeltaY = y - _prevMousePos.y;

	_prevMousePos.x = x;
	_prevMousePos.y = y;

	sf::Vector2u windowSize = GetWindowSize();

	if (DeltaX > (int)windowSize.x / 4 || DeltaX < -(int)windowSize.x / 4 ||
		DeltaY >(int) windowSize.y / 4 || DeltaY < -(int)windowSize.y / 4)
		return;

	if (x < (int)windowSize.x / 4 || x >(int) windowSize.x * 3 / 4 ||
		y < (int)windowSize.y / 4 || y >(int) windowSize.y * 3 / 4)
	{
		x = windowSize.x / 2;
		y = windowSize.y / 2;

		SetCursor(x, y);
	}

	_player->OnMouseMove(DeltaX, DeltaY);
}

void Application::MenuMouseFunc(int x, int y)
{

}