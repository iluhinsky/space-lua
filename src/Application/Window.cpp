#include "Window.h"

Window::Window()
{}

Window::~Window()
{
	delete window_;
	delete platform_;
}

bool Window::InitWindow(sf::Vector2u size, std::string title)
{
	sf::ContextSettings settings;

	settings.depthBits         = 24;
	settings.stencilBits       = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion      = 3;
	settings.minorVersion      = 0;

	if ((window_ = new sf::Window(sf::VideoMode(size.x, size.y), title, sf::Style::Default, settings)) == nullptr)
		return false;

	window_ -> setVerticalSyncEnabled(true);

	platform_ = new Platform;

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		exit(-1);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	keys_ = {
		sf::Keyboard::A,
		sf::Keyboard::D,
		sf::Keyboard::W,
		sf::Keyboard::S,
		sf::Keyboard::Q,
		sf::Keyboard::E
	};

	sf::Vector2u windowSize = GetWindowSize();

	SetCursor(windowSize.x / 2, windowSize.y / 2);
	prevMousePos_ = sf::Mouse::getPosition();

	return true;
}

void Window::MainLoop()
{
	sf::Event event;

	isLoopRunning_ = true;

	while (isLoopRunning_)
	{
		while (window_->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				CloseFunction();
				break;

			case sf::Event::Resized:
				ReshapeFunc(event.size.width, event.size.height);
				break;

			case sf::Event::MouseMoved:
				PassiveMotionFunc(event.mouseMove.x, event.mouseMove.y);
				break;


			default:
				break;
			}
		}

		KeyboardFunc();

		DisplayFunc();
	}
}

void Window::StopLoop()
{
	isLoopRunning_ = false;
}

sf::Vector2u Window::GetWindowSize()
{
	return window_->getSize();
}

void Window::SetCursor(int x, int y)
{
	sf::Vector2i position(x, y);

	sf::Mouse::setPosition(position, *window_);
}

void Window::ClipCursorInWindow()
{
	sf::Vector2i position   = window_->getPosition();
	sf::Vector2u windowSize = window_->getSize();

	int borderSize = 50;

	platform_->PlatformClipCursor(position.x + borderSize, position.y + borderSize,
		position.x + windowSize.x - borderSize, position.y + windowSize.y - borderSize);
}

void Window::ShowCursor(bool state)
{
	window_->setMouseCursorVisible(state);
}