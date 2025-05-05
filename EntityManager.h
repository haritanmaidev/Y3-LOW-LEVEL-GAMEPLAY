#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "PlayerCharacter.h"
#include "InputHandler.h"
#include "EnemyCharacter.h"

class EntityManager
{
public:
	EntityManager()
	{
		Player = std::make_unique<PlayerCharacter>(sf::Vector2f(100.f, 100.f));

		SpawnEnemyCharacter(sf::Vector2f(800.f, 200.f));
		SpawnEnemyCharacter(sf::Vector2f(800.f, 375.f));
		SpawnEnemyCharacter(sf::Vector2f(800.f, 550.f));
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
			entity->Update();
		}
	}

	template <typename T> void RenderAll(std::vector<std::unique_ptr<T>>& list, sf::RenderWindow& window)
	{
		for (auto& entity : list)
		{
			entity->Render(window);
		}
	}

	//==================================:::::|||||[CHARACTER STUFF][CHARACTER STUFF][CHARACTER STUFF]|||||:::::==================================//
	//ASK: This function is called in SpawnPlayer which passes this a PlayerCharacter rvalue, so this means, even if the types are different, as long as its RVALUE, it works?
	//Character* AddCharacter(std::unique_ptr<Character> character) { Add(std::move(character), CharacterList); }

	void AddPlayerToCharacterList(std::unique_ptr<PlayerCharacter>& player)
	{ 
		Add(std::unique_ptr<Character>(player.release()), CharacterList);
	}

	//NOTE: Current not used since I'm focusing on Singleplayer functionality
	void SpawnPlayerCharacter(const sf::Vector2f& position)
	{
		auto newCharacter = std::make_unique<PlayerCharacter>(position);
		newCharacter->SetActive(true);
		AddPlayerToCharacterList(newCharacter);
	}

	void AddEnemyToCharacterList(std::unique_ptr<EnemyCharacter>& enemy)
	{
		Add(std::unique_ptr<Character>(enemy.release()), CharacterList);
	}

	void SpawnEnemyCharacter(const sf::Vector2f& position)
	{
		auto newCharacter = std::make_unique<EnemyCharacter>(position, *Player);
		newCharacter->SetActive(true);
		AddEnemyToCharacterList(newCharacter);
		//Add(std::unique_ptr<GameObject>(newCharacter.release()), GameObjectList);
	}
	
	void EnemySpawner() 
	{
		spawnTimer += 0.1f;
		std::cout << "Spawn Timer = " << spawnTimer << std::endl;
		if (spawnRate < spawnTimer)
		{
			SpawnEnemyCharacter(sf::Vector2f(800.f, rand() % 1000));
			spawnTimer = 0.f;
		}
	}

	void UpdateAllCharacters(sf::RenderWindow & window, InputHandler& inputHandler)
	{
		UpdateAll(CharacterList);

		inputHandler.MoveCharacter(*Player);
		inputHandler.FireProjectile(*this, Player->GetSprite().getPosition(), GetMouseDirection(window, *Player), 20.f);

		BorderCollisionCheck(Player->GetSprite());
	}

	void RenderAllCharacters(sf::RenderWindow& window)
	{
		RenderAll(CharacterList, window);
		Player->Render(window);
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

private:
	std::unique_ptr <PlayerCharacter> Player;
	std::vector<std::unique_ptr<GameObject>> GameObjectList;
	std::vector<std::unique_ptr<Character>> CharacterList;
	std::vector<std::unique_ptr<Projectile>> ProjectileList;

	float spawnTimer = 0.f;
	float spawnRate = 5.f;

	void BorderCollisionCheck(sf::Sprite& mainCharacter)
	{
		//Right Collision
		if (mainCharacter.getPosition().x < 0)
		{
			mainCharacter.setPosition(sf::Vector2f(0, mainCharacter.getPosition().y));
		}
		//Left Collision
		if (mainCharacter.getPosition().x + mainCharacter.getGlobalBounds().size.x > 1000)
		{
			mainCharacter.setPosition(sf::Vector2f(1000 - mainCharacter.getGlobalBounds().size.x, mainCharacter.getPosition().y));
		}
		//Top Collision
		if (mainCharacter.getPosition().y < 0)
		{
			mainCharacter.setPosition(sf::Vector2f(mainCharacter.getPosition().x, 0));
		}
		//Bottom Collision
		if (mainCharacter.getPosition().y + mainCharacter.getGlobalBounds().size.y > 1000)
		{
			mainCharacter.setPosition(sf::Vector2f(mainCharacter.getPosition().x, 1000 - mainCharacter.getGlobalBounds().size.y));
		}
	}

	sf::Vector2f GetMouseDirection(sf::RenderWindow& window, PlayerCharacter& player)
	{
		float angle = atan2(sf::Mouse::getPosition(window).y - player.GetSprite().getPosition().y,
							sf::Mouse::getPosition(window).x - player.GetSprite().getPosition().x);

		return sf::Vector2f(cos(angle), sin(angle));
	}
};