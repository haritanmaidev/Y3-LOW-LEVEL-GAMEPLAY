#pragma once
#include <random>
#include "InputHandler.h"
#include "PlayerCharacter.h"
#include "HumanCharacter.h"
#include "EnemyHulk.h"
#include "EnemyBrain.h"
#include "EnemyEnforcer.h"
#include "EnemyTank.h"
#include "Projectile.h"
#include "ProjectileEnforcer.h"
#include "ProjectileSnake.h"
#include "ProjectileShell.h"
#include "Electrode.h"

class EntityManager
{
public:
	//Constructor & Destructor
	EntityManager();
	~EntityManager() = default;

	//==================================:::::|||||[--- TEMPLATE FUNCTIONS ---]|||||:::::==================================//
	template <typename T> void Add(std::unique_ptr<T>&& entity, std::vector<std::unique_ptr<T>>& list)
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

	//==================================:::::|||||[--- ADD TO LIST FUNCTIONS ---]|||||:::::==================================//
	void AddGameObjectToGameObjectList(std::unique_ptr<GameObject>& entity) { Add(std::move(entity), GameObjectList); }

	void AddPlayerToGameObjectList(std::unique_ptr<PlayerCharacter>& player) { Add(std::unique_ptr<GameObject>(player.release()), GameObjectList); }

	void AddHumanToGameObjectList(std::unique_ptr<HumanCharacter>& human) { Add(std::unique_ptr<GameObject>(human.release()), GameObjectList); }

	void AddEnemyGruntToGameObjectList(std::unique_ptr<EnemyCharacter>& enemy) { Add(std::unique_ptr<GameObject>(enemy.release()), GameObjectList); }

	void AddEnemyHulkToGameObjectList(std::unique_ptr<EnemyHulk>& hulk) { Add(std::unique_ptr<GameObject>(hulk.release()), GameObjectList); }

	void AddEnemyBrainToGameObjectList(std::unique_ptr<EnemyBrain>& brain) { Add(std::unique_ptr<GameObject>(brain.release()), GameObjectList); }

	void AddEnemyEnforcerToGameObjectList(std::unique_ptr<EnemyEnforcer>& enforcer) { Add(std::unique_ptr<GameObject>(enforcer.release()), GameObjectList); }

	void addEnemyTankToGameObjectList(std::unique_ptr<EnemyTank>& tank) { Add(std::unique_ptr<GameObject>(tank.release()), GameObjectList); }

	void AddProjectileToGameObjectList(std::unique_ptr<Projectile> projectile) { Add(std::unique_ptr<GameObject>(projectile.release()), GameObjectList); }

	void AddProjectileSnakeToGameObjectList(std::unique_ptr<ProjectileSnake> projectile) { Add(std::unique_ptr<GameObject>(projectile.release()), GameObjectList); }

	void AddProjectileEnforcerToGameObjectList(std::unique_ptr<ProjectileEnforcer> projectile) { Add(std::unique_ptr<GameObject>(projectile.release()), GameObjectList); }

	void AddProjectileShellToGameObjectList(std::unique_ptr<ProjectileShell> projectile) { Add(std::unique_ptr<GameObject>(projectile.release()), GameObjectList); }

	void addElectrodeToGameObjectList(std::unique_ptr<Electrode> electrode) { Add(std::unique_ptr<GameObject>(electrode.release()), GameObjectList); }

	//==================================:::::|||||[--- SPAWN FUNCTIONS ---]|||||:::::==================================//
	void SpawnPlayerCharacter(const sf::Vector2f& position)
	{
		auto newCharacter = std::make_unique<PlayerCharacter>(position);
		Player = newCharacter.get();
		AddPlayerToGameObjectList(newCharacter);
	}

	void SpawnHumanCharacter(const sf::Vector2f& position)
	{
		auto newHuman = std::make_unique<HumanCharacter>(position, *Player, *this);
		AddHumanToGameObjectList(newHuman);
	}

	void SpawnEnemyCharacter(const sf::Vector2f& position)
	{
		sf::Vector2f randomDirection = GetRandomVector(-1.f, 1.f);
		auto newCharacter = std::make_unique<EnemyCharacter>(position, *Player, randomDirection);
		newCharacter->SetVelocity(randomDirection);
		AddEnemyGruntToGameObjectList(newCharacter);
	}

	void SpawnEnemyHulk(const sf::Vector2f& position)
	{
		sf::Vector2f randomDirection = GetRandomVector(-1.f, 1.f);
		auto newHulk = std::make_unique<EnemyHulk>(position, *Player, randomDirection, *this);
		newHulk->SetVelocity(randomDirection);
		AddEnemyHulkToGameObjectList(newHulk);
	}

	void SpawnEnemyBrain(const sf::Vector2f& position)
	{
		sf::Vector2f randomDirection = GetRandomVector(-1.f, 1.f);
		auto newBrain = std::make_unique<EnemyBrain>(position, *Player, randomDirection, *this);
		newBrain->SetVelocity(randomDirection);
		AddEnemyBrainToGameObjectList(newBrain);
	}

	void SpawnEnemyEnforcer(const sf::Vector2f& position)
	{
		sf::Vector2f randomDirection = GetRandomVector(-1.f, 1.f);
		auto newEnforcer = std::make_unique<EnemyEnforcer>(position, *Player, randomDirection, *this);
		newEnforcer->SetVelocity(randomDirection);
		AddEnemyEnforcerToGameObjectList(newEnforcer);
	}

	void SpawnEnemyTank(const sf::Vector2f& position)
	{
		sf::Vector2f randomDirection = GetRandomVector(-1.f, 1.f);
		auto newTank = std::make_unique<EnemyTank>(position, *Player, randomDirection, *this);
		newTank->SetVelocity(randomDirection);
		addEnemyTankToGameObjectList(newTank);
	}

	void SpawnProjectile(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<Projectile>(position, direction, speed);
		AddProjectileToGameObjectList(std::move(newProjectile));
	}

	void SpawnProjectileSnake(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<ProjectileSnake>(position, direction, speed, *Player);
		AddProjectileSnakeToGameObjectList(std::move(newProjectile));
	}

	void SpawnProjectileEnforcer(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<ProjectileEnforcer>(position, direction, speed, *Player);
		AddProjectileEnforcerToGameObjectList(std::move(newProjectile));
	}

	void SpawnProjectileShell(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<ProjectileShell>(position, direction, speed);
		newProjectile->SetVelocity(direction);
		AddProjectileShellToGameObjectList(std::move(newProjectile));
	}

	void SpawnElectrode(const sf::Vector2f& position)
	{
		auto newElectrode = std::make_unique<Electrode>(position);
		addElectrodeToGameObjectList(std::move(newElectrode));
	}

	//==================================:::::|||||[--- UPDATE - RENDER FUNCTIONS ---]|||||:::::==================================//
	void UpdateAllEntities(sf::RenderWindow& window, InputHandler& inputHandler)
	{
		UpdateAll(GameObjectList);
		inputHandler.MoveCharacter(GetPlayer());
		inputHandler.FireProjectile(*this, Player->GetSprite().getPosition(), GetMouseDirection(window, *Player), 15.5f);
		//inputHandler.GetCoordinates(window);
	}

	void RenderAllGameObjects(sf::RenderWindow& window) { RenderAll(GameObjectList, window); }

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

	void RemoveEntityFromList()
	{
		for (int i = 0; i < GameObjectList.size(); i++)
		{
			if (!GameObjectList[i]->IsActive() && GameObjectList[i]->GetTag() != "Player")
			{
				GameObjectList.erase(GameObjectList.begin() + i);
				i--;
				//std::cout << "GameObject: " << i << " removed from list!" << std::endl;
			}
		}
	}

	void ClearAll()
	{
		GameObjectList.clear();
		Player = nullptr;
	}

	//==================================:::::|||||[--- WAVE SYSTEM RELATED FUNCTIONS ---]|||||:::::==================================//
	//The enemies marked here are the ones that are required to be killed in order to clear wave
	bool AreEnemiesDead() const
	{
		for (const auto& obj : GameObjectList)
		{
			if (obj->IsActive())
			{
				const std::string& tag = obj->GetTag();
				if (tag == "Enemy" || tag == "EnemyEnforcer" || tag == "EnemyBrain" 
					|| tag == "EnemyTank" || tag == "ProjectileSnake" || tag == "ProjectileShell")
				{
					return false;
				}
				else if(tag == "Human") 
				{
					HumanCharacter* human = dynamic_cast<HumanCharacter*>(obj.get());
					if (human && human->isCorrupt)
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	//The enemies marked here aren't required to be killed for wave progression
	void ResetSceneForWaves()
	{
		for (auto& obj : GameObjectList)
		{
			const std::string& tag = obj->GetTag();
			if (tag == "EnemyHulk" || tag == "Human" || tag == "Electrode")
			{
				obj->SetActive(false);
			}
			else if (tag == "Player")
			{
				sf::Vector2f pos = sf::Vector2f(GetRandomNumber(450, 550), GetRandomNumber(550, 650));
			}
		}
	}

	//==================================:::::|||||[--- EXTRA FUNCTIONS ---]|||||:::::==================================//
	Character& GetPlayer() const { return *Player; }

	HumanCharacter* GetActiveHumanForBrain() const
	{
		for (auto& obj : GameObjectList)
		{
			HumanCharacter* human = dynamic_cast<HumanCharacter*>(obj.get());
			if (human && human->IsActive())
			{
				if(!human->isCorrupt) return human;
			}
		}

		return nullptr;
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
	HumanCharacter* Human;
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
		//Left Collision
		if (object.GetPosition().x < 20)
		{
			object.SetPosition(20.f, object.GetPosition().y);

			object.SetVelocity(sf::Vector2f(-object.GetVelocity().x, object.GetVelocity().y));

			if (object.GetTag() == "Projectile") object.SetActive(false);
		}
		//Right Collision
		if (object.GetPosition().x > 998)
		{
			object.SetPosition(998, object.GetPosition().y);

			object.SetVelocity(sf::Vector2f(-object.GetVelocity().x, object.GetVelocity().y));

			if (object.GetTag() == "Projectile") object.SetActive(false);
		}
		//Top Collision
		if (object.GetPosition().y < 76)
		{
			std::cout << "Top Collision" << std::endl;
			object.SetPosition(object.GetPosition().x, 86);

			object.SetVelocity(sf::Vector2f(object.GetVelocity().x, -object.GetVelocity().y));

			if (object.GetTag() == "Projectile") object.SetActive(false);
		}
		//Bottom Collision
		if (object.GetPosition().y > 998)
		{
			std::cout << "Bottom Collision" << std::endl;
			object.SetPosition(object.GetPosition().x, 998.f);

			object.SetVelocity(sf::Vector2f(object.GetVelocity().x, -object.GetVelocity().y));

			if (object.GetTag() == "Projectile") object.SetActive(false);
		}
	}
};