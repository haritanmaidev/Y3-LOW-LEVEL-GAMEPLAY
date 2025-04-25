#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"


class Projectile : public GameObject
{
public:

	virtual void Fire();
	virtual void Update();
	virtual void SpawnProjectile();

	//Projectile(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction, float speed)
	//	: speed(speed), direction(direction)
	//{
	//	sprite.setTexture(texture);
	//	sprite.setPosition(position);
	//	sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
	//}
	void Update(float deltaTime)
	{
		sprite.move(direction * speed * deltaTime);
	}
	void Render(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
	sf::FloatRect GetGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}

private:
	sf::Vector2f direction;
	float speed = 0.0f;
};