#pragma once
#include "Character.h"

class EntityManager;

class HumanCharacter : public Character
{
public:
	//Constructor & Destructor
	HumanCharacter(const sf::Vector2f& spawn, const EntityManager& EntityManagerRef);
	~HumanCharacter() = default;

	//Override Functions
	void Update() override;
	void MoveCharacter(const sf::Vector2f& direction) override;
	void OnCollision(const std::string& tag) override;
	void TakeDamage(int damage, const std::string& damageBy) override;
	void Die(const std::string& killedBy) override;

private:
	const EntityManager& entityManager;
	float randomMoveTimer = 0.f;
	sf::Vector2f randomDirection = sf::Vector2f(0.f, 0.f);
};

