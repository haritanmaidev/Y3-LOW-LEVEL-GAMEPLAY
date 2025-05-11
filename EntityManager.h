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
		SpawnHumanCharacter(GetRandomVector(100, 500));
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
			if (entity->IsActive()) 
			{
				entity->Update();
				BorderCollisionCheck(*entity);
			} 
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
	void AddGameObjectToGameObjectList(std::unique_ptr<GameObject>& entity) { Add(std::move(entity), GameObjectList); }
	
	void AddPlayerToGameObjectList(std::unique_ptr<PlayerCharacter>& player) { Add(std::unique_ptr<GameObject>(player.release()), GameObjectList); }

	void AddHumanToGameObjectList(std::unique_ptr<HumanCharacter>& human) { Add(std::unique_ptr<GameObject>(human.release()), GameObjectList); }

	void AddEnemyGruntToGameObjectList(std::unique_ptr<EnemyCharacter>& enemy) { Add(std::unique_ptr<GameObject>(enemy.release()), GameObjectList); }

	void AddEnemyHulkToGameObjectList(std::unique_ptr<EnemyHulk>& hulk) { Add(std::unique_ptr<GameObject>(hulk.release()), GameObjectList); }
	
	void AddProjectileToGameObjectList(std::unique_ptr<Projectile> projectile) { Add(std::unique_ptr<GameObject>(projectile.release()), GameObjectList); }

	//==================================:::::|||||[--- SPAWN & SPAWNER FUNCTIONS ---]|||||:::::==================================//
	void SpawnPlayerCharacter(const sf::Vector2f& position)
	{
		auto newCharacter = std::make_unique<PlayerCharacter>(position);
		newCharacter->SetActive(true);
		Player = newCharacter.get();
		AddPlayerToGameObjectList(newCharacter);
	}

	void SpawnHumanCharacter(const sf::Vector2f& position)
	{
		auto newHuman = std::make_unique<HumanCharacter>(position, *this);
		newHuman->SetActive(true);
		AddHumanToGameObjectList(newHuman);
	}

	void SpawnEnemyCharacter(const sf::Vector2f& position)
	{
		sf::Vector2f randomDirection = GetRandomVector(-1.f, 1.f);
		auto newCharacter = std::make_unique<EnemyCharacter>(position, *Player, randomDirection);
		newCharacter->SetVelocity(randomDirection);
		newCharacter->SetActive(true);
		AddEnemyGruntToGameObjectList(newCharacter);
	}

	void SpawnEnemyHulk(const sf::Vector2f& position) 
	{
		static int HulkCount = 0;
		if (HulkCount > 5) return;
		sf::Vector2f randomDirection = GetRandomVector(-1.f, 1.f);
		auto newHulk = std::make_unique<EnemyHulk>(position, *Player, randomDirection, *this);
		newHulk->SetVelocity(randomDirection);
		AddEnemyHulkToGameObjectList(newHulk);
		HulkCount++;
	}

	void SpawnProjectile(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<Projectile>(position, direction, speed);
		newProjectile->SetActive(true);
		AddProjectileToGameObjectList(std::move(newProjectile));
	}

	//==================================:::::|||||[--- COLLISION FUNCTIONS ---]|||||:::::==================================//
	void GameObjectListCollisionCheck() 
	{
		for (int i = 0; i < GameObjectList.size(); i++)
		{
			for (int j = 0; j < GameObjectList.size(); j++)
			{
				if (i != j && GameObjectList[i]->GetSprite().getGlobalBounds().findIntersection(GameObjectList[j]->GetSprite().getGlobalBounds()))
				{
					GameObjectList[i]->OnCollision(GameObjectList[j]->GetTag());
					GameObjectList[j]->OnCollision(GameObjectList[j]->GetTag());
				}
			}
		}
	}

	//Placed this in collisions section as it's closely related
	void RemoveEntityFromList()
	{
		for (int i = 0; i < GameObjectList.size(); i++)
		{
			if (!GameObjectList[i]->IsActive())
			{
				GameObjectList.erase(GameObjectList.begin() + i);
				//std::cout << "GameObject: " << i << " removed from list!" << std::endl;
			}
		}
	}

	//==================================:::::|||||[--- UPDATE & RENDER FUNCTIONS ---]|||||:::::==================================//
	void UpdateAllEntities(sf::RenderWindow& window, InputHandler& inputHandler)
	{ 
		UpdateAll(GameObjectList);
		inputHandler.MoveCharacter(GetPlayer());
		inputHandler.FireProjectile(*this, Player->GetSprite().getPosition(), GetMouseDirection(window, *Player), 20.f);
	}

	void RenderAllGameObjects(sf::RenderWindow& window) { RenderAll(GameObjectList, window); }

	//==================================:::::|||||[--- EXTRA FUNCTIONS ---]|||||:::::==================================//
	Character& GetPlayer() { return *Player; }

	bool AreEnemiesDead() const
	{
		int count = 0;
		for (const auto& obj : GameObjectList)
		{
			if (obj->IsActive()) 
			{
				const std::string& tag = obj->GetTag();
				if (tag == "Enemy" || tag == "EnemyBrain" || tag == "EnemyTank")
				{
					count++;
					return false;
				}
			}
		}
		return true;
	}

	float GetRandomNumber(float a, float b) const
	{
		//This function is completely from an online source, as I saw no other way to achieve this
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(a, b);
		float randomNumber = dis(gen);
		return randomNumber;
	}

	sf::Vector2f GetRandomVector(float a, float b) const
	{
		return sf::Vector2f(GetRandomNumber(a, b), GetRandomNumber(a, b));
	}

private:
	PlayerCharacter* Player;
	std::vector<std::unique_ptr<GameObject>> GameObjectList;

	sf::Vector2f GetMouseDirection(sf::RenderWindow& window, PlayerCharacter& player)
	{
		float angle = atan2(sf::Mouse::getPosition(window).y - player.GetSprite().getPosition().y,
							sf::Mouse::getPosition(window).x - player.GetSprite().getPosition().x);

		return sf::Vector2f(cos(angle), sin(angle));
	}

	void BorderCollisionCheck(GameObject& object)
	{

		//REFACTOR: Makes this work with hitbox variable
		//Right Collision
		if (object.GetSprite().getPosition().x < 0)
		{
			object.GetSprite().setPosition(sf::Vector2f(0, object.GetSprite().getPosition().y));
			object.SetVelocity(sf::Vector2f(-object.GetVelocity().x, object.GetVelocity().y));
			if (object.GetTag() == "Projectile") object.SetActive(false);
		}
		//Left Collision
		if (object.GetSprite().getPosition().x + object.GetSprite().getGlobalBounds().size.x > 1000)
		{
			object.GetSprite().setPosition(sf::Vector2f(1000 - object.GetSprite().getGlobalBounds().size.x, object.GetSprite().getPosition().y));
			object.SetVelocity(sf::Vector2f(-object.GetVelocity().x, object.GetVelocity().y));
			if (object.GetTag() == "Projectile") object.SetActive(false);
		}
		//Top Collision
		if (object.GetSprite().getPosition().y < 0)
		{
			object.GetSprite().setPosition(sf::Vector2f(object.GetSprite().getPosition().x, 0));
			object.SetVelocity(sf::Vector2f(object.GetVelocity().x, -object.GetVelocity().y));
			if (object.GetTag() == "Projectile") object.SetActive(false);
		}
		//Bottom Collision
		if (object.GetSprite().getPosition().y + object.GetSprite().getGlobalBounds().size.y > 1000)
		{
			object.GetSprite().setPosition(sf::Vector2f(object.GetSprite().getPosition().x, 1000 - object.GetSprite().getGlobalBounds().size.y));
			object.SetVelocity(sf::Vector2f(object.GetVelocity().x, -object.GetVelocity().y));
			if (object.GetTag() == "Projectile") object.SetActive(false);
		}
	}
};