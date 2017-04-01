#include "Player.h"

const static float StepScale = 0.1f;

Player::Player()
{
	_camera = new Camera();

	_camera->m_pos = glm::vec3(-10.0f, 7.0f, 2.0f);
}

Player::~Player()
{
	delete _camera;
}

Camera* Player::GetCamera()
{
	return _camera;
}

void Player::OnKeyboard(int key)
{
	switch (key) {

	case sf::Keyboard::W:
		_camera->m_pos += (_camera->m_target * StepScale);
		break;

	case sf::Keyboard::S:
		_camera->m_pos -= (_camera->m_target * StepScale);
		break;

	case sf::Keyboard::A:
	{
		glm::vec3 Left = glm::cross(_camera->m_up, _camera->m_target);
		Left = glm::normalize(Left);
		Left *= StepScale;
		_camera->m_pos += Left;
	}
	break;

	case sf::Keyboard::D:
	{
		glm::vec3 Right = glm::cross(_camera->m_target, _camera->m_up);
		Right = glm::normalize(Right);
		Right *= StepScale;
		_camera->m_pos += Right;
	}
	break;

	case sf::Keyboard::Q:
		_camera->m_pos -= (_camera->m_up * StepScale);
		break;

	case sf::Keyboard::E:
		_camera->m_pos += (_camera->m_up * StepScale);
		break;
	}
}

void Player::OnMouse(int x, int y)
{

}

void Player::OnMouseMove(int DeltaX, int DeltaY)
{
	_camera->m_AngleH -= (float)DeltaX / 5.0f;
	_camera->m_AngleV += (float)DeltaY / 5.0f;
}

void Player::UpdateCamera()
{
	_camera->Update();
}