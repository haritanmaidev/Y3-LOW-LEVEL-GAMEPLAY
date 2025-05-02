#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "PlayerCharacter.h"

class Character;
class PlayerCharacter;

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager() = default;

	template <typename T> void Add(std::unique_ptr<T>& entity, std::vector<std::unique_ptr<T>>& list)
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

	//==================================:::::|||||[ALL GAME OBJECTS]|||||:::::==================================//
    void AddEntity(std::unique_ptr<GameObject>& entity) 
	{ 
		Add(entity, EntityList);
	}

    void UpdateAllEntities(){ UpdateAll(EntityList); }

    void RenderAllEntities(sf::RenderWindow& window) { RenderAll(EntityList, window); }


	//==================================:::::|||||[CHARACTER STUFF]|||||:::::==================================//
	void AddCharacter(std::unique_ptr<Character> character) { Add(character, CharacterList); }

	void UpdateAllCharacters() { UpdateAll(CharacterList); }

	void RenderAllCharacters(sf::RenderWindow& window) { RenderAll(CharacterList, window); }

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
		Add(projectile, ProjectileList);
		std::cout << "Projectile List Length = " << ProjectileList.size() << std::endl;
	}

	void UpdateAllProjectiles() { UpdateAll(ProjectileList); }
	void RenderAllProjectiles(sf::RenderWindow& window){ RenderAll(ProjectileList, window); }

	void SpawnProjectile(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<Projectile>(position, direction, speed);
		newProjectile->SetActive(true);
		AddProjectile(std::move(newProjectile));
		//AddProjectile(newProjectile);
	}

	void RemoveProjectile(Projectile* projectile)
	{
		auto it = std::remove_if(ProjectileList.begin(), ProjectileList.end(),
			[projectile](const std::unique_ptr<Projectile>& p) { return p.get() == projectile; });
		if (it != ProjectileList.end())
		{
			ProjectileList.erase(it, ProjectileList.end());
			std::cout << "Projectile Removed from Projectile List!" << std::endl;
		}
	}

private:
	std::vector<std::unique_ptr<GameObject>> EntityList;
	std::vector<std::unique_ptr<Character>> CharacterList;
	std::vector<std::unique_ptr<Projectile>> ProjectileList;
};