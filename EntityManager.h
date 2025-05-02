#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "PlayerCharacter.h"
#include "InputHandler.h"
#include "EnemyCharacter.h"

class Character;
class PlayerCharacter;

class EntityManager
{
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
		//ASK: Is it better to keep this here or in InputHandler?
		//TO-DO: Use PlayerCharacter class instead of Sprite here!
		float angle = atan2(sf::Mouse::getPosition(window).y - player.GetSprite().getPosition().y,
			sf::Mouse::getPosition(window).x - player.GetSprite().getPosition().x);

		return sf::Vector2f(cos(angle), sin(angle));
	}

public:
	EntityManager()
	{
		Player = std::make_unique<PlayerCharacter>();
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

	//==================================:::::|||||[CHARACTER STUFF]|||||:::::==================================//
	Character* AddCharacter(std::unique_ptr<Character> character) { Add(std::move(character), CharacterList); }

	void AddToPlayerCharacterList(std::unique_ptr<PlayerCharacter>& player)
	{ 
		Add(std::unique_ptr<Character>(player.release()), CharacterList);
	}

	void AddEnemyCharacterToList(std::unique_ptr<EnemyCharacter>& enemy)
	{
		Add(std::unique_ptr<Character>(enemy.release()), CharacterList);
	}

	void UpdateAllCharacters(sf::RenderWindow & window, InputHandler& inputHandler, float deltaTime)
	{
		UpdateAll(CharacterList);

		inputHandler.MoveCharacter(*Player);
		inputHandler.FireProjectile(*this, Player->GetSprite().getPosition(), GetMouseDirection(window, *Player), 10.f, deltaTime);

		BorderCollisionCheck(Player->GetSprite());
	}

	void RenderAllCharacters(sf::RenderWindow& window)
	{
		RenderAll(CharacterList, window);
		Player->Render(window);
	}

	void SpawnPlayerCharacter(const sf::Vector2f& position)
	{
		auto newCharacter = std::make_unique<PlayerCharacter>();
		newCharacter->SetPosition(position.x, position.y);
		newCharacter->SetActive(true);
		AddCharacter(std::move(newCharacter));
	}


	//==================================:::::|||||[PROJECTILE STUFF]|||||:::::==================================//
	void AddProjectile(std::unique_ptr<Projectile> projectile)
	{
		Add(std::move(projectile), ProjectileList);
		std::cout << "Projectile List Length = " << ProjectileList.size() << std::endl;
	}

	void UpdateAllProjectiles() { UpdateAll(ProjectileList); }
	void RenderAllProjectiles(sf::RenderWindow& window){ RenderAll(ProjectileList, window); }

	void SpawnProjectile(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<Projectile>(position, direction, speed);
		newProjectile->SetActive(true);
		AddProjectile(std::move(newProjectile));
	}

	//==================================:::::|||||[ALL GAME OBJECTS]|||||:::::==================================//
	void AddEntity(std::unique_ptr<GameObject>& entity) { Add(std::move(entity), GameObjectList); }

	void UpdateAllEntities() { UpdateAll(GameObjectList); }

	void RenderAllEntities(sf::RenderWindow& window) { RenderAll(GameObjectList, window); }


private:
	std::unique_ptr <PlayerCharacter> Player;
	std::vector<std::unique_ptr<GameObject>> GameObjectList;
	std::vector<std::unique_ptr<Character>> CharacterList;
	std::vector<std::unique_ptr<Projectile>> ProjectileList;
};