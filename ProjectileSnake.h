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
	ProjectileSnake(const sf::Vector2f& spawn, const sf::Vector2f& aimDir, float projSpeed, const PlayerCharacter& playerRef)
	: GameObject(), spawnPoint(spawn), direction(aimDir), projectileSpeed(projSpeed), player(playerRef)
	{
		if (LoadGameObjectTextureFromFile("assets/Cropped/ProjectileSnake.png", std::nullopt))
		{
			sprite.setTextureRect(sf::IntRect({ 0, 0 }, sf::Vector2i(texture->getSize())));
			sprite.setScale(sf::Vector2f(.08f, .05f));
			sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f));
			sprite.setPosition(spawnPoint);
			score = 50;
			SoundManager::PlayProjectileSound();
			SetTag("ProjectileSnake");
			direction = aimDir;
		}
	}

	void Update() override
	{
		wiggleTimer += 0.1f;
		if (wiggleTimer > wiggleRate)
		{
			direction = player.GetPositionConst() - sprite.getPosition();

			float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			if (mag != 0.f) { direction /= mag; }

			sf::Vector2f perpendicular = { -direction.y, direction.x };
			//float wiggle = entityManager.GetRandomNumber(-wiggleMax, wiggleMax);
			float wiggleMax = 1.5f;
			float wiggle = ((std::rand() % 201) - 100) / 100.0f * wiggleMax;
			direction += perpendicular * wiggle;

			mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			if (mag != 0.f) { direction /= mag; }
			wiggleTimer = 0.f;
		}

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
			UIManager::AddScore(score);
			SoundManager::PlayEnemyHurtSound();
			//SoundManager::PlayProjectileDestroySound();
			SetActive(false);
		}
	}

private:
	const PlayerCharacter& player;
	sf::Vector2f spawnPoint;
	sf::Vector2f direction;
	float projectileSpeed = 0.5f;
	float wiggleRate = 2.f;
	float wiggleTimer = 0.f;
	int score = 50;
};