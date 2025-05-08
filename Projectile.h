#pragma once
#include "InputHandler.h"
#include <iostream>
#include "GameObject.h"
#include <SFML/Audio.hpp>

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

		if (!buffer.loadFromFile("Audio/SpaceGunShot.wav"))
		{
			std::cout << "Sound didn't load!" << std::endl;
			return;
		}

		SetTag("Projectile");
		PlaySound();
		SetActive(true);
	}

	//NOTE:Removing Awake is throwing me "Projectile can't instantiate abstract class" error
	void Awake() override
	{
	}

	void Update() override
	{
		sprite.move(aimDirection * projectileSpeed);
		ProjectileBorderCheck();
		//std::cout << "ProjectileList's Update is called!" << std::endl;
	}

	void OnCollision() override
	{
		Die();
	}

	void ProjectileBorderCheck()
	{
		sf::Vector2f pos = sprite.getPosition();
		if (pos.x < 0 || pos.x > 1000 || pos.y < 0 || pos.y > 1000) { SetActive(false); }
	}

	void Die()
	{
		SetPosition(2000, 2000);
		SetActive(false);
	}

	void PlaySound() 
	{
		sound.setVolume(40.f);
		sound.play();
	}

private:
	sf::Vector2f spawnPoint;
	sf::Vector2f aimDirection;
	float projectileSpeed = 1.0f;

	sf::SoundBuffer buffer;
	sf::Sound sound = sf::Sound(buffer);
};