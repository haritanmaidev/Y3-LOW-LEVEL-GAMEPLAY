#pragma once
#include <SFML/Graphics.hpp>

class InputHandler
{
public:
	void Update(sf::Sprite& characterRef, sf::Sprite& projectileRef);
	void MoveCharacter(sf::Sprite &character);
	void FireProjectile();

	sf::Vector2f direction = sf::Vector2f(0, 0);
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	sf::Vector2f lastDirection = sf::Vector2f(1.f, 0);

	bool isFiring = false;

private:
	float playerSpeed = 10;
	float projectileSpeed = 2;
};
