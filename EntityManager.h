#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "PlayerCharacter.h"
#include "InputHandler.h"
#include "EnemyCharacter.h"
#include <random>

class EntityManager
{
public:
	EntityManager()
	{
		Player = std::make_unique<PlayerCharacter>(sf::Vector2f(100.f, 100.f));

		//ASK: This crashes the game?
		//SpawnPlayerCharacter(sf::Vector2f(100.f, 100.f));
	}

	~EntityManager() = default;

	template <typename T> void Add(std::unique_ptr<T> && entity, std::vector<std::unique_ptr<T>>& list)
	{
		list.push_back(std::move(entity));
	}

	template <typename T> void UpdateAll(std::vector<std::unique_ptr<T>>& list)
	{
		for (auto& entity : list)
		{
			if(entity->IsActive()) entity->Update();
		}
	}

	template <typename T> void RenderAll(std::vector<std::unique_ptr<T>>& list, sf::RenderWindow& window)
	{
		for (auto& entity : list)
		{
			if (entity->IsActive()) entity->Render(window);
		}
	}

	//==================================:::::|||||[CHARACTER STUFF][CHARACTER STUFF][CHARACTER STUFF]|||||:::::==================================//
	Character& GetPlayer() { return *Player; }

	void AddPlayerToCharacterList(std::unique_ptr<PlayerCharacter>& player)
	{ 
		Add(std::unique_ptr<Character>(player.release()), CharacterList);
	}

	//NOTE: Current not used since I'm focusing on Singleplayer functionality
	void SpawnPlayerCharacter(const sf::Vector2f& position)
	{
		auto newCharacter = std::make_unique<PlayerCharacter>(position);
		newCharacter->SetActive(true);
		//PlayerPtr = newCharacter.get();
		AddPlayerToCharacterList(newCharacter);
	}

	void AddEnemyToCharacterList(std::unique_ptr<EnemyCharacter>& enemy)
	{
		Add(std::unique_ptr<Character>(enemy.release()), CharacterList);
	}

	void SpawnEnemyCharacter(const sf::Vector2f& position)
	{
		sf::Vector2f randomDirection = GetRandomDirection(-1.f, 1.f);
		auto newCharacter = std::make_unique<EnemyCharacter>(position, *Player, randomDirection);
		newCharacter->SetVelocity(randomDirection);
		newCharacter->SetActive(true);
		AddEnemyToCharacterList(newCharacter);
		//Add(std::unique_ptr<GameObject>(newCharacter.release()), GameObjectList);
	}
	
	void EnemySpawner() 
	{
		spawnTimer += 0.1f;
		if (spawnRate < spawnTimer)
		{
			// Getting Random values between 0 and 1 and scaling them to desired proportion
			float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			float distance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			angle *= 2.f * 3.14f;
			distance *= 200.f;
			sf::Vector2f spawnPosition = sf::Vector2f(800.f, static_cast<float>(rand() % 1000)) + 
										 sf::Vector2f(cos(angle) * distance, sin(angle) * distance);
			SpawnEnemyCharacter(spawnPosition);
			spawnTimer = 0.f;
		}
	}

	void UpdateAllCharacters(sf::RenderWindow & window, InputHandler& inputHandler)
	{
		UpdateAll(CharacterList);

		inputHandler.MoveCharacter(*Player);
		inputHandler.FireProjectile(*this, Player->GetSprite().getPosition(), GetMouseDirection(window, *Player), 20.f);

		//ASK: How can I make this work with Character foreach loop? Player throws an error throughout the script when moved in the memory due to AddPlayer... function
		BorderCollisionCheck(*Player);

		for (auto& character : CharacterList)
		{
			if (character->IsActive())
			{
				BorderCollisionCheck(*character);
			}
		}
	}

	void RenderAllCharacters(sf::RenderWindow& window)
	{
		Player->Render(window);
		RenderAll(CharacterList, window);
	}

	void ProjectileToEnemyCollisionCheck()
	{
		for (int i = 0; i < ProjectileList.size(); i++)
		{
			for (int j = 0; j < CharacterList.size(); j++)
			{
				if (ProjectileList[i]->GetSprite().getGlobalBounds().findIntersection(CharacterList[j]->GetSprite().getGlobalBounds())) 
				{
					std::cout << "Projectile: " << i << "! Collided with Enemy: "<< j << std::endl;
					ProjectileList[i]->OnCollision();
					CharacterList[j]->OnCollision();
				}
			}
		}
	}

	void RemoveEntityFromList()
	{
		for (int i = 0; i < ProjectileList.size(); i++)
		{
			if (!ProjectileList[i]->IsActive())
			{
				ProjectileList.erase(ProjectileList.begin() + i);
				std::cout << "Projectile: " << i << " removed from list!" << std::endl;
			}
		}

		for(int i = 0; i < CharacterList.size();i++)
		{
			if(!CharacterList[i]->IsActive())
			{
				CharacterList.erase(CharacterList.begin() + i);
				std::cout << "Character: " << i << " removed from list!" << std::endl;
			}
		}
	}

	//==================================:::::|||||[PROJECTILE STUFF][PROJECTILE STUFF][PROJECTILE STUFF]|||||:::::==================================//
	void AddProjectile(std::unique_ptr<Projectile> projectile)
	{
		Add(std::move(projectile), ProjectileList);
		//Add(std::unique_ptr<GameObject>(projectile.release()), GameObjectList);
		std::cout << "Projectile List Length = " << ProjectileList.size() << std::endl;
	}

	void SpawnProjectile(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<Projectile>(position, direction, speed);
		newProjectile->SetActive(true);
		AddProjectile(std::move(newProjectile));
	}

	void UpdateAllProjectiles() { UpdateAll(ProjectileList); }

	void RenderAllProjectiles(sf::RenderWindow& window){ RenderAll(ProjectileList, window); }

	//==================================:::::|||||[ALL GAME OBJECTS][ALL GAME OBJECTS][ALL GAME OBJECTS]|||||:::::==================================//
	void AddEntity(std::unique_ptr<GameObject>& entity) { Add(std::move(entity), GameObjectList); }

	void UpdateAllEntities() { UpdateAll(GameObjectList); }

	void RenderAllGameObjects(sf::RenderWindow& window) { RenderAll(GameObjectList, window); }

protected:
	std::unique_ptr <PlayerCharacter> Player;
	std::vector<std::unique_ptr<GameObject>> GameObjectList;
	std::vector<std::unique_ptr<Character>> CharacterList;
	std::vector<std::unique_ptr<Projectile>> ProjectileList;

	float spawnTimer = 0.f;
	float spawnRate = 5.f;

	float GetRandomNumber(float a, float b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(a, b);
		float randomNumber = dis(gen);
		return randomNumber;
	}

	sf::Vector2f GetRandomDirection(float a, float b) 
	{
		return sf::Vector2f(GetRandomNumber(a, b), GetRandomNumber(a, b));
	}

	sf::Vector2f GetMouseDirection(sf::RenderWindow& window, PlayerCharacter& player)
	{
		float angle = atan2(sf::Mouse::getPosition(window).y - player.GetSprite().getPosition().y,
							sf::Mouse::getPosition(window).x - player.GetSprite().getPosition().x);

		return sf::Vector2f(cos(angle), sin(angle));
	}

	void BorderCollisionCheck(Character& mainCharacter)
	{
		//TODO: Makes this work with hitbox variable
		//REFACTOR NOTE: COULD REFACTOR TO MAKE IT CLEANER!!
		//Right Collision
		if (mainCharacter.GetSprite().getPosition().x < 0)
		{
			mainCharacter.GetSprite().setPosition(sf::Vector2f(0, mainCharacter.GetSprite().getPosition().y));
			mainCharacter.SetVelocity(sf::Vector2f(-mainCharacter.GetVelocity().x, mainCharacter.GetVelocity().y));
		}
		//Left Collision
		if (mainCharacter.GetSprite().getPosition().x + mainCharacter.GetSprite().getGlobalBounds().size.x > 1000)
		{
			mainCharacter.GetSprite().setPosition(sf::Vector2f(1000 - mainCharacter.GetSprite().getGlobalBounds().size.x, mainCharacter.GetSprite().getPosition().y));
			mainCharacter.SetVelocity(sf::Vector2f(-mainCharacter.GetVelocity().x, mainCharacter.GetVelocity().y));
		}
		//Top Collision
		if (mainCharacter.GetSprite().getPosition().y < 0)
		{
			mainCharacter.GetSprite().setPosition(sf::Vector2f(mainCharacter.GetSprite().getPosition().x, 0));
			mainCharacter.SetVelocity(sf::Vector2f(mainCharacter.GetVelocity().x, -mainCharacter.GetVelocity().y));
		}
		//Bottom Collision
		if (mainCharacter.GetSprite().getPosition().y + mainCharacter.GetSprite().getGlobalBounds().size.y > 1000)
		{
			mainCharacter.GetSprite().setPosition(sf::Vector2f(mainCharacter.GetSprite().getPosition().x, 1000 - mainCharacter.GetSprite().getGlobalBounds().size.y));
			mainCharacter.SetVelocity(sf::Vector2f(mainCharacter.GetVelocity().x, -mainCharacter.GetVelocity().y));
		}
	}
};