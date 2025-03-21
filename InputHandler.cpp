#include "InputHandler.h"

void InputHandler::MoveCharacter(sf::Sprite &character)
{
	speed = 4;
	projectileSpeed = 10;
	direction = sf::Vector2f(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		direction = sf::Vector2f(0, -speed);
		character.move(direction);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		direction = sf::Vector2f(-speed, 0);
		character.move(direction);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		direction = sf::Vector2f(0, speed);
		character.move(direction);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		direction = sf::Vector2f(speed, 0);
		character.move(direction);
	}

	//Normalize Speed for diagonal movement.
}

void InputHandler::FireProjectile(sf::Sprite &projectile)
{
	projectile.move(sf::Vector2f(direction.x * projectileSpeed, direction.y * projectileSpeed));
}