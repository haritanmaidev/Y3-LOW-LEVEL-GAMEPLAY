#pragma once
#include <iostream>
#include <cmath>
#include "SoundManager.h"
#include "PlayerCharacter.h"
#include "EntityManager.h"

class ProjectileSnake : public GameObject
{
public:
	//ASK: Should these be const?
	ProjectileSnake(const sf::Vector2f& spawn, const sf::Vector2f& aimDir, float projSpeed, const PlayerCharacter& playerRef, EntityManager& entityManRef)
	: GameObject(), spawnPoint(spawn), aimDirection(aimDir), projectileSpeed(projSpeed), player(playerRef), entityManager(entityManRef)
	{
		if (LoadGameObjectTextureFromFile("assets/Cropped/ProjectileSnake.png", std::nullopt))
		{
			sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
			sprite.setScale(sf::Vector2f(.1f, .1f));
			sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
			sprite.setPosition(spawnPoint);
			SoundManager::PlayProjectileSound();
			SetTag("ProjectileSnake");
			aimDirection = aimDir;
		}
	}

	void Update() override
	{
		sf::Vector2f dir = player.GetPositionConst() - sprite.getPosition();
		float mag = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		if (mag != 0.f) { dir /= mag; }

		sf::Vector2f perpendicular = { -dir.y, dir.x };
		float wiggleMax = 0.1f;
		float wiggle = entityManager.GetRandomNumber(-wiggleMax, wiggleMax);

		dir += perpendicular * wiggle;
		mag = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		if (mag != 0.f) { dir /= mag; }

		sprite.move(dir * projectileSpeed);
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
	EntityManager& entityManager;
	const PlayerCharacter& player;
	sf::Vector2f spawnPoint;
	sf::Vector2f aimDirection;
	float projectileSpeed = 1.f;
};