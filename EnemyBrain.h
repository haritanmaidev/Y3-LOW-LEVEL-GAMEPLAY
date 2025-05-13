#pragma once
#include "EnemyCharacter.h"

class EntityManager;
class PlayerCharacter;
class HumanCharacter;

class EnemyBrain : public EnemyCharacter
{
public:
	//Constructor & Destructor
	EnemyBrain(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir, EntityManager& EntityManagerRef);
	~EnemyBrain() = default;

	//Override Functions
	void Update() override;
	void MoveCharacter(const sf::Vector2f& direction) override;
	void OnCollision(const std::string& tag) override;
	void TakeDamage(int damage, const std::string& damageBy) override;
	void Die(const std::string& taggedBy) override;

private:
	EntityManager& entityManager;
	const PlayerCharacter& playerRef;
	HumanCharacter* humanRef;
	float fireTimer = 0.f;
	float randomMoveTimer = 0.f;
	sf::Vector2f randomDirection = sf::Vector2f(0.f, 0.f);
};