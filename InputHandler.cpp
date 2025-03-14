#include "InputHandler.h"

void InputHandler::MoveCharacter(sf::Sprite & character)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		character.move(sf::Vector2f(0, 1));
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		character.move(sf::Vector2f(1, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		character.move(sf::Vector2f(0, -1));
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		character.move(sf::Vector2f(-1, 0));
	}
}