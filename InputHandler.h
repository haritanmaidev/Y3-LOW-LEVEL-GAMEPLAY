#pragma once

#include <SFML/Graphics.hpp>

class InputHandler
{
public:
	void MoveCharacter(sf::Sprite &character);
	void FireProjectile(sf::Sprite &projectile);
	sf::Vector2f direction;
private:
	int speed = 2;
	int projectileSpeed = 10;
};
