#pragma once
#include "EnemyCharacter.h"

class EntityManager;

class EnemyEnforcer : public EnemyCharacter
{
public:
	//Constructor & Destructor
	EnemyEnforcer(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir, EntityManager& EntityManagerRef);
	~EnemyEnforcer() = default;

	//Override Functions
	void Update() override;
	void MoveCharacter(const sf::Vector2f& direction) override;
	void OnCollision(const std::string& tag) override;
	void TakeDamage(int damage, const std::string& damageBy) override;
	void Die(const std::string& taggedBy) override;

	//Class Functions
	void FireMine(const sf ::Vector2f& dir);

private:
	EntityManager& entityManager;
	const PlayerCharacter& PlayerRef;
	float fireRate = 5.5f;
	float fireTimer = 0.f;
	float detectionRadius = 500.f;
};

