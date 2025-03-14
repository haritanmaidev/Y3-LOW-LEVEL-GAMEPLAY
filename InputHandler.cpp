#include "InputHandler.h"

void InputHandler::MoveCharacter(sf::Sprite &character)
{
	int speed = 2;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		character.move(sf::Vector2f(0, -speed));
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		character.move(sf::Vector2f(-speed, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		character.move(sf::Vector2f(0, speed));
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		character.move(sf::Vector2f(speed, 0));
	}

	//Normalize Speed for diagonal movement.
}