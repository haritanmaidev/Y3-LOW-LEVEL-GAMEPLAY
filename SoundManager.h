#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager
{
public:
	static void PlaySound(const std::string& filepath, float volume = 50.f)
	{
		//NOTE: Making shared to ensure buffer is active as long as any object uses it
		std::shared_ptr<sf::SoundBuffer> buffer = std::make_shared<sf::SoundBuffer>();
		if (!buffer->loadFromFile(filepath)) 
		{ 
			std::cout << "Sound didn't load!" << std::endl;
		}
		std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>(*buffer);
		sound->setVolume(volume);
		sound->play();
		Sounds.push_back(std::make_pair(std::move(sound), buffer));
	}

	static void PlayPlayerHurtSound() { PlaySound("Audio/PlayerHurt.wav", 15.f); }
	static void PlayProjectileSound() { PlaySound("Audio/GunFireBlop.wav", 25.f); }
	static void PlayEnemySpawnSound() { PlaySound("Audio/EnemySpawn.wav", 40.f); }
	static void PlayEnemyHurtSound() { PlaySound("Audio/EnemyHit.wav", 50.f); }
	static void PlayEnemyDeathSound() { PlaySound("Audio/EnemyDeath.wav", 60.f);}
	static void PlayHumanRescueSound() { PlaySound("Audio/HumanPickup.wav", 65.f); }

	static void CleanUpSounds()
	{
		for (int i = 0; i < Sounds.size(); i++)
		{
			if (Sounds[i].first->getStatus() == sf::Sound::Status::Stopped)
			{
				Sounds.erase(Sounds.begin() + i);
				i--;
			}
		}
	}

private:
	inline static std::vector<std::pair<std::unique_ptr<sf::Sound>, std::shared_ptr<sf::SoundBuffer>>> Sounds;
};