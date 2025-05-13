#include "InputHandler.h"
#include "PlayerCharacter.h"
#include "EntityManager.h"
#include <iostream>

void InputHandler::Update(sf::Sprite &characterRef, sf::Sprite& projectileRef)
{
	//ASK: Is this the right way to do this?
	//MoveCharacter(characterRef);
	//FireProjectile();
}	

void InputHandler::MoveCharacter(Character& character)
{
	//Resetting direction to 0 since this runs every frame. To stop the character movement when no inputs pressed
	direction = sf::Vector2f(0, 0);

	//Y axis is reversed, hence why the W key gets -ve & the S key gets +ve
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		direction.y = -character.GetSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		direction.x = -character.GetSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		direction.y = character.GetSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		direction.x = character.GetSpeed();
	}

	//character.SetVelocity(direction);
	velocity = direction;

	//Normalize Speed for diagonal movement.
	if (direction.x != 0 && direction.y != 0)
	{
		float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= magnitude;
		velocity = direction * character.GetSpeed();
		lastDirection = velocity;
	}
	else if (direction.x != 0 || direction.y != 0)
	{
		lastDirection = direction;
	}

	//character.MoveCharacter(character.GetVelocity());
	character.GetSprite().move(velocity);
	std::cout << "Character Position: " << character.GetPosition().x << ", " << character.GetPosition().y << std::endl;
}

void InputHandler::FireProjectile(EntityManager& entManger, const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
{
	time += 0.1f;
	if (fireRate < time) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			isFiring = true;
			entManger.SpawnProjectile(position, direction, speed);
			time = 0.f;
		}
		else
		{
			isFiring = false;
		}
	}
}

void InputHandler::GetCoordinates(const sf::RenderWindow& win)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(win);
		std::cout << "Mouse Position: " << pixelPos.x << ", " << pixelPos.y << std::endl;
	}
}

