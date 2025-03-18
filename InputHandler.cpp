#include "InputHandler.h"

int main()
{
	
}

void InputHandler::MoveCharacter(sf::Sprite &character)
{
	int speed = 2;
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

void InputHandler::FireProjectile(sf::Sprite projectile)
{
	int speed = 10.f;

	projectile.move(sf::Vector2f(direction.x * speed, direction.y * speed));
}