#include "InputHandler.h"

void InputHandler::MoveCharacter(sf::Sprite &character)
{
	speed = 4;
	direction = sf::Vector2f(0, 0); // Reset direction before checking keys

	//Y axis is reversed, hence why W gets -ve & S gets +ve
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		direction.y = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		direction.x = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		direction.y = speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		direction.x = speed;
	}

	//Normalize Speed for diagonal movement.
	if (direction.x != 0 && direction.y != 0)
	{
		//CAN I USE STANDARD LIB???
		float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= magnitude;
		direction *= speed;    // Apply the speed
	}

	// Moves the character in the new direction
	character.move(direction);
}

void InputHandler::FireProjectile(sf::Sprite& projectile)
{
	projectileSpeed = 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		if (direction != sf::Vector2f(0, 0)) // Ensure a direction exists
		{
			projectile.move(sf::Vector2f(direction.x * projectileSpeed, direction.y * projectileSpeed));
		}
		else
		{
			projectile.move(sf::Vector2f(0, projectileSpeed)); // Default direction if no movement keys are pressed
		}
	}
}
