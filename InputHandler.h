#pragma once
#include <SFML/Graphics.hpp>

class InputHandler
{
public:
	void Update(sf::Sprite& characterRef, sf::Sprite& projectileRef);
	void MoveCharacter(sf::Sprite &character);
	void FireProjectile(sf::Sprite &projectile);
	sf::Vector2f direction = sf::Vector2f(0, 0);
private:
	float speed = 2;
	float projectileSpeed = 10;
};
