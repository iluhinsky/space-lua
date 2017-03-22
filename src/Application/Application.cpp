#include "Application.h"

#include "../Game/World/World.h"

Application* Application::instance_ = nullptr;


Application::Application()
{
}

Application::~Application() 
{
	delete world_;
	delete player_;
}

void Application::Init()
{
	instance_ = this;

	if (!InitWindow(sf::Vector2u(800, 600), "Out of Space"))
	{
		fprintf(stderr, "Error: Can't open window\n");
		exit(-1);
	}

	ClipCursorInWindow();
	ShowCursor(false);

	clocks_.restart();

	currentState_ = Game;

	player_       = new Player;
	world_        = new World;

	world_->Init();
	world_->Load("Mustafar.txt");
}

sf::Time Application::getTime() const
{
	return clocks_.getElapsedTime();
}

void Application::DisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	player_->UpdateCamera();

	world_->Draw(player_->GetCamera());

	window_->display();
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

	for (auto it = keys_.begin(); it != keys_.end(); ++it)
		if (sf::Keyboard::isKeyPressed(*it)) player_->OnKeyboard(*it);
}

void Application::PassiveMotionFunc(int x, int y)
{
	if      (currentState_ == Game) GameMouseFunc (x, y);
	else if (currentState_ == Menu) MenuMouseFunc (x, y);
}

void Application::GameMouseFunc(int x, int y)
{
	const int DeltaX = x - prevMousePos_.x;
	const int DeltaY = y - prevMousePos_.y;

	prevMousePos_.x = x;
	prevMousePos_.y = y;

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

	player_->OnMouseMove(DeltaX, DeltaY);
}

void Application::MenuMouseFunc(int x, int y)
{

}