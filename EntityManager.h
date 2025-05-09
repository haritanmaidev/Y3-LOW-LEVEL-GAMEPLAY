#pragma once
#include "InputHandler.h"
#include "GameObject.h"
#include "Projectile.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "HumanCharacter.h"
#include "EnemyHulk.h"
#include <random>

class EntityManager
{
public:
	//Constructor & Destructor
	EntityManager()
	{
		SpawnPlayerCharacter(sf::Vector2f(500.f, 500.f));
		SpawnHumanCharacter(GetRandomDirection(100, 500));
	}
	~EntityManager() = default;

	//==================================:::::|||||[--- TEMPLATE FUNCTIONS ---]|||||:::::==================================//
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
	
	//template <typename T> void SpawnerGameObject(const sf::Vector2f& position, std::unique_ptr<T>&& clas) 
	//{

	//}

	//TO-DO: MAKE A TEMPLATE FUNCTION FOR SPAWNERS AND SpawnGameObjectFunction

	//==================================:::::|||||[--- ADD TO LIST FUNCTIONS ---]|||||:::::==================================//
	void AddEntity(std::unique_ptr<GameObject>& entity) { Add(std::move(entity), GameObjectList); }
	
	void AddPlayerToCharacterList(std::unique_ptr<PlayerCharacter>& player) { Add(std::unique_ptr<Character>(player.release()), CharacterList); }

	void AddHuman(std::unique_ptr<HumanCharacter>&& human) { Add(std::move(human), HumanList); }

	void AddHumanToCharacterList(std::unique_ptr<HumanCharacter>& human) { Add(std::unique_ptr<Character>(human.release()), CharacterList); }

	void AddEnemyToCharacterList(std::unique_ptr<EnemyCharacter>& enemy) { Add(std::unique_ptr<Character>(enemy.release()), CharacterList); }

	void AddEnemyHulkToCharacterList(std::unique_ptr<EnemyHulk>& hulk) { Add(std::unique_ptr<Character>(hulk.release()), CharacterList); }
	
	void AddProjectile(std::unique_ptr<Projectile> projectile)
{
		Add(std::move(projectile), ProjectileList);
		//Add(std::unique_ptr<GameObject>(projectile.release()), GameObjectList);
	}

	//==================================:::::|||||[--- SPAWN & SPAWNER FUNCTIONS ---]|||||:::::==================================//
	void SpawnPlayerCharacter(const sf::Vector2f& position)
	{
		auto newCharacter = std::make_unique<PlayerCharacter>(position);
		newCharacter->SetActive(true);
		Player = newCharacter.get();
		AddPlayerToCharacterList(newCharacter);
	}

	void SpawnHumanCharacter(const sf::Vector2f& position)
	{
		auto newHuman = std::make_unique<HumanCharacter>(position, *this);
		newHuman->SetActive(true);
		AddHuman(std::move(newHuman));
		//AddHumanToCharacterList(newHuman);
		//Add(std::unique_ptr<GameObject>(newCharacter.release()), GameObjectList);
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

	void SpawnEnemyHulk(const sf::Vector2f& position) 
	{
		static int HulkCount = 0;
		if (HulkCount > 5) return;
		sf::Vector2f randomDirection = GetRandomDirection(-1.f, 1.f);
		auto newHulk = std::make_unique<EnemyHulk>(position, *Player, randomDirection, *this);
		newHulk->SetVelocity(randomDirection);
		AddEnemyHulkToCharacterList(newHulk);
		HulkCount++;
	}

	void SpawnProjectile(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<Projectile>(position, direction, speed);
		newProjectile->SetActive(true);
		AddProjectile(std::move(newProjectile));
	}

	void HumanSpawner(float&& rate)
	{
		static float spawnRate = rate;
		static float spawnTimer = 0.f;
		spawnTimer += 0.1f;
		if (spawnRate < spawnTimer)
		{
			sf::Vector2f spawnPosition = sf::Vector2f(GetRandomNumber(500, 999), GetRandomNumber(0, 999));
			SpawnHumanCharacter(spawnPosition);
			spawnTimer = 0.f;
		}
	}

	void EnemySpawner(float&& rate)
	{
		static float spawnRate = rate;
		static float spawnTimer = 0.f;
		spawnTimer += 0.1f;
		if (spawnRate < spawnTimer)
		{
			float angle = GetRandomNumber(0, 360);
			float distance = GetRandomNumber(0, 200);
			float locationY = GetRandomNumber(0, 1000);
			sf::Vector2f spawnPosition = sf::Vector2f(800.f, locationY) + sf::Vector2f(cos(angle) * distance, sin(angle) * distance);
			SpawnEnemyCharacter(spawnPosition);
			spawnTimer = 0.f;
		}
	}

	void EnemyHulkSpawner(float&& rate) 
	{
		static float spawnRate = rate;
		static float spawnTimer = 0.f;
		spawnTimer += 0.1f;
		if (spawnRate < spawnTimer)
		{
			sf::Vector2f spawnPosition = sf::Vector2f(GetRandomNumber(200, 600), GetRandomNumber(0, 400));
			SpawnEnemyHulk(spawnPosition);
			spawnTimer = 0.f;
		}
	}

	//==================================:::::|||||[--- COLLISION FUNCTIONS ---]|||||:::::==================================//
	void PlayerToHumanCollisionCheck()
	{
		for (int i = 0; i < HumanList.size(); i++)
		{
			if (Player->GetSprite().getGlobalBounds().findIntersection(HumanList[i]->GetSprite().getGlobalBounds()))
			{
				HumanList[i]->OnCollision();
			}
		}
	}
	
	void PlayerToCharacterCollisionCheck()
	{
		for (int i = 1; i < CharacterList.size(); i++)
		{
			if (Player->GetSprite().getGlobalBounds().findIntersection(CharacterList[i]->GetSprite().getGlobalBounds()))
			{
				std::cout << "Player Collided with Enemy: " << i << std::endl;
				Player->OnCollision();
				CharacterList[i]->OnCollision();
			}
		}
	}
	
	void ProjectileToCharacterCollisionCheck()
	{
		for (int i = 0; i < ProjectileList.size(); i++)
		{
			for (int j = 1; j < CharacterList.size(); j++)
			{
				if (ProjectileList[i]->GetSprite().getGlobalBounds().findIntersection(CharacterList[j]->GetSprite().getGlobalBounds()))
				{
					std::cout << "Projectile: " << i << "! Collided with Enemy: " << j << std::endl;
					ProjectileList[i]->OnCollision();
					CharacterList[j]->OnCollision();
				}
			}
		}
	}

	//==================================:::::|||||[--- UPDATE FUNCTIONS ---]|||||:::::==================================//
	void UpdateAllEntities() { UpdateAll(GameObjectList); }

	void UpdateAllHumans() { UpdateAll(HumanList); }

	void UpdateAllCharacters(sf::RenderWindow& window, InputHandler& inputHandler)
	{
		UpdateAll(CharacterList);
		UpdateAll(HumanList);

		inputHandler.MoveCharacter(GetPlayer());
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
		for (auto& human : HumanList)
		{
			if (human->IsActive())
			{
				BorderCollisionCheck(*human);
			}
		}
	}

	void UpdateAllProjectiles() { UpdateAll(ProjectileList); }

	//==================================:::::|||||[--- RENDER FUNCTIONS ---]|||||:::::==================================//
	void RenderAllGameObjects(sf::RenderWindow& window) { RenderAll(GameObjectList, window); }

	void RenderAllCharacters(sf::RenderWindow& window)
	{
		RenderAll(CharacterList, window);
		RenderAll(HumanList, window);
	}

	void RenderAllHumans(sf::RenderWindow& window) { RenderAll(HumanList, window); }

	void RenderAllProjectiles(sf::RenderWindow& window) { RenderAll(ProjectileList, window); }

	//==================================:::::|||||[--- EXTRA FUNCTIONS ---]|||||:::::==================================//
	Character& GetPlayer() { return *Player; }

	void RemoveEntityFromList()
	{
		for (int i = 0; i < ProjectileList.size(); i++)
		{
			if (!ProjectileList[i]->IsActive())
			{
				ProjectileList.erase(ProjectileList.begin() + i);
				//std::cout << "Projectile: " << i << " removed from list!" << std::endl;
			}
		}

		for(int i = 0; i < CharacterList.size();i++)
		{
			if(!CharacterList[i]->IsActive())
			{
				CharacterList.erase(CharacterList.begin() + i);
				//std::cout << "Character: " << i << " removed from list!" << std::endl;
			}
		}

		for (int i = 0; i < HumanList.size(); i++)
		{
			if (!HumanList[i]->IsActive())
			{
				HumanList.erase(HumanList.begin() + i);
				//std::cout << "Human: " << i << " removed from list!" << std::endl;
			}
		}
	}

	float GetRandomNumber(float a, float b) const
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(a, b);
		float randomNumber = dis(gen);
		return randomNumber;
	}

	sf::Vector2f GetRandomDirection(float a, float b) const
	{
		return sf::Vector2f(GetRandomNumber(a, b), GetRandomNumber(a, b));
	}

protected:
	PlayerCharacter* Player;
	std::vector<std::unique_ptr<GameObject>> GameObjectList;
	std::vector<std::unique_ptr<Character>> CharacterList;
	std::vector<std::unique_ptr<Projectile>> ProjectileList;
	std::vector<std::unique_ptr<HumanCharacter>> HumanList;

private:
	sf::Vector2f GetMouseDirection(sf::RenderWindow& window, PlayerCharacter& player)
	{
		float angle = atan2(sf::Mouse::getPosition(window).y - player.GetSprite().getPosition().y,
							sf::Mouse::getPosition(window).x - player.GetSprite().getPosition().x);

		return sf::Vector2f(cos(angle), sin(angle));
	}

	void BorderCollisionCheck(Character& mainCharacter)
	{
		//REFACTOR: Makes this work with hitbox variable
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