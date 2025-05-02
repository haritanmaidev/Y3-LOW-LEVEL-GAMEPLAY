#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerCharacter.h"

// Forward declaratio
//class PlayerCharacter;

class EntityManager;

class InputHandler
{
public:
	void Update(sf::Sprite& characterRef, sf::Sprite& projectileRef);
	void MoveCharacter(PlayerCharacter& character);
	//ASK: Should these be const?
	void FireProjectile(EntityManager& entManger, const sf::Vector2f& position, const sf::Vector2f& direction, float speed, float& deltaTime);

	sf::Vector2f direction = sf::Vector2f(0, 0);
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	sf::Vector2f lastDirection = sf::Vector2f(1.f, 0);

	bool isFiring = false;
	float fireRate = 1.f;
	float time = 0.f;
};