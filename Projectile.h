#pragma once
#include "InputHandler.h"
#include <iostream>
#include "GameObject.h"
#include "SoundManager.h"

class Projectile : public GameObject
{
public:
	//ASK: Should these be const?
	Projectile(const sf::Vector2f& spawn, const sf::Vector2f& aimDir, float projSpeed) 
	: GameObject(), spawnPoint(spawn), aimDirection(aimDir), projectileSpeed(projSpeed)
	{;
		LoadGameObjectTextureFromFile("assets/Cropped/BasicProjectile.png", std::nullopt);
 		sprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(texture->getSize())));
		sprite.setScale(sf::Vector2f(.25f, .25f));
		sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
		sprite.setPosition(spawnPoint);
		SoundManager::PlayProjectileSound();
		SetTag("Projectile");
		SetActive(true);
	}

	void Update() override
	{
		sprite.move(aimDirection * projectileSpeed);
		ProjectileBorderCheck();
		//std::cout << "ProjectileList's Update is called!" << std::endl;
	}

	void OnCollision(const std::string& tag) override
	{
		if(tag == "Enemy")
		{
			std::cout << "Projectile collided with: " << tag << std::endl;
			SetActive(false);
		}
		else if(tag == "EnemyHulk")
		{
			std::cout << "Projectile collided with: " << tag << std::endl;
			SetActive(false);
		}
	}

	void ProjectileBorderCheck()
	{
		sf::Vector2f pos = sprite.getPosition();
		if (pos.x < 0 || pos.x > 1000 || pos.y < 0 || pos.y > 1000) SetActive(false);
	}

private:
	sf::Vector2f spawnPoint;
	sf::Vector2f aimDirection;
	float projectileSpeed = 1.0f;
};