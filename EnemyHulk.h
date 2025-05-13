#pragma once
#include "EnemyCharacter.h"

class EntityManager;

class EnemyHulk : public EnemyCharacter
{
public:
	//Constrcutor & Destructor
	EnemyHulk(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir, const EntityManager& EntityManagerRef);
	~EnemyHulk() = default;

	//Override Functions
	void Update() override;
	void MoveCharacter(const sf::Vector2f& direction) override;
	void OnCollision(const std::string& tag) override;
	void TakeDamage(int damage, const std::string& damageBy) override;
	void Die(const std::string& taggedBy) override;

private:
	const EntityManager& entityManager;
	float randomMoveTimer = 0.f;
	sf::Vector2f randomDirection = sf::Vector2f(0.f, 0.f);
};