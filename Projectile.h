#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
#include "InputHandler.h"

class Projectile : public GameObject
{
public:
	Projectile(sf::RenderWindow& window, const sf::Vector2f& spawn, const sf::Vector2f& aimDir, float projSpeed) 
		: GameObject(), renderWindow(window), spawnPoint(spawn), aimDirection(aimDir), projectileSpeed(projSpeed)
	{
		LoadGameObjectTexture("assets/Cropped/BasicProjectile.png");
		sprite.setPosition(spawnPoint);
		sprite.setScale(sf::Vector2f(15.f, 15.f));
		sf::Texture projTexture;
		const sf::Image LoadSprite("assets/Cropped/BasicProjectile.png");
		bool result = projTexture.loadFromImage(LoadSprite);
		sf::Sprite projSprite(projTexture);
		SetActive(true);
		//sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
	}

	void Awake() override
	{
	}

	void Update() override
	{
		sprite.move(aimDirection * projectileSpeed);
		//std::cout << "Projectile moved to: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;

	}

	void OnCollision() override
	{
		//Call this in CollisionManager for GameObjects
		SetActive(false);
	}

private:
	sf::Vector2f spawnPoint;
	sf::Vector2f aimDirection;
	sf::RenderWindow& renderWindow;
	float projectileSpeed = 1.0f;
};