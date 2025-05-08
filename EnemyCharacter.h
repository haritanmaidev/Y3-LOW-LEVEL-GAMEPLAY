#pragma once
#include "Character.h"

class PlayerCharacter;

class EnemyCharacter : public Character
{
public:
	//Constructor & Destructor
	EnemyCharacter(const sf::Vector2f& spawn, const PlayerCharacter& player, sf::Vector2f& randomDir);
	~EnemyCharacter() = default;

	//Override Functions
	void Awake() override;
	void OnCollision() override;
	void Update() override;
	void MoveCharacter(const sf::Vector2f& direction) override;
	void TakeDamage(int damage) override;
	void Die() override;

private:
	const PlayerCharacter& playerref;
	float detectionRadius = 300.f;
	sf::Vector2f travelDir = sf::Vector2f(0.f, 0.f);
};