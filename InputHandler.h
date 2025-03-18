#include <SFML/Graphics.hpp>

#pragma once
class InputHandler
{
public:
	static void MoveCharacter(sf::Sprite &character);
	static void FireProjectile(sf::Sprite projectile);
	static sf::Vector2f direction;

private:
	int speed = 2;
	int projectileSpeed = 10;
};

