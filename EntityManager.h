#include "GameObject.h"
#include "Projectile.h"

class EntityManager
{
public:
	//===========================|||||[ALL GAME OBJECT'S MANAGER]|||||===========================
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

	//==================================|||||[PROJECTILE STUFF]|||||==================================
	void AddProjectile(std::unique_ptr<Projectile> projectile)
	{
		ProjectileList.push_back(std::move(projectile));
		std::cout << "Projectile List Length = " << ProjectileList.size() << std::endl;
		//WORKS: std::cout << "Projectile Added to Projectile List!" << std::endl;
	}

	void SpawnProjectile(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
	{
		auto newProjectile = std::make_unique<Projectile>(position, direction, speed);
		newProjectile->SetActive(true);
		newProjectile->Awake();
		AddProjectile(std::move(newProjectile));
		//WORKS: std::cout << "Spawn Projectile Called!" << std::endl;
		//ProjectileList.push_back(std::move(newProjectile));
	}

	void UpdateAllProjectiles()
	{
		std::cout << "ProjectileList's Update is called!" << std::endl;
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
};