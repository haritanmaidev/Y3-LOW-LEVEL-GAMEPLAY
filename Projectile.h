#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "InputHandler.h"


class Projectile : public GameObject
{
public:
	InputHandler inputHandler;	

	void Awake() override
	{
		LoadGameObjectTexture("assets/Cropped/BasicProjectile.png");
		sprite.setPosition(sf::Vector2f(200, 200));
		sprite.setScale(sf::Vector2f(1.5f, 1.5f));
		//Could pre-write this
		sf::Vector2f newOrigin = sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y/2.f);
		sprite.setOrigin(newOrigin);
		speed = 5.0f;
		//ASK: If SetActive is better or manually setting isActive = true better?
		SetActive(true);
		Update();
	}

	void SetDirection(sf::Vector2f direction)
	{
		aimDirection = direction;
	}

	void Update() override
	{
		sprite.move(aimDirection * speed);
	}

	void OnCollision() override
	{
		//Call this in CollisionManager for GameObjects
		SetActive(false);
	}

	sf::FloatRect GetGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}

private:
	sf::Vector2f aimDirection;
	float speed = 0.0f;
};