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
	void FireMine();

private:
	EntityManager& entityManager;
	const PlayerCharacter& PlayerRef;
	float fireRate = 0.5f;
	float fireTimer = 0.f;
	float detectionRadius = 800.f;
	float randomMoveTimer = 0.f;
	float randomMoveRate = 10.f;
	sf::Vector2f randomDirection = sf::Vector2f(0.f, 0.f);
};

