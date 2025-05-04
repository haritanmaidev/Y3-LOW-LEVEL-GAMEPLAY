#pragma once
#include "Character.h"

class PlayerCharacter;

class EnemyCharacter : public Character
{
public:
	//Constructor & Destructor
	EnemyCharacter(const sf::Vector2f& spawn, const PlayerCharacter& player);
	~EnemyCharacter() = default;

	//Override Functions
	void Awake() override;
	void OnCollision() override;
	void Update() override;
	void TakeDamage(int& damage) override;
	void MoveCharacter(const sf::Vector2f& direction) override;
	void Die() override;

private:
	const PlayerCharacter& playerref;
};