#pragma once
#include "GameObject.h"
#include "Projectile.h"

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager() = default;

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

	//==================================|||||[ALL GAME OBJECT'S MANAGER]|||||==================================
    void AddEntity(std::unique_ptr<GameObject> entity)
    {
        EntityList.push_back(std::move(entity));
    }

    void UpdateAllEntities(){ UpdateAll(EntityList); }
    void RenderAllEntities(sf::RenderWindow& window) { RenderAll(EntityList, window); }

	//==================================|||||[PROJECTILE STUFF]|||||==================================
	void AddProjectile(std::unique_ptr<Projectile> projectile)
	{
		ProjectileList.push_back(std::move(projectile));
		//std::cout << "Projectile List Length = " << ProjectileList.size() << std::endl;
	}

	void UpdateAllProjectiles() { UpdateAll(ProjectileList); }
	void RenderAllProjectiles(sf::RenderWindow& window){ RenderAll(ProjectileList, window); }

	void SpawnProjectile(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<Projectile>(position, direction, speed);
		newProjectile->SetActive(true);
		AddProjectile(std::move(newProjectile));
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
	//std::vector<std::unique_ptr<>
};