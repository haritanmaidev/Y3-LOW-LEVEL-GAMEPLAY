#pragma once
#include "InputHandler.h"
#include <iostream>
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	//ASK: Should these be const?
	Projectile(const sf::Vector2f& spawn, const sf::Vector2f& aimDir, float projSpeed) 
	: GameObject(), spawnPoint(spawn), aimDirection(aimDir), projectileSpeed(projSpeed)
	{
		//sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
		LoadGameObjectTexture("assets/Cropped/BasicProjectile.png");
		sprite.setPosition(spawnPoint);
		sprite.setScale(sf::Vector2f(.25f, .25f));
		SetActive(true);
	}

	void Awake() override
	{
	}

	void Update() override
	{
		//std::cout << "ProjectileList's Update is called!" << std::endl;
		sprite.move(aimDirection * projectileSpeed);
		//std::cout << "Projectile moved to: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
	}

	void OnCollision() override
	{
		SetActive(false);
	}

private:
	sf::Vector2f spawnPoint;
	sf::Vector2f aimDirection;
	float projectileSpeed = 1.0f;
};