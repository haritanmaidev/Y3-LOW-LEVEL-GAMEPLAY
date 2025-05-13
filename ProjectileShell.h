#pragma once
#include "InputHandler.h"
#include <iostream>
#include "GameObject.h"
#include "SoundManager.h"

class ProjectileShell : public GameObject
{
public:
	//ASK: Should these be const?
	ProjectileShell(const sf::Vector2f& spawn, const sf::Vector2f& aimDir, float projSpeed)
	: GameObject(), spawnPoint(spawn), aimDirection(aimDir), projectileSpeed(projSpeed)
	{
		if (LoadGameObjectTextureFromFile("assets/Cropped/ShellProjectile.png", std::nullopt))
		{
			sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
			sprite.setScale(sf::Vector2f(.15f, .15f));
			sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
			sprite.setPosition(spawnPoint);
			SoundManager::PlayProjectileSound();
			SetTag("ProjectileShell");
		}
	}

	void Update() override
	{
		sprite.move(velocity * projectileSpeed);
	}

	void OnCollision(const std::string& tag) override
	{
		if (tag == "Player")
		{
			SetActive(false);
		}
		else if (tag == "Projectile") 
		{
			SetActive(false);
		}
	}

private:
	sf::Vector2f spawnPoint;
	sf::Vector2f aimDirection;
	float projectileSpeed = 1.0f;
};