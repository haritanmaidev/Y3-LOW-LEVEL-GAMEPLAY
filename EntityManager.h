#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Projectile.h"

class EntityManager
{
public:
	//ALL GAME OBJECTS' MANAGER!
    void AddEntity(std::unique_ptr<GameObject> entity)
    {
        EntityList.push_back(std::move(entity));
    }

    void UpdateAllEntities()
    {
        for (auto& entity : EntityList)
        {
            entity->Update();
        }
    }

    void RenderAllEntities(sf::RenderWindow& window)
    {
        for (auto& entity : EntityList)
        {
            entity->Render(window);
        }
    }

	//PROJECTILE MANAGER!
	void AddProjectile(std::unique_ptr<Projectile> projectile)
	{
		ProjectileList.push_back(std::move(projectile));
	}

	void UpdateAllProjectiles()
	{
		for (auto& projectile : ProjectileList)
		{
			projectile->Update();
		}
	}

	void RenderAllProjectiles(sf::RenderWindow& window)
	{
		for (auto& projectile : ProjectileList)
		{
			projectile->Render(window);
		}
	}

private:
    std::vector<std::unique_ptr<GameObject>> EntityList;
	std::vector<std::unique_ptr<Projectile>> ProjectileList;
	//std::vector<std::unique_ptr<Enemy>> EnemyList;
};