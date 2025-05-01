#include "InputHandler.h"
#include "PlayerCharacter.h"
#include <iostream>

void InputHandler::Update(sf::Sprite &characterRef, sf::Sprite& projectileRef)
{
	//ASK: Is this the right way to do this?
	//MoveCharacter(characterRef);
	//FireProjectile();
}	

void InputHandler::MoveCharacter(PlayerCharacter& character)
{
	//Resetting direction to 0 since this runs every frame. To stop the character movement when no inputs pressed
	direction = sf::Vector2f(0, 0);

	//Y axis is reversed, hence why the W key gets -ve & the S key gets +ve
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		direction.y = -playerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		direction.x = -playerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		direction.y = playerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		direction.x = playerSpeed;
	}

	velocity = direction;

	//Normalize Speed for diagonal movement.
	if (direction.x != 0 && direction.y != 0)
	{
		float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= magnitude;
		velocity = direction * playerSpeed;
		lastDirection = velocity;
	}
	else if (direction.x != 0 || direction.y != 0)
	{
		lastDirection = direction;
	}

	character.GetSprite().move(velocity);
}

void InputHandler::FireProjectile(EntityManager& entManger, const sf::Vector2f& position, const sf::Vector2f& direction, float speed, float& deltaTime)
{
	time += 0.1f;
	if (fireRate < time) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			std:: cout<< "Time value is:" << time << std::endl;
			isFiring = true;
			entManger.SpawnProjectile(position, direction, speed);
			time = 0.f;
			//std::cout << "Spacebar Pressed!" << std::endl;
		}
		else
		{
			isFiring = false;
		}
	}

}

