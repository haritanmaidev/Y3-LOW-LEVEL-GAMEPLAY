#pragma once
#include "InputHandler.h"
#include <iostream>
#include "GameObject.h"
#include "SoundManager.h"

class ProjectileSnake : public GameObject
{
public:
	//ASK: Should these be const?
	ProjectileSnake(const sf::Vector2f& spawn, const sf::Vector2f& aimDir, float projSpeed, const PlayerCharacter& playerRef)
	: GameObject(), spawnPoint(spawn), aimDirection(aimDir), projectileSpeed(projSpeed), player(playerRef)
	{
		if (LoadGameObjectTextureFromFile("assets/Cropped/BasicProjectile.png", std::nullopt))
		{
			sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
			sprite.setScale(sf::Vector2f(.25f, .25f));
			sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
			sprite.setPosition(spawnPoint);
			sprite.setColor(sf::Color::Red);
			SoundManager::PlayProjectileSound();
			SetTag("ProjectileSnake");
		}
	}

	void Update() override
	{
		sf::Vector2f playerPosition = player.GetPositionConst();
		sf::Vector2f position = sprite.getPosition();
		sf::Vector2f direction = playerPosition - position;
		float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= mag;

		sprite.move(direction * projectileSpeed);
	}

	void OnCollision(const std::string& tag) override
	{
		if (tag == "Player")
		{
			//std::cout << "Projectile collided with: " << tag << std::endl;
			SetActive(false);
		}
		else if (tag == "Projectile")
		{
			UIManager::AddScore(25);
			SoundManager::PlayEnemyHurtSound();
			//SoundManager::PlayProjectileDestroySound();
			SetActive(false);
		}
	}

private:
	const PlayerCharacter& player;
	sf::Vector2f spawnPoint;
	sf::Vector2f aimDirection;
	float projectileSpeed = 1.f;
};