#include "Player.h"

const static float StepScale = 0.1f;

Player::Player()
{
	_camera = new Camera();

	_cameraPos = glm::vec3(-10.0f, 0.0f, 5.0f);
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
	glm::mat4 Rotate;

	switch (key) {

	case sf::Keyboard::W:
		_object->_worldPos += (_object->_target * StepScale);
		break;

	case sf::Keyboard::S:
		_object->_worldPos -= (glm::vec3(1.0f, 0.0f, 0.0f) * StepScale);
		break;

	case sf::Keyboard::A:
		Rotate = glm::rotate(glm::mat4(1.0f), (float)ToRadian(-2.0f), _object->_target);

		_object->_up = glm::normalize(glm::vec3(Rotate * glm::vec4(_object->_up, 1.0f)));
		break;

	case sf::Keyboard::D:
		Rotate = glm::rotate(glm::mat4(1.0f), (float)ToRadian(2.0f), _object->_target);

		_object->_up = glm::normalize(glm::vec3(Rotate * glm::vec4(_object->_up, 1.0f)));
		break;

	case sf::Keyboard::Q:
		_object->_worldPos -= (glm::vec3(0.0f, 0.0f, 1.0f) * StepScale);
		break;

	case sf::Keyboard::E:
		_object->_worldPos += (glm::vec3(0.0f, 0.0f, 1.0f) * StepScale);
		break;
	}
}

void Player::OnMouse(int x, int y)
{

}

void Player::OnMouseMove(int DeltaX, int DeltaY)
{
	glm::mat4 Rotate;
	
	Rotate = glm::rotate(glm::mat4(1.0f), (float)ToRadian(DeltaY/5.0f), 
		glm::normalize(glm::cross(_object->_up, _object->_target)));

	_object->_target = glm::normalize(glm::vec3(Rotate * glm::vec4(_object->_target, 1.0f)));
	_object->_up     = glm::normalize(glm::vec3(Rotate * glm::vec4(_object->_up    , 1.0f)));
}

void Player::UpdateCamera()
{
	_camera->m_pos = _object->_worldPos +
		_cameraPos.x * _object->_target +
		_cameraPos.y * glm::normalize(glm::cross(_object->_up, _object->_target)) +
		_cameraPos.z * _object->_up;

	_camera->m_target = _object->_target;
	_camera->m_up     = _object->_up;	
}

void Player::BindCamera(AbstractObject* object)
{
	//_camera->BindObject();
}